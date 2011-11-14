#include "CSinglePlayerState.hpp"
#include "../utils/CFadingImage.hpp"
#include "../CGraphicalLevel.hpp"
#include "../CFleet.hpp"
#include "../entities/IMultiModeTransformer.hpp"
#include <fusion/core/string.hpp>
#include "../states/CErrorState.hpp"



// todo updater level ?
void
CSinglePlayerState::updatePlaying()
{

//reloadLevel()
    if( ! _initialized ){

        if( setupLuaThread() ){
            _initialized = true;
        }
        else {
            //_initialized = false;
            //return;
        }
    }

    float percievedSpeed = 0.f;
    float speed = 0.f;


    const TTimeUnit& elapsedTime = engine()->getElapsedTime();

    //_player->update( CGameEngine::getInstance() )
    speed = _player->_walkyrie->getSpeed(SModeDescription::DefaultForward)/100.f;

    // plus on est eloigne du bas de l'ecran plus la sensation de vitesse
    float ecart = (_player->getPosition().Z- conf::_LOWER_LIMIT);
    ecart /= (conf::_UPPER_PART - conf::_LOWER_LIMIT);
    // Comme ca on a un ecart < 1

    //_INFO << "ecart " << ecart;
    speed += ecart/1000.f;// /10.f


    //_INFO << "upper progress" << _levelMgr._upperProgress/100.f;

    percievedSpeed += (speed);

    // TOOOOOOODOOOO : a retirer !!
    //BUG
    // HACK
    //getLevelManager()
//    if( _levelMgr) {
//        getLevelManager().updatePlayerProgress(percievedSpeed);
//    }


    //_INFO << "speed" << translation;

    // Selon l'avancement du joueur, incliner plus ou moins la camera
    this->updateCamera();


    /////////////////////////////////////////////////////
    //////
    /////////////////////////////////////////////////////
    //engine()->PushState( new CTransitionState("images/youaredead.png") );



//    _enemyFleet->update(elapsedTime, _state );
//    _alliedFleet->update(elapsedTime, _state );
    _enemyFleet->update(elapsedTime);
    _alliedFleet->update(elapsedTime);


    // COLLISION: Entre le joueur et la flotte adverse
    // (cas à part pr l'instant)
    _alliedFleet->checkCollisions( *_enemyFleet);
    //collided = _enemyFleet->checkCollisions(3,getPlayer()->getPosition());

    // IF terrain registered
//    if(_terrain != 0){
//        //_terrain->getMaterial(0).getTextureMatrix(0).setTextureTranslate(0.f,-percievedSpeed/10.f);
//    }




    /////////////////////////////////////////////////////
    //////   Execute lua code
    /////////////////////////////////////////////////////

    // TODO a optimiser en loadant un chunk
    const char* filename = "scripts/update.lua";

    //_initialized =  _script->RunFile(filename);
    _initialized =  engine()->getScriptingVM().RunFile(filename);
    if(!_initialized){

        _LOG_ERROR << "Can't run [" << filename << "] from " << __LINE__ << ":" << __FILE__;

        //engine()->popupMessage(L"Lua thread error",_script->getErrorDescription() );
        engine()->popupMessage(L"Lua thread error",engine()->getScriptingVM().getErrorDescription() );
    }

}





void
CSinglePlayerState::updateStartingLevel(){
    //_INFO << "Update starting level!";


    // Fin de l'affichage
    if(  !_levelTransitionImage->update( ENGINE->getElapsedTime() ) ){

        changeState( NPlayState::Playing );
    }
}

//bool
//CSinglePlayerState::isPlayerUpdatable() const
//{
//    return (getInnerState() == NPlayState::Playing);
//}


void
CSinglePlayerState::updateEndingLevel(){
    // On commence une image de transition
    _INFO << "Transition between levels finished !";

    //_levelTransitionImage.update( engine()->getElapsedTime() );

    // Once transition finished
//    if( nextLevelName.empty() ){
//        // if there isn't any other level we go back to menu state
//    }
//    else {
//
//    }
}


bool
CSinglePlayerState::setupFadingTransition(const char* filename) {


    video::ITexture* img = engine()->driver()->getTexture(filename);

    /// starting level
    if( !img ){
        _LOG_ERROR << "Could not load [" << filename << "]";
        return false;
    }
    else {
        changeState(NPlayState::EndingLevel);


        _levelTransitionImage.reset( new CFadingImage( img ) );
        //  valeur par defaut
        _levelTransitionImage->addFading(500);
        //*_levelTransitionImage();
        return true;
    }
}


bool
CSinglePlayerState::reloadLevel()
{
    return loadLevel( _levelFilename );
}




/**
Level handling here
**/
bool
CSinglePlayerState::loadLevel(const std::string& nextLevelName) {

    // assert(state ==unitialized or FinishLevel
    _levelFilename = nextLevelName;



    _INFO << "loading level [" << nextLevelName << "]";

    // If one level already loaded than switch to "endlevel" mode
    /*
    if( _levelMgr.use_count() > 0){

         _INFO << "Changing state";
        //changeState(NPlayState::EndingLevel);

        // detruire tous les batiments des flottes actuelles
        // TODO
        //level->getEnemyFleet()->


        //const char* filename = "images/onLevelEnd.png";
        if(setupFadingTransition("images/onLevelEnd.png") ) {
            changeState(NPlayState::EndingLevel);
        }

    }
*/
// TODO passer le nom du niveau qque part

    //_levelMgr._player = _player;
    //CGraphicalLevel* level = new CGraphicalLevel();
    //level->init(this);
    //_levelMgr.reset(  );
    //level->init(  );


    // regenerer les flottes
    _enemyFleet.reset( new CFleet( this ) );
    _alliedFleet.reset( new CFleet( this ) );


    //http://permalink.gmane.org/gmane.comp.lang.lua.bind.user/2524?set_blog_all=yes
    luabind::object global_vars;
    _script->getGlobals(global_vars);

    //global_vars["GraphicalLevel"]        = level;
    global_vars["AlliedFleet"]  = getAllyFleet();
    global_vars["EnemyFleet"]   = getEnemyFleet();


    if( setupFadingTransition( "images/startingLevel.png" ) ) {
        changeState(NPlayState::StartingLevel);
    }


    bool ret     = _script->RunFile( _levelFilename.c_str() );
    if(!ret)
    {
        // TODO afficher l'erreur ici !
        _LOG_ERROR << _script->getErrorDescription();
        engine()->popupMessage(L"update.lua Error",_script->getErrorDescription() );

        //engine()->popupMessage(L"Lua Error N°2 test",_script->getErrorDescription() );
    }

    _initialized = ret;

    return ret;


}


