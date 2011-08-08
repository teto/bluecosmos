  stringw a(""); //a string in wich we store the result.

   if(driver->queryFeature(EVDF_RENDER_TO_TARGET))
      a+="YES: EVDF_RENDER_TO_TARGET\n";
   else
      a+="NO:  EVDF_RENDER_TO_TARGET\n";

   if(driver->queryFeature(EVDF_HARDWARE_TL))
      a+="YES: EVDF_HARDWARE_TL \n";
   else
      a+="NO:  EVDF_HARDWARE_TL \n";

   if(driver->queryFeature(EVDF_MULTITEXTURE))
      a+="YES: EVDF_MULTITEXTURE\n";
   else
      a+="NO:  EVDF_MULTITEXTURE\n";

   if(driver->queryFeature(EVDF_BILINEAR_FILTER))
      a+="YES: EVDF_BILINEAR_FILTER\n";
   else
      a+="NO:  EVDF_BILINEAR_FILTER\n";

   if(driver->queryFeature(EVDF_MIP_MAP))
      a+="YES: EVDF_MIP_MAP\n";
   else
      a+="NO:  EVDF_MIP_MAP\n";

   if(driver->queryFeature(EVDF_MIP_MAP_AUTO_UPDATE))
      a+="YES: EVDF_MIP_MAP_AUTO_UPDATE\n";
   else
      a+="NO:  EVDF_MIP_MAP_AUTO_UPDATE\n";

   if(driver->queryFeature(EVDF_STENCIL_BUFFER))
      a+="YES: EVDF_STENCIL_BUFFER\n";
   else
      a+="NO:  EVDF_STENCIL_BUFFER\n";

   if(driver->queryFeature( EVDF_VERTEX_SHADER_1_1 ))
      a+="YES: EVDF_VERTEX_SHADER_1_1\n";
   else
      a+="NO:  EVDF_VERTEX_SHADER_1_1\n";

   if(driver->queryFeature( EVDF_VERTEX_SHADER_2_0  ))
      a+="YES: EVDF_VERTEX_SHADER_2_0 \n";
   else
      a+="NO:  EVDF_VERTEX_SHADER_2_0 \n";

   if(driver->queryFeature(  EVDF_VERTEX_SHADER_3_0))
      a+="YES: EVDF_VERTEX_SHADER_3_0\n";
   else
      a+="NO:  EVDF_VERTEX_SHADER_3_0\n";

   if(driver->queryFeature(EVDF_PIXEL_SHADER_1_1 ))
      a+="YES: EVDF_PIXEL_SHADER_1_1\n";
   else
      a+="NO:  EVDF_PIXEL_SHADER_1_1\n";

   if(driver->queryFeature( EVDF_PIXEL_SHADER_1_2 ))
      a+="YES: EVDF_PIXEL_SHADER_1_2\n";
   else
      a+="NO:  EVDF_PIXEL_SHADER_1_2\n";

   if(driver->queryFeature( EVDF_PIXEL_SHADER_1_3 ))
      a+="YES: EVDF_PIXEL_SHADER_1_3\n";
   else
      a+="NO:  EVDF_PIXEL_SHADER_1_3\n";

   if(driver->queryFeature(EVDF_PIXEL_SHADER_1_4  ))
      a+="YES: EVDF_PIXEL_SHADER_1_4\n";
   else
      a+="NO:  EVDF_PIXEL_SHADER_1_4\n";

   if(driver->queryFeature( EVDF_PIXEL_SHADER_2_0 ))
      a+="YES: EVDF_PIXEL_SHADER_2_0\n";
   else
      a+="NO:  EVDF_PIXEL_SHADER_2_0\n";

   if(driver->queryFeature( EVDF_PIXEL_SHADER_3_0 ))
      a+="YES: EVDF_PIXEL_SHADER_3_0\n";
   else
      a+="NO:  EVDF_PIXEL_SHADER_3_0\n";

   if(driver->queryFeature(EVDF_ARB_VERTEX_PROGRAM_1  ))
      a+="YES: EVDF_ARB_VERTEX_PROGRAM_1\n";
   else
      a+="NO:  EVDF_ARB_VERTEX_PROGRAM_1\n";

   if(driver->queryFeature( EVDF_ARB_FRAGMENT_PROGRAM_1 ))
      a+="YES: EVDF_ARB_FRAGMENT_PROGRAM_1\n";
   else
      a+="NO:  EVDF_ARB_FRAGMENT_PROGRAM_1\n";

   if(driver->queryFeature( EVDF_ARB_GLSL ))
      a+="YES: EVDF_ARB_GLSL\n";
   else
      a+="NO:  EVDF_ARB_GLSL\n";

   if(driver->queryFeature( EVDF_HLSL ))
      a+="YES: EVDF_HLSL\n";
   else
      a+="NO:  EVDF_HLSL\n";

   if(driver->queryFeature(EVDF_TEXTURE_NSQUARE  ))
      a+="YES: EVDF_TEXTURE_NSQUARE\n";
   else
      a+="NO:  EVDF_TEXTURE_NSQUARE\n";

   if(driver->queryFeature( EVDF_TEXTURE_NPOT ))
      a+="YES: EVDF_TEXTURE_NPOT\n";
   else
      a+="NO:  EVDF_TEXTURE_NPOT\n";

   if(driver->queryFeature( EVDF_FRAMEBUFFER_OBJECT ))
      a+="YES: EVDF_FRAMEBUFFER_OBJECT\n";
   else
      a+="NO:  EVDF_FRAMEBUFFER_OBJECT\n";

   if(driver->queryFeature( EVDF_VERTEX_BUFFER_OBJECT ))
      a+="YES: EVDF_VERTEX_BUFFER_OBJECT\n";
   else
      a+="NO:  EVDF_VERTEX_BUFFER_OBJECT\n";

   if(driver->queryFeature( EVDF_ALPHA_TO_COVERAGE ))
      a+="YES: EVDF_ALPHA_TO_COVERAGE\n";
   else
      a+="NO:  EVDF_ALPHA_TO_COVERAGE\n";

   if(driver->queryFeature( EVDF_COLOR_MASK ))
      a+="YES: EVDF_COLOR_MASK\n";
   else
      a+="NO:  EVDF_COLOR_MASK\n";

   if(driver->queryFeature( EVDF_MULTIPLE_RENDER_TARGETS ))
      a+="YES: EVDF_MULTIPLE_RENDER_TARGETS\n";
   else
      a+="NO:  EVDF_MULTIPLE_RENDER_TARGETS\n";

   if(driver->queryFeature( EVDF_MRT_BLEND ))
      a+="YES: EVDF_MRT_BLEND\n";
   else
      a+="NO:  EVDF_MRT_BLEND\n";

   if(driver->queryFeature( EVDF_MRT_COLOR_MASK ))
      a+="YES: EVDF_MRT_COLOR_MASK\n";
   else
      a+="NO:  EVDF_MRT_COLOR_MASK\n";




   guienv->addStaticText((wchar_t*) a.c_str(),
      rect<s32>(10,10,260,400), true);
