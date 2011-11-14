#include "CParticleManager.hpp"
//#include "../game_engine.hpp"

#include <irrlicht.h>
#include <boost/foreach.hpp>
#include <fusion/fusion.hpp>

//#define _USE_MATH_DEFINES
//#include <cmath>


//SPK_Destroy(system);
//		infos+=" - VBO: "; infos+=(IRRBuffer::isVBOHintActivated() ? "true" : "false");
using namespace irr;
using namespace std;
using namespace SPK;
using namespace SPK::IRR;

CParticleManager::CParticleManager(irr::IrrlichtDevice * device) :
_explosionID(0),
_boosterID(0),
_device(device)
{
    SPK::randomSeed = device->getTimer()->getRealTime();

	// Sets the update step
	System::setClampStep(true,0.1f);			// clamp the step to 100 ms
	System::useAdaptiveStep(0.001f,0.01f);		// use an adaptive step from 1ms to 10ms (1000fps to 100fps)

    // Prepare systems
//    createBaseBooster();
//    createBaseExplosion();

    //ctor
	//cout << "\nSPARK FACTORY AFTER INIT :" << endl;
	//SPKFactory::getInstance().traceAll();
}



//void CParticleManager::handleMessage ( const CMessage& message )


// Creates the base system and returns its ID
//SPK_ID createParticleSystemBase(GLuint textureExplosion,GLuint textureFlash,GLuint textureSpark1,GLuint textureSpark2,GLuint textureWave)
//GLuint textureExplosion,GLuint textureFlash,GLuint textureSpark1,GLuint textureSpark2,
void
CParticleManager::createBaseExplosion()
{
	///////////////
	// Renderers //
	///////////////
    irr::video::IVideoDriver* driver = _device->getVideoDriver();

    irr::video::ITexture* textureExplosion  =  driver->getTexture("images/explosion/explosion.bmp");
    irr::video::ITexture* textureSpark1     =  driver->getTexture("images/explosion/spark1.bmp");
    irr::video::ITexture* textureSpark2     =  driver->getTexture("images/explosion/point.bmp");
    irr::video::ITexture* textureFlash      =  driver->getTexture("images/explosion/flash.bmp");
    irr::video::ITexture* textureWave       =  driver->getTexture("images/explosion/wave.bmp");

	// smoke renderer
	IRRQuadRenderer* smokeRenderer = IRRQuadRenderer::create(_device);
	//smokeRenderer->setTexturingMode(TEXTURE_2D);
	//
	smokeRenderer->setTexture( textureExplosion );
	//smokeRenderer->setTextureBlending(GL_MODULATE);
	smokeRenderer->setAtlasDimensions(2,2); // uses 4 different patterns in the texture
	smokeRenderer->setBlending(BLENDING_ALPHA);
	smokeRenderer->enableRenderingHint(DEPTH_WRITE,false);
	smokeRenderer->setShared(true);

	// flame renderer
	IRRQuadRenderer* flameRenderer = IRRQuadRenderer::create(_device);
//	flameRenderer->setTexturingMode(TEXTURE_2D);
	flameRenderer->setTexture( textureExplosion );
	// todo PB ici ptet ?
	//flameRenderer->setTextureBlending(GL_MODULATE);
	flameRenderer->setAtlasDimensions(2,2);
	flameRenderer->setBlending(BLENDING_ADD);
	flameRenderer->enableRenderingHint(DEPTH_WRITE,false);
	flameRenderer->setShared(true);

	// flash renderer
	IRRQuadRenderer* flashRenderer = IRRQuadRenderer::create(_device);
//	flashRenderer->setTexturingMode(TEXTURE_2D);
	flashRenderer->setTexture(textureFlash);
	//flashRenderer->setTextureBlending(GL_REPLACE);
	flashRenderer->setBlending(BLENDING_ADD);
	flashRenderer->enableRenderingHint(DEPTH_WRITE,false);
	flashRenderer->setShared(true);

	// spark 1 renderer
	IRRQuadRenderer* spark1Renderer = IRRQuadRenderer::create(_device);
//	spark1Renderer->setTexturingMode(TEXTURE_2D);
	spark1Renderer->setTexture(textureSpark1);
	//spark1Renderer->setTextureBlending(GL_REPLACE);
	spark1Renderer->setBlending(BLENDING_ADD);
	spark1Renderer->enableRenderingHint(DEPTH_WRITE,false);
	spark1Renderer->setOrientation(DIRECTION_ALIGNED); // sparks are oriented function o their velocity
	spark1Renderer->setScale(0.05f,1.0f); // thin rectangles
	spark1Renderer->setShared(true);

	// spark 2 renderer
	IRRRenderer* spark2Renderer = 0;
	// TODO creer l'equivalent irrlicht
	//disableFeature GL_ARB_point_sprite
//    COpenGLDriver* oglDriver = dynamic_cast<IVideoDriver*>(driver);
  //  oglDriver->
    //COpenGLExtensionHandler::queryFeature
    //queryOpenGLFeature(EOpenGLFeatures feature)
//    COpenGLExtensionHandler::queryOpenGLFeature(IRR_ARB_point_sprite)
//    queryOpenGLFeature(IRR_NV_point_sprite)
//    queryOpenGLFeature(IRR_SGIS_point_parameters)
//
     //queryOpenGLFeature(IRR_EXT_point_parameters)
//    bool PointSpriteLoaded = false;
//
//    if(irr::COpenGLExtensionHandler::queryOpenGLFeature(IRR_ARB_point_parameters)){
//        PointSpriteLoaded = true;
//    }

	//if (IRRPointRenderer::loadGLExtPointSprite() && IRRPointRenderer::loadGLExtPointParameter()) // uses point sprite if possible
 //irr::COpenGLExtensionHandler::queryOpenGLFeature
//queryOpenGLFeature
	if (1) // uses point sprite if possible
	{
		//IRRPointRenderer::setPixelPerUnit(45.0f * M_PI / 180.f,screenHeight);
		IRRPointRenderer* pointRenderer = IRRPointRenderer::create(_device);
//		pointRenderer->setType(POINT_SPRITE);
		pointRenderer->setTexture(textureSpark2);
//		//pointRenderer->setTextureBlending(GL_MODULATE);
//		pointRenderer->enableWorldSize(true);
		pointRenderer->setSize(0.02f);
		spark2Renderer = pointRenderer;
	}
	else
	{
		IRRQuadRenderer* quadRenderer = IRRQuadRenderer::create(_device);
		quadRenderer->setTexturingMode(TEXTURE_2D);
		quadRenderer->setTexture(textureSpark2);
		//quadRenderer->setTextureBlending(GL_MODULATE);
		quadRenderer->setScale(0.02f,0.02f);
		spark2Renderer = quadRenderer;
	}
	spark2Renderer->setBlending(BLENDING_ADD);
	spark2Renderer->enableRenderingHint(DEPTH_WRITE,false);
	spark2Renderer->setShared(true);

	// wave renderer
	IRRQuadRenderer* waveRenderer = IRRQuadRenderer::create(_device);
	waveRenderer->setTexturingMode(TEXTURE_2D);
	waveRenderer->setTexture(textureWave);
	//waveRenderer->setTextureBlending(GL_MODULATE);
	waveRenderer->setBlending(BLENDING_ALPHA);
	waveRenderer->enableRenderingHint(DEPTH_WRITE,false);
	waveRenderer->enableRenderingHint(ALPHA_TEST,true); // uses the alpha test
	waveRenderer->setAlphaTestThreshold(0.0f);
	waveRenderer->setOrientation(FIXED_ORIENTATION); // the orientatin is fixed
	waveRenderer->lookVector.set(0.0f,1.0f,0.0f);
	waveRenderer->upVector.set(1.0f,0.0f,0.0f); // we dont really care about the up axis
	waveRenderer->setShared(true);

	////////////
	// Models //
	////////////

	Interpolator* interpolator = NULL; // pointer to an interpolator that is used to retrieve interpolators

	// smoke model
	Model* smokeModel = Model::create(FLAG_RED | FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA | FLAG_SIZE | FLAG_ANGLE | FLAG_TEXTURE_INDEX,
		FLAG_SIZE | FLAG_ANGLE,
		FLAG_SIZE | FLAG_ANGLE | FLAG_TEXTURE_INDEX,
		FLAG_ALPHA);
	smokeModel->setParam(PARAM_RED,0.2f);
	smokeModel->setParam(PARAM_GREEN,0.2f);
	smokeModel->setParam(PARAM_BLUE,0.2f);
	smokeModel->setParam(PARAM_SIZE,0.6f,0.8f,1.0f,1.4f);
	smokeModel->setParam(PARAM_TEXTURE_INDEX,0.0f,4.0f);
	smokeModel->setParam(PARAM_ANGLE,0.0f, M_PI * 0.5f,0.0f, M_PI * 0.5f);
	smokeModel->setLifeTime(2.5f,3.0f);
	smokeModel->setShared(true);

	interpolator = smokeModel->getInterpolator(PARAM_ALPHA);
	interpolator->addEntry(0.0f,0.0f);
	interpolator->addEntry(0.4f,0.4f,0.6f);
	interpolator->addEntry(0.6f,0.4f,0.6f);
	interpolator->addEntry(1.0f,0.0f);

	// flame model
	Model* flameModel = Model::create(FLAG_RED | FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA | FLAG_SIZE | FLAG_ANGLE | FLAG_TEXTURE_INDEX,
		FLAG_ANGLE | FLAG_RED | FLAG_GREEN | FLAG_BLUE,
		FLAG_ANGLE | FLAG_TEXTURE_INDEX,
		FLAG_SIZE | FLAG_ALPHA);
	flameModel->setParam(PARAM_RED,1.0f,0.2f);
	flameModel->setParam(PARAM_GREEN,0.5f,0.2f);
	flameModel->setParam(PARAM_BLUE,0.2f,0.2f);
	flameModel->setParam(PARAM_TEXTURE_INDEX,0.0f,4.0f);
	flameModel->setParam(PARAM_ANGLE,0.0f,M_PI * 0.5f,0.0f,M_PI * 0.5f);
	flameModel->setLifeTime(1.5f,2.0f);
	flameModel->setShared(true);

	interpolator = flameModel->getInterpolator(PARAM_SIZE);
	interpolator->addEntry(0.0f,0.25f);
	interpolator->addEntry(0.02f,0.6f,0.8f);
	interpolator->addEntry(1.0f,1.0f,1.4f);

	interpolator = flameModel->getInterpolator(PARAM_ALPHA);
	interpolator->addEntry(0.5f,1.0f);
	interpolator->addEntry(1.0f,0.0f);

	// flash model
	Model* flashModel = Model::create(FLAG_ALPHA | FLAG_SIZE | FLAG_ANGLE,
		FLAG_NONE,
		FLAG_ANGLE,
		FLAG_ALPHA | FLAG_SIZE);
	flashModel->setParam(PARAM_ANGLE,0.0f,2.0f * M_PI);
	flashModel->setLifeTime(0.5f,0.5f);
	flashModel->setShared(true);

	interpolator = flashModel->getInterpolator(PARAM_SIZE);
	interpolator->addEntry(0.0f,0.25f);
	interpolator->addEntry(0.1f,1.0f,2.0f);

	interpolator = flashModel->getInterpolator(PARAM_ALPHA);
	interpolator->addEntry(0.0f,1.0f);
	interpolator->addEntry(0.4f,0.0f);

	// spark 1 model
	Model* spark1Model = Model::create(FLAG_SIZE | FLAG_ALPHA,
		FLAG_ALPHA,
		FLAG_SIZE);
	spark1Model->setParam(PARAM_ALPHA,1.0f,0.0f);
	spark1Model->setParam(PARAM_SIZE,0.2f,0.4f);
	spark1Model->setLifeTime(0.2f,1.0f);
	spark1Model->setShared(true);

	// spark 2 model
	Model* spark2Model = Model::create(FLAG_RED | FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA,
		FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA,
		FLAG_GREEN);
	spark2Model->setParam(PARAM_ALPHA,1.0f,0.0f);
	spark2Model->setParam(PARAM_RED,1.0f);
	spark2Model->setParam(PARAM_GREEN,1.0f,1.0f,0.3f,1.0f);
	spark2Model->setParam(PARAM_BLUE,0.7f,0.3f);
	spark2Model->setLifeTime(1.0f,3.0f);
	spark2Model->setShared(true);

	// wave model
	Model* waveModel = Model::create(FLAG_ALPHA | FLAG_SIZE,
		FLAG_SIZE | FLAG_ALPHA);
	waveModel->setParam(PARAM_SIZE,0.0f,4.0f);
	waveModel->setParam(PARAM_ALPHA,0.2f,0.0f);
	waveModel->setLifeTime(0.8f,0.8f);
	waveModel->setShared(true);

	//////////////
	// Emitters //
	//////////////

	// This zone will be used by several emitters
	Sphere* explosionSphere = Sphere::create(Vector3D(0.0f,0.0f,0.0f),0.4f);

	// smoke emitter
	RandomEmitter* smokeEmitter = RandomEmitter::create();
	smokeEmitter->setZone(Sphere::create(Vector3D(0.0f,0.0f,0.0f),0.6f),false);
	smokeEmitter->setFlow(-1);
	smokeEmitter->setTank(15);
	smokeEmitter->setForce(0.02f,0.04f);

	// flame emitter
	NormalEmitter* flameEmitter = NormalEmitter::create();
	flameEmitter->setZone(explosionSphere);
	flameEmitter->setFlow(-1);
	flameEmitter->setTank(15);
	flameEmitter->setForce(0.06f,0.1f);

	// flash emitter
	StaticEmitter* flashEmitter = StaticEmitter::create();
	flashEmitter->setZone(Sphere::create(Vector3D(0.0f,0.0f,0.0f),0.1f));
	flashEmitter->setFlow(-1);
	flashEmitter->setTank(3);

	// spark 1 emitter
	NormalEmitter* spark1Emitter = NormalEmitter::create();
	spark1Emitter->setZone(explosionSphere);
	spark1Emitter->setFlow(-1);
	spark1Emitter->setTank(20);
	spark1Emitter->setForce(2.0f,3.0f);

	// spark 2 emitter
	NormalEmitter* spark2Emitter = NormalEmitter::create();
	spark2Emitter->setZone(explosionSphere);
	spark2Emitter->setFlow(-1);
	spark2Emitter->setTank(400);
	spark2Emitter->setForce(0.4f,0.8f);

	// wave emitter
	StaticEmitter* waveEmitter = StaticEmitter::create();
	waveEmitter->setZone(Point::create());
	waveEmitter->setFlow(-1);
	waveEmitter->setTank(1);

	////////////
	// Groups //
	////////////

	// smoke group
	Group* smokeGroup = Group::create(smokeModel,15);
	smokeGroup->addEmitter(smokeEmitter);
	smokeGroup->setRenderer(smokeRenderer);
	smokeGroup->setGravity(Vector3D(0.0f,0.05f,0.0f));

	// flame group
	Group* flameGroup = Group::create(flameModel,15);
	flameGroup->addEmitter(flameEmitter);
	flameGroup->setRenderer(flameRenderer);

	// flash group
	Group* flashGroup = Group::create(flashModel,3);
	flashGroup->addEmitter(flashEmitter);
	flashGroup->setRenderer(flashRenderer);

	// spark 1 group
	Group* spark1Group = Group::create(spark1Model,20);
	spark1Group->addEmitter(spark1Emitter);
	spark1Group->setRenderer(spark1Renderer);
	spark1Group->setGravity(Vector3D(0.0f,-1.5f,0.0f));

	// spark 2 group
	Group* spark2Group = Group::create(spark2Model,400);
	spark2Group->addEmitter(spark2Emitter);
	spark2Group->setRenderer(spark2Renderer);
	spark2Group->setGravity(Vector3D(0.0f,-0.3f,0.0f));
	spark2Group->setFriction(0.4f);

	// wave group
	Group* waveGroup = Group::create(waveModel,1);
	waveGroup->addEmitter(waveEmitter);
	waveGroup->setRenderer(waveRenderer);

	////////////
	// System //
	////////////
//_device->getSceneManager()->getRootSceneNode()
//IRRSystem(null,device->getSceneManager(),false);
/// TODO HACK
/// le false permet de se retrouver en coordonnes SPARK => scale
/// cf http://spark.forum0.net/t90-irrsystem-scale-doesn-t-work
///
	IRRSystem* system = IRRSystem::create( 0,_device->getSceneManager(), false );
	system->addGroup(waveGroup);
	system->addGroup(smokeGroup);
	system->addGroup(flameGroup);
	system->addGroup(flashGroup);
	system->addGroup(spark1Group);
	system->addGroup(spark2Group);

	// Gets a pointer to the base const
    typedef SPK_ID (SPK::Registerable::*SPK_getID)(void);
    // ( SPK_getID )
	_explosionID = system->SPK::Registerable::getID();

	//return ;

	//particleSystems.sort(cmpDistToCam);
}



