
//Affihcer le mesh / le monde derriere / skybox
#if 0
video::S3DVertex vertices[6];
    vertices[0].TCoords = core::vector2df(1.0f, .1f);
    vertices[5].Pos = core::vector3df(0.f,0.f,0.1);
    vertices[4].Pos = core::vector3df(0,20,0.1);
    vertices[3].Pos = core::vector3df(3,25,0.1);
    vertices[2].Pos = core::vector3df(100,25,0.1);
    vertices[1].Pos = core::vector3df(100,5,0.1);
    vertices[0].Pos = core::vector3df(97,0,0.1);

    short int index[6];
    for(unsigned int i=0; i<6; i++)
    {
        index[i]=i;
        vertices[i].Color = video::SColor(30, 255, 255, 255);
    }

SMaterial material;
material.MaterialType =  EMT_TRANSPARENT_REFLECTION_2_LAYER;
//device->getLogger()->log(material.isTransparent (),ELL_INFORMATION);
driver->setMaterial(material);
//guienv->setMaterial(material);
//updateHoveredElement

    driver->draw2DVertexPrimitiveList  ( vertices,
      6,//6 vertices
      index,//const void *  indexList,
      6,//u32  primCount,
      EVT_STANDARD,
       scene::EPT_POLYGON
     );

#endif
