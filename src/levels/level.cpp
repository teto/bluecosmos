/**
* \file level.cpp
*/

/****************************
***************************/
#if 0
/****************************
***************************/
#include "level.h"
#include "entity_manager.h"
#include "../core/exceptions.h"
#include "../core/rsrc_manager.h"
#include "../core/log.h"
#include "../core/loader_manager.h"
#include "../core/rsrc_manager.h"
#include "../loaders/sound.h"
#include "../engine/game_engine.h"
#include "../utilities/skybox.h"
#include "../states/menu.h"
#include <SFML/Graphics.hpp>


////////////////////////////////
/// A gerer en lua
///////////////////////////////

void
Logger(const fus::ELogLevel& level,const std::string& message){
    fus::ILogger::Log(level) << message;
}

//! Constructor
CSinglePlayerState::CSinglePlayerState() {

    mPlayer = NULL;

    /// Load textures _DIR_IMAGES
    mTextures[ETextureLife]   = fus::GetResource<fus::CTexture>("barre",_DIR_IMAGES + "barre.bmp");
    mTextures[ETextureEnergy] = fus::GetResource<fus::CTexture>("icon",_DIR_IMAGES + "icon.bmp");
    mTextures[ETextureExplosion] = fus::GetResource<fus::CTexture>("bombe",_DIR_IMAGES + "bomb.png");
    mTextures[ETextureCursor] = fus::GetResource<fus::CTexture>("cursor",_DIR_IMAGES + "crosshair_cursor.png");
    mTextures[ETextureLockon] = fus::GetResource<fus::CTexture>("lockon",_DIR_IMAGES + "lockon.png");

    /// Allocate memory for the explosions
    mExplosions.reserve(_RESERVE_EXPLOSIONS);

    /// Set logger for omonyom
    o3::CRunner::GetInstance()->SetLogger(&Logger);
};


/// \function HandleEvents
void
CSinglePlayerState::HandleEvent(sf::Event event){

    CGameEngine* game = GameEngine();
    static bool click = false;

    //! According to event type
    switch(event.Type){
        //case sf::JoyButtonPressed
        //JoyButtonReleased
        //JoyMoved

        /// whenever a click occurs
        case sf::Event::MouseButtonPressed :

            switch (event.MouseButton.Button)
            {
            	case sf::Mouse::Left:
                    mPlayer->FireBullet();
            		break;

                case sf::Mouse::Right:
                    mPlayer->FireMissile();
                    break;

                case sf::Mouse::XButton1:
                    break;

                // permet de changer la camera ?
            	case sf::Mouse::Middle:
                    break;

            	default:
            		break;
            }

            break;

        //! If Key pressed
        case sf::Event::KeyPressed:
            //If rotation asked
            // can't go into switch beacause not constant
            if(event.Key.Code == mPlayer->mKeyMap->Rotation){
                    //then begin rotation
                    mPlayer->SwitchRotation();
                    break;
            }
            //! According to key pressed
            switch(event.Key.Code){

                // Met le jeu en pause cad n'appelle plus update()
                /*case sf::Key::P :
                    SWITCH(mPause);
                    break;*/

                // Montre les hitbox
                case sf::Key::H :
                    CEntityManager::GetInstance()->SwitchShowHitBox();
                    break;

                case sf::Key::R:
                    mPlayer->UpgradeMode(EPlus);
                    //std::cout << "Mode Up" << std::endl;
                    break;

                case sf::Key::T:
                    mPlayer->UpgradeMode(EMinus);
                    //std::cout << "Mode down" << std::endl;
                    break;

                default:
                    break;

            }// end 1st switch
            break;

// TODO
        //! If wheel moved
        case sf::Event::MouseWheelMoved:
            if(event.MouseWheel.Delta < 0){
                mPlayer->UpgradeMode(EPlus);
            }
            else{
                mPlayer->UpgradeMode(EMinus);
            }
            //game->SetCamera(event.MouseWheel.Delta,0);
            //LocalTranslate( TVectord(0,1,0) * speed * event.MouseWheel.Delta);
            break;

        case sf::Event::JoyButtonPressed:
            if(event.JoyButton.Button == 1){
                mPlayer->SwitchRotation();
            }
            break;
        default:
            break;
    }// end 1nd switch


}



// + des layers
void
CLevelManager::DrawExplosions(){

// \todo reactiver le billboard
//  BillboardPerso(GameEngine()->SetCamera(0,0),temp,fus::TVectorf(0,0,1));
    //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    //fus::TVectorf pos;
    for(std::vector<SSprite>::iterator i = mExplosions.begin();i != mExplosions.end();){

        glPushMatrix();
        glTranslatef(i->pos.x,i->pos.y,i->pos.z);

        // End of explosion
        if( ! i->sprite->Update(false) ){
            delete i->sprite;
            i = mExplosions.erase(i);

        }
        // otherwise display it
        else {
            i->sprite->Draw();
            i++;
        }
        glPopMatrix();

    }

}