void
CParticleManager::update()
{

//    BOOST_FOREACH(IRRSystem* system,_systems){
//
//        if( system->hasFinished() ) {
//            system->remove();
//        }
//    }

}


//irr::scene::ISceneNode* parentNode
void
CParticleManager::createBaseBooster()
{

//_device->getSceneManager()->getRootSceneNode()
//_device->getSceneManager()->getRootSceneNode()
    IRRSystem* system = IRRSystem::create( 0 ,_device->getSceneManager() );
    video::ITexture* texture = _device->getVideoDriver()->getTexture("images/explosion/point.bmp");

	IRRQuadRenderer* particleRenderer = IRRQuadRenderer::create(_device);
	particleRenderer->setTexture( texture );
	//particleRenderer->setTexturingMode(TEXTURE_2D);
	particleRenderer->setScale(0.2f,0.2f);
	particleRenderer->setBlending(BLENDING_ADD);
	particleRenderer->enableRenderingHint(DEPTH_WRITE,false);

	// enabled/mutable/random/interpolate
	//| FLAG_RED
	Model* particleModel = Model::create(
                            FLAG_RED | FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA,
                             FLAG_ALPHA | FLAG_BLUE | FLAG_GREEN | FLAG_RED,                          //mutable
                            FLAG_NONE,                          //random
                            FLAG_ALPHA | FLAG_BLUE | FLAG_GREEN | FLAG_RED // interpolated
                            );
	particleModel->setParam(PARAM_ALPHA,0.8f,0.2f); // constant alpha
//	particleModel->setParam(PARAM_GREEN,0.3f, 0.8f); // constant alpha
	//particleModel->setParam(PARAM_BLUE,0.8f,0.3f); // constant alpha
	//particleModel->setParam(PARAM_RED,0.3f,0.8f); // constant alpha
	particleModel->setLifeTime(1.f,2.f);

    Interpolator* interpolator = particleModel->getInterpolator(PARAM_ALPHA);
//	interpolator->addEntry(0.0f,0.0f);
//	interpolator->addEntry(0.2f,0.2f);
	//interpolator->addEntry(1.0f,0.0f);



	// Emitter
	StraightEmitter* particleEmitter = StraightEmitter::create();

//create (const Vector3D &position=Vector3D(0.0f, 0.0f, 0.0f), const Vector3D &normal=Vector3D(0.0f, 1.0f, 0.0f), float minRadius=0.0f, float maxRadius=1.0f)
	// normale du ring
	// pos/normal/min radius/max radius
	Ring* ring = Ring::create(Vector3D(0.0f, 0.0f, 0.0f), Vector3D( 0.0f,1.0f, 0.0f), 0.4f, 0.6f  );
	particleEmitter->setZone( ring );
	particleEmitter->setFlow(300);  // nb de particules par unite de temps donne
	particleEmitter->setDirection( Vector3D(0,1.0f,0.0f) );
	particleEmitter->setForce(1.5f,2.f);




	// Create new modifier
    // to attract particles
    PointMass* trapper = new PointMass 	(
        Ring::create(Vector3D(0.0f, 0.0f, 0.0f), Vector3D( 0.0f,1.0f, 0.0f), 0.4f, 0.6f  ),
		//INSIDE_ZONE,            // trigger
		ALWAYS,
		1.0f,    // mass
		0.05f     // minDistance
	);
	//Utiliser irr2spk() pr convertir vecteur
	// force min /max




	// particle group 2nd param = capacite du pool
	Group* particleGroup = Group::create(particleModel,2100);
	particleGroup->addEmitter(particleEmitter);
	particleGroup->setRenderer(particleRenderer);
	particleGroup->addModifier(trapper);


	particleGroup->enableAABBComputing(true);

    //system->setParent(parentNode);
	system->addGroup(particleGroup);
    system->setAutoUpdateEnabled(true,true);



    _boosterID = system->SPK::Registerable::getID();

    //


	//return system;
}



