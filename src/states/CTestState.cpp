/**
generer aleatoirement lesnuages
splatting

http://www.fmod.org/forum/viewtopic.php?p=38351&sid=a95521d982ce6812f6f22c89c8c15682
http://www.fmod.org/forum/viewtopic.php?p=36949&sid=6fa6cdbd0ac7cfc056e5cc74a36ca767
*/



#define DT 0.01

/**** Function Init() ****/
bool CTestState::Init(){


    return true;
}


//! Render a frame
void
CTestState::Draw(CGameEngine *game){

	// Terrain pager parameters
	STerrainParameters param2;
	param2.MapSize = 256;							// size of terrain-1 => 256 is ideal for quality/speed
	param2.Dimension = core::dimension2di(4,4);		// tiles organisation (4x4 square)
	param2.LodTextureScale = 100.0f;				// detail texture scale
	param2.MapListFileName = listeMap;				// heightmaps list
	param2.ColorMapListFileName = colorMap;			// colormap list
	param2.Position = core::vector3df(0,0,0);		// first terrain position
	param2.Scale = core::vector3df(10,10,10);		// terrain scale
	param2.Quality = CTerrain::ETQ_MEDIUM;			// terrain quality
	param2.DistanceMaxRender = 180.0f;				// max render distance, ideal tweek between 100-250
	param2.DistanceLoad = param2.MapSize * 1.38f * param2.Scale.X;		// +38% of map size
	param2.DistanceUnload = param2.DistanceLoad * 1.05f;	// +5% of load distance
	param2.Fog = true;								// use fog
	param2.Debug = true;							// show bounding box for terrain tiles

	// create Terrain pager
	CTerrainPager * terrPag = new  CTerrainPager(param2, smgr->getRootSceneNode(), smgr, 0);

	// set fog
	f32 minFog = 400;
	f32 maxFog = param2.DistanceMaxRender * param2.Scale.X * 0.85f;
	video::SColor fogColor = video::SColor(0,150,150,255);
	driver->setFog(fogColor, true, minFog, maxFog);

}


/*
Brouillard

Il est relativement facile de créer un effet de brouillard avec OpenGL. En effet, le rendu utilise la notion de profondeur (distance d’un objet à l’observateur) pour le rendu. En ‘mixant’ la couleur d’un objet avec une couleur ‘du brouillard’ en fonction de la distance (plus l’objet est éloigné, plus la couleur de fond est prépondérante), on crée un joli brouillard.

L’activation et la désactivation du brouillard se fait respectivement avec glEnable(GL_FOG) et glDisable(GL_FOG). La modification des paramètres du brouillard se fait avec la fonction

glFogf(GLenum nomparam,Glfloat valeur)

‘paramètre’ est le nom du paramètre à modifier, et ‘valeur’ est évidemment la nouvelle valeur du paramètre. Il existe plusieurs modes de brouillard, correspondant à différentes fonctions de mélange de la couleur de l’objet et de la couleur du brouillard. Je ne vais pas détailler tous les modes aujourd’hui (vous trouverez tout ça dans le livre [1]), je vous livre simplement les paramètres utilisés pour le programme exemple. Il s’agit d’un brouillard de type exponentiel :

glFogi(GL_FOG_MODE,GL_EXP); // Réglage du type de brouillard
glFogfv(GL_FOG_COLOR,couleurAP); // Couleur du brouillard, généralement la identique à la couleur de fond définie avec glClearColor()
glFogf(GL_FOG_START,0); //distance de début du brouillard (relativement à l’observateur)
glFogf(GL_FOG_END,15); // distance de fin du brouillard
glFogf(GL_FOG_DENSITY,0.35); // Densité du brouillard
*/



/**** Function HandleEvents() ****/
bool
CTestState::OnEvent(const irr::SEvent&);

//static sf::Mouse::Button button;
#if 0
    switch (event.Type){

            case sf::Event::KeyPressed:
                switch (event.Key.Code){
                    //go forward
                    case sf::Key::W:
                        mFogDepth -= 0.1f;
                        break;
                    case sf::Key::X:
                        mFogDepth += 0.1f;
                        break;
                    case sf::Key::V:
                        SWITCH(mDrawSkeleton);
                        break;

                    case sf::Key::R:
                        mPlayer->UpgradeMode(EPlus);
                        std::cout << "Mode Up" << std::endl;
                        break;

                    case sf::Key::F5:

                        SWITCH(mDrawModel);
                         std::cout << "Draw normals switched" << std::endl;
                        break;

                    case sf::Key::T:
                        mPlayer->UpgradeMode(EMinus);
                        std::cout << "Mode down" << std::endl;
                        break;
                    default:
                        break;
                }
            default:
                break;
    }
    #endif
}

/*
Penser à mettre le background de la couleur du brouillard :
ainsi, l’effet sera plus frappant. La commande correspondante est  :
glClearColor(couleur_brouillard[0],couleur_brouillard[1],couleur_brouillard[2],couleur_brouillard[3]);
*/
/*glEnable(GL_FOG) ;
GLfloat fogcolor[4] = {0.5, 0.5, 0.5, 1} ;
GLint fogmode = GL_LINEAR ;
glFogi (GL_FOG_MODE, fogmode) ;
glFogfv(GL_FOG_COLOR, fogcolor) ;
glFogf(GL_FOG_DENSITY, mFogDepth) ;
glFogf(GL_FOG_START, 3.f) ;
glFogf(GL_FOG_END, 4.f) ;
//glDisable(GL_FOG) ;*/
/**** Function Update() ****/
//Data will range is 0.0 to 1.0.
void CTestState::Update(){


}