//! Constructor
CLevelManager::CLevelManager() : mCurrentLevel(NULL),mCurrentWave(NULL),mLevelNumber(0) {

     /// Open the file
     if(!mLevels.Load(_FILE_LEVEL)){
         //throw fus::SLoadingException(_FILE_LEVEL," Impossible to open levels file");
         fus::ILogger::Log(EError) << " Impossible to open levels file";
     }

     // recupere le 1er niveau
     mCurrentLevel = mLevels.GetElement("levels|level");

     //essaye de charger niveau
     if(mCurrentLevel){
         //essaye de le charger tant que ca marche pas
        while(!LoadLevel(mCurrentLevel)){
            mCurrentLevel = mCurrentLevel->NextSiblingElement("level");
            if(!mCurrentLevel){
                break;
            }
        }
     }
     else{
        throw fus::SLoadingException(_FILE_LEVEL,"No <level> registered!");
     }

/*
//Skybox
    fus::TVectorf pos(_X_MAX/2,_Y_MAX/2,0);
    fus::TVectorf size(_X_MAX,_Y_MAX,80);
    fus::CTexture* textures[6] = {NULL};


    mSkyBox = new fus::CSkyBox(pos,size,textures);
*/
}



//! Destructor
CLevelManager::~CLevelManager(){

}


//! Adds a particle system
void
CLevelManager::CreateExplosion(const fus::TVectorf& pos){
    std::cout << "Explosion" << std::endl;
    //nb,speed,life,size);mettre parametre pour dire de ne pas se renouveler
    SSprite explosion;
    explosion.pos = pos;
    explosion.sprite = new fus::CSprite(mTextures[ETextureExplosion],4,4);

    mExplosions.push_back(explosion);
}




/*
faire plusieurs couches avec alphas differents,
tenir compte du temps
afficher un model 3D genre fond de terrain
*/
void
CLevelManager::Draw(){


    /*** Game ***/
    sf::IntRect v(static_cast<int>(_SIDE_BAND*ConfigManager()->GetWidth()),
                0,
                static_cast<int>(( 1 - _SIDE_BAND) * ConfigManager()->GetWidth()),
                ConfigManager()->GetHeight()
                );

    //'x' et 'y' sont les coordonnées du coin supérieur gauche de la sous-fenêtre
    //glViewport(GLint x,GLint y,GLSizei largeur,GLSizei hauteur)
    glViewport(v.Left,v.Top,v.GetWidth(),v.GetHeight());




    // To allow picking
    //CEntityManager::GetInstance()->DrawForPicking();

    CEntityManager::GetInstance()->Draw();
    mLevelManager->Draw();
    DrawExplosions();
    DrawHUD();

//TODO: dessiner le curseur seulement si celui-ci dans le carré de dessin !!
    // Draw Cursor
    const sf::Input& input = GameEngine()->GetInput();
    sf::Vector2f center(input.GetMouseX() -mTextures[ETextureLockon]->mImage.GetWidth()/2,
                        input.GetMouseY() -mTextures[ETextureLockon]->mImage.GetHeight()/2 );
    sf::Sprite cursor( mTextures[ETextureLockon]->mImage, center );
    //cursor.Resize( 20,20);
//std::cout << "cursor" << mTextures["cursor"]->mImage.GetWidth() << "/" << mTextures["cursor"]->mImage.GetHeight() << std::endl;
//std::cout << "center" << center.x << "/" <<center.y << std::endl;

    GameEngine()->Draw(cursor);


    /*static float i = 0;
    sf::Image image;
    i += 0.01;
    if( i > 1)
        i = 0;
    std::cout << "i" << i << std::endl;

    mSkyBox->Draw();

    // a une taille de 64x64 pixels
    if(image.LoadFromFile("temp/cloud.png")){
        image.Bind();
        glEnable(GL_BLEND);
        glColor4f(1.0f,1.0f,1.0f,0.5f);			// Full Brightness, 50% Alpha ( NEW )
        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
        glBegin(GL_QUADS);
        glColor4ub(255,255,255,10);
        glTexCoord2f(2,2+i);
        glVertex3i(_X_MAX,_Y_MAX,-5);
        glTexCoord2f(2,0+i);
        glVertex3i(_X_MAX,0,-5);
        glTexCoord2f(0,0+i);
        glVertex3i(0,0,-5);
        glTexCoord2f(0,2+i);
        glVertex3i(0,_Y_MAX,-5);
        glEnd();
        glDisable(GL_BLEND);
    }



    if(image.LoadFromFile("temp/forest.bmp")){
        image.Bind();
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
        glBegin(GL_QUADS);
        //glColor4ub(255,255,255,10);
        glTexCoord2f(2,2);
        glVertex3i(_X_MAX,_Y_MAX,-5);
        glTexCoord2f(2,0);
        glVertex3i(_X_MAX,0,-5);
        glTexCoord2f(0,0);
        glVertex3i(0,0,-5);
        glTexCoord2f(0,2);
        glVertex3i(0,_Y_MAX,-5);
        glEnd();
    }*/


}





//! Update creation and settlement of entities
//TODO: Play the sound and create enemy
bool
CLevelManager::Update() {



    // If no problem occured
    return true;
}
#endif