// Creates a particle system from the base system
//const Vector3D& pos
IRRSystem*
CParticleManager::createExplosion(const bool& autoremove)
{
	// Creates a copy of the base system
	IRRSystem* system = SPK_Copy(IRRSystem,_explosionID);

	// Locates the system at the given position
	//system->setTransformPosition(pos);
	//system->updateTransform(); // updates the world transform of system and its children
    if(autoremove){
        // add it to
        registerSystem(system);
    }
	return system;
}



IRRSystem*
CParticleManager::createBooster(const bool& autoremove)
{
	// Creates a copy of the base system
	IRRSystem* system = SPK_Copy(IRRSystem,_boosterID);

	// Locates the system at the given position
	//system->setTransformPosition(pos);
	//system->updateTransform(); // updates the world transform of system and its children
    if(autoremove){
        // add it to
        registerSystem(system);
    }
	return system;
}



void
CParticleManager::registerSystem(IRRSystem* particleSystem){

	//particleSystem->addGroup(particleGroup);
	//particleSystem->enableAABBComputing(true);
	// pareil que verifier hasFinished
	particleSystem->setDestroyable(true);
	//_systems.push_back(particleSystem);
}


CParticleManager::~CParticleManager()
{
	//cout << "\nSPARK FACTORY BEFORE DESTRUCTION :" << endl;
	//SPKFactory::getInstance().traceAll();
	//SPKFactory::getInstance().destroyAll();
	//cout << "\nSPARK FACTORY AFTER DESTRUCTION :" << endl;
	//SPKFactory::getInstance().traceAll();
}

