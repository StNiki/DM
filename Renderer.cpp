//----------------------------------------------------//
//                                                    //
// File: Renderer.cpp                                 //
// Initialization, rendering and input handling		  //
// happens here										  //
//                                                    //
// Author:                                            //
// Kostas Vardis                                      //
//                                                    //
// These files are provided as part of the BSc course //
// of Computer Graphics at the Athens University of   //
// Economics and Business (AUEB)					  //
//                                                    //
//----------------------------------------------------//

#include "HelpLib.h"		// - Library for including GL libraries, checking for OpenGL errors, writing to Output window, etc.

#include "OBJ/OBJLoader.h"	// - Header file for the OBJ Loader
#include "OBJ/OGLMesh.h"	// - Header file for the OGL mesh
#include "ShaderGLSL.h"		// - Header file for GLSL objects
#include "Light.h"			// - Header file for Lights
#include "Shaders.h"		// - Header file for all the shaders
#include "Renderer.h"		// - Header file for our OpenGL functions
#include "../Source/Player.h"
#include "SceneGraph/Root.h"
#include "SceneGraph/TransformNode.h"
#include "SceneGraph/GroupNode.h"
#include "SceneGraph/GeometryNode.h"

// window settings
float current_width;
float current_height;

// camera parameters
glm::vec3 start = glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 eye = glm::vec3(0.0f, 1.6f, 1.5f);
glm::vec3 target = glm::vec3(0.0f, 1.2f, -3.0f);
glm::vec3 up;

Player* myPlayer = new Player("IronWarrior",start,eye,target);

// transformation matrices
glm::mat4x4 world_to_camera_matrix;
glm::mat4x4 perspective_projection_matrix;

// Mouse button and coords
int mouse_button = -1;
int prev_x = 0;
int prev_y = 0;
float wheelcap = 2.5f;

// World Rotation
float world_rotate_x = 0;
float world_rotate_y = 0;
glm::vec3 world_translate;
float door_rotangle = 0.0f;
float door_rotangle2 = 0.0f;
float door_rotangle3 = 0.0f;
float door_rotangle4 = 0.0f;
float door_rotangle5 = 0.0f;
float door_rotangle6 = 0.0f;
float door_rotangle7 = 0.0f;
float door_rotangle8 = 0.0f;
float totem_rotangle = 0.0f;
float arrowpos = -13.5f;
float arrowpos2 = -13.5f;
int thrownL = 0;
int thrownR = 0;
float arrowpos21 = 5.0f;
float arrowpos22 = 5.0f;
int thrownL2 = 0;
int thrownR2 = 0;
float arrowpos31 = 2.5f;
float arrowpos32 = 2.5f;
int thrownL3 = 0;
int thrownR3 = 0;
float arrowpos41 = 5.0f;
float arrowpos42 = 5.0f;
int thrownL4 = 0;
int thrownR4 = 0;
float arrowdistX;
float arrowdistX2;
float arrowdistX21;
float arrowdistX22;
float arrowdistX31;
float arrowdistX32;
float arrowdistX41;
float arrowdistX42;
float arrowdistZ;
float arrowdistZ2;
float arrowdistZ21;
float arrowdistZ22;
float arrowdistZ31;
float arrowdistZ32;
float arrowdistZ41;
float arrowdistZ42;
float door_dist;
float door_dist2;
float door_dist3;
float door_dist4;
float door_dist5;
float door_dist6;
float door_dist7;
float door_dist8;
float spikespos = 0.0f;

// Rendering mode
int rendering_mode = GL_FILL;

// OBJ models
OGLMesh* groundwhiteMesh;
OGLMesh* spherewhiteMesh;
//
OGLMesh* roomSmallMesh;
OGLMesh* roomMediumMesh;
//
OGLMesh* corridorMediumMesh;
OGLMesh* corridorNarrowMesh;
OGLMesh* corridorWideMesh;
OGLMesh* corridorMediumCrossMesh;
OGLMesh* corridorNarrowCrossMesh;
OGLMesh* corridorMediumTJMesh;
OGLMesh* corridorNarrowTJMesh;
OGLMesh* corridorMediumTurnMesh;
OGLMesh* corridorNarrowTurnMesh;
OGLMesh* corridorWideTurnMesh;
//
OGLMesh* hallMesh;
//
OGLMesh* wallHalf1Mesh;
OGLMesh* wall1Mesh;
//
OGLMesh* doorMesh;
OGLMesh* doorSideMesh;
OGLMesh* doorExteMesh;
//
OGLMesh* columnMesh;
OGLMesh* pillar1Mesh;
OGLMesh* arrowMesh;
OGLMesh* dragonMesh;
OGLMesh* pedestalMesh;
OGLMesh* spikesMesh;
OGLMesh* trapMesh;
OGLMesh* bloodMesh;
OGLMesh* wellMesh;
OGLMesh* totemMesh;
OGLMesh* floortiles1Mesh;
OGLMesh* floortiles2Mesh;
OGLMesh* floortiles3Mesh;
//
OGLMesh* warriorMesh;

// Scene graph nodes
Root* root;
Root* root2;

TransformNode* world_transform;
TransformNode* ground_transform;
GeometryNode* ground_geom;

//rooms
TransformNode* roomMedium_transform;
GeometryNode* roomMedium_geom;
TransformNode* roomSmall_transform;
GeometryNode* roomSmall_geom;
TransformNode* roomMedium_transform2;
GeometryNode* roomMedium_geom2;
TransformNode* roomSmall_transform2;
GeometryNode* roomSmall_geom2;

//corridors
TransformNode* corridorMedium_transform;
GeometryNode* corridorMedium_geom;
TransformNode* corridorMedium_transform2;
GeometryNode* corridorMedium_geom2;
TransformNode* corridorMedium_transform3;
GeometryNode* corridorMedium_geom3;
TransformNode* corridorMedium_transform4;
GeometryNode* corridorMedium_geom4;
TransformNode* corridorMedium_transform5;
GeometryNode* corridorMedium_geom5;
TransformNode* corridorMedium_transform6;
GeometryNode* corridorMedium_geom6;
TransformNode* corridorMedium_transform7;
GeometryNode* corridorMedium_geom7;
TransformNode* corridorMedium_transform8;
GeometryNode* corridorMedium_geom8;
TransformNode* corridorMedium_transform9;
GeometryNode* corridorMedium_geom9;
TransformNode* corridorMedium_transform10;
GeometryNode* corridorMedium_geom10;
TransformNode* corridorMedium_transform11;
GeometryNode* corridorMedium_geom11;
TransformNode* corridorMedium_transform12;
GeometryNode* corridorMedium_geom12;
TransformNode* corridorMedium_transform13;
GeometryNode* corridorMedium_geom13;
TransformNode* corridorMedium_transform14;
GeometryNode* corridorMedium_geom14;
TransformNode* corridorMedium_transform15;
GeometryNode* corridorMedium_geom15;
TransformNode* corridorMedium_transform16;
GeometryNode* corridorMedium_geom16;
TransformNode* corridorMedium_transform17;
GeometryNode* corridorMedium_geom17;
TransformNode* corridorMedium_transform18;
GeometryNode* corridorMedium_geom18;
TransformNode* corridorMedium_transform19;
GeometryNode* corridorMedium_geom19;

TransformNode* corridorNarrow_transform;
GeometryNode* corridorNarrow_geom;
TransformNode* corridorNarrow_transform2;
GeometryNode* corridorNarrow_geom2;
TransformNode* corridorNarrow_transform3;
GeometryNode* corridorNarrow_geom3;
TransformNode* corridorNarrow_transform4;
GeometryNode* corridorNarrow_geom4;
TransformNode* corridorNarrow_transform5;
GeometryNode* corridorNarrow_geom5;
TransformNode* corridorNarrow_transform6;
GeometryNode* corridorNarrow_geom6;
TransformNode* corridorNarrow_transform7;
GeometryNode* corridorNarrow_geom7;
TransformNode* corridorNarrow_transform8;
GeometryNode* corridorNarrow_geom8;
TransformNode* corridorNarrow_transform9;
GeometryNode* corridorNarrow_geom9;
TransformNode* corridorNarrow_transform10;
GeometryNode* corridorNarrow_geom10;
TransformNode* corridorNarrow_transform11;
GeometryNode* corridorNarrow_geom11;
TransformNode* corridorNarrow_transform12;
GeometryNode* corridorNarrow_geom12;
TransformNode* corridorNarrow_transform13;
GeometryNode* corridorNarrow_geom13;
TransformNode* corridorNarrow_transform14;
GeometryNode* corridorNarrow_geom14;
TransformNode* corridorNarrow_transform15;
GeometryNode* corridorNarrow_geom15;
TransformNode* corridorNarrow_transform16;
GeometryNode* corridorNarrow_geom16;
TransformNode* corridorNarrow_transform17;
GeometryNode* corridorNarrow_geom17;
TransformNode* corridorNarrow_transform18;
GeometryNode* corridorNarrow_geom18;
TransformNode* corridorNarrow_transform19;
GeometryNode* corridorNarrow_geom19;
TransformNode* corridorNarrow_transform20;
GeometryNode* corridorNarrow_geom20;
TransformNode* corridorNarrow_transform21;
GeometryNode* corridorNarrow_geom21;
TransformNode* corridorNarrow_transform22;
GeometryNode* corridorNarrow_geom22;

TransformNode* corridorWide_transform;
GeometryNode* corridorWide_geom;
TransformNode* corridorMediumCross_transform;
GeometryNode* corridorMediumCross_geom;
TransformNode* corridorNarrowCross_transform;
GeometryNode* corridorNarrowCross_geom;
TransformNode* corridorMediumTJ_transform;
GeometryNode* corridorMediumTJ_geom;

TransformNode* corridorNarrowTJ_transform;
GeometryNode* corridorNarrowTJ_geom;
TransformNode* corridorNarrowTJ_transform2;
GeometryNode* corridorNarrowTJ_geom2;

TransformNode* corridorMediumTurn_transform;
GeometryNode* corridorMediumTurn_geom;
TransformNode* corridorMediumTurn_transform2;
GeometryNode* corridorMediumTurn_geom2;
TransformNode* corridorMediumTurn_transform3;
GeometryNode* corridorMediumTurn_geom3;
TransformNode* corridorMediumTurn_transform4;
GeometryNode* corridorMediumTurn_geom4;
TransformNode* corridorMediumTurn_transform5;
GeometryNode* corridorMediumTurn_geom5;
TransformNode* corridorMediumTurn_transform6;
GeometryNode* corridorMediumTurn_geom6;

TransformNode* corridorNarrowTurn_transform;
GeometryNode* corridorNarrowTurn_geom;
TransformNode* corridorNarrowTurn_transform2;
GeometryNode* corridorNarrowTurn_geom2;
TransformNode* corridorNarrowTurn_transform3;
GeometryNode* corridorNarrowTurn_geom3;
TransformNode* corridorNarrowTurn_transform4;
GeometryNode* corridorNarrowTurn_geom4;
TransformNode* corridorNarrowTurn_transform5;
GeometryNode* corridorNarrowTurn_geom5;
TransformNode* corridorNarrowTurn_transform6;
GeometryNode* corridorNarrowTurn_geom6;
TransformNode* corridorNarrowTurn_transform7;
GeometryNode* corridorNarrowTurn_geom7;

TransformNode* corridorWideTurn_transform;
GeometryNode* corridorWideTurn_geom;
TransformNode* corridorWideTurn_transform2;
GeometryNode* corridorWideTurn_geom2;

//hall
TransformNode* hall_transform;
GeometryNode* hall_geom;
TransformNode* hall_transform2;
GeometryNode* hall_geom2;

//doors
TransformNode* door_transform;
GeometryNode* door_geom;
TransformNode* doorExte_transform;
GeometryNode* doorExte_geom;
TransformNode* doorSide_transform;
GeometryNode* doorSide_geom;
TransformNode* doorSide_transform2;
GeometryNode* doorSide_geom2;

TransformNode* door_transform2;
GeometryNode* door_geom2;
TransformNode* doorExte_transform2;
GeometryNode* doorExte_geom2;
TransformNode* doorSide_transform21;
GeometryNode* doorSide_geom21;
TransformNode* doorSide_transform22;
GeometryNode* doorSide_geom22;

TransformNode* door_transform3;
GeometryNode* door_geom3;
TransformNode* doorExte_transform3;
GeometryNode* doorExte_geom3;
TransformNode* doorSide_transform31;
GeometryNode* doorSide_geom31;
TransformNode* doorSide_transform32;
GeometryNode* doorSide_geom32;

TransformNode* door_transform4;
GeometryNode* door_geom4;
TransformNode* doorExte_transform4;
GeometryNode* doorExte_geom4;
TransformNode* doorSide_transform41;
GeometryNode* doorSide_geom41;
TransformNode* doorSide_transform42;
GeometryNode* doorSide_geom42;

TransformNode* door_transform5;
GeometryNode* door_geom5;
TransformNode* doorExte_transform5;
GeometryNode* doorExte_geom5;
TransformNode* doorSide_transform51;
GeometryNode* doorSide_geom51;
TransformNode* doorSide_transform52;
GeometryNode* doorSide_geom52;

TransformNode* door_transform6;
GeometryNode* door_geom6;
TransformNode* doorExte_transform6;
GeometryNode* doorExte_geom6;
TransformNode* doorSide_transform61;
GeometryNode* doorSide_geom61;
TransformNode* doorSide_transform62;
GeometryNode* doorSide_geom62;

TransformNode* door_transform7;
GeometryNode* door_geom7;
TransformNode* doorExte_transform7;
GeometryNode* doorExte_geom7;
TransformNode* doorSide_transform71;
GeometryNode* doorSide_geom71;
TransformNode* doorSide_transform72;
GeometryNode* doorSide_geom72;

TransformNode* door_transform8;
GeometryNode* door_geom8;
TransformNode* doorExte_transform8;
GeometryNode* doorExte_geom8;
TransformNode* doorSide_transform81;
GeometryNode* doorSide_geom81;
TransformNode* doorSide_transform82;
GeometryNode* doorSide_geom82;

//misc
TransformNode* column_transform;
GeometryNode* column_geom;

TransformNode* pillar1_transform;
GeometryNode* pillar1_geom;

TransformNode* wallHalf1_transform;
GeometryNode* wallHalf1_geom;
TransformNode* wallHalf1_transform2;
GeometryNode* wallHalf1_geom2;
TransformNode* wallHalf1_transform3;
GeometryNode* wallHalf1_geom3;
TransformNode* wallHalf1_transform4;
GeometryNode* wallHalf1_geom4;
TransformNode* wallHalf1_transform5;
GeometryNode* wallHalf1_geom5;

TransformNode* wall1_transform;
GeometryNode* wall1_geom;

TransformNode* well_transform;
GeometryNode* well_geom;
TransformNode* totem_transform;
GeometryNode* totem_geom;
TransformNode* arrow_transform;
GeometryNode* arrow_geom;
TransformNode* arrow_transform2;
GeometryNode* arrow_geom2;

TransformNode* well_transform2;
GeometryNode* well_geom2;
TransformNode* totem_transform2;
GeometryNode* totem_geom2;
TransformNode* arrow_transform21;
GeometryNode* arrow_geom21;
TransformNode* arrow_transform22;
GeometryNode* arrow_geom22;

TransformNode* well_transform3;
GeometryNode* well_geom3;
TransformNode* totem_transform3;
GeometryNode* totem_geom3;
TransformNode* arrow_transform31;
GeometryNode* arrow_geom31;
TransformNode* arrow_transform32;
GeometryNode* arrow_geom32;

TransformNode* well_transform4;
GeometryNode* well_geom4;
TransformNode* totem_transform4;
GeometryNode* totem_geom4;
TransformNode* arrow_transform41;
GeometryNode* arrow_geom41;
TransformNode* arrow_transform42;
GeometryNode* arrow_geom42;

TransformNode* dragon_transform;
GeometryNode* dragon_geom;
TransformNode* pedestal_transform;
GeometryNode* pedestal_geom;
TransformNode* dragon_transform2;
GeometryNode* dragon_geom2;
TransformNode* pedestal_transform2;
GeometryNode* pedestal_geom2;

TransformNode* spikes_transform;
GeometryNode* spikes_geom;
TransformNode* spikes_transform2;
GeometryNode* spikes_geom2;
TransformNode* spikes_transform3;
GeometryNode* spikes_geom3;
TransformNode* spikes_transform4;
GeometryNode* spikes_geom4;
TransformNode* spikes_transform5;
GeometryNode* spikes_geom5;
TransformNode* spikes_transform6;
GeometryNode* spikes_geom6;
TransformNode* spikes_transform7;
GeometryNode* spikes_geom7;
TransformNode* spikes_transform8;
GeometryNode* spikes_geom8;
TransformNode* spikes_transform9;
GeometryNode* spikes_geom9;

TransformNode* trap_transform;
GeometryNode* trap_geom;
TransformNode* trap_transform2;
GeometryNode* trap_geom2;
TransformNode* trap_transform3;
GeometryNode* trap_geom3;
TransformNode* trap_transform4;
GeometryNode* trap_geom4;
TransformNode* trap_transform5;
GeometryNode* trap_geom5;
TransformNode* trap_transform6;
GeometryNode* trap_geom6;
TransformNode* trap_transform7;
GeometryNode* trap_geom7;
TransformNode* trap_transform8;
GeometryNode* trap_geom8;
TransformNode* trap_transform9;
GeometryNode* trap_geom9;

TransformNode* blood_transform;
GeometryNode* blood_geom;
TransformNode* floortiles1_transform;
GeometryNode* floortiles1_geom;
TransformNode* floortiles1_transform2;
GeometryNode* floortiles1_geom2;
TransformNode* floortiles1_transform3;
GeometryNode* floortiles1_geom3;
TransformNode* floortiles1_transform4;
GeometryNode* floortiles1_geom4;
TransformNode* floortiles1_transform5;
GeometryNode* floortiles1_geom5;
//warrior
TransformNode* warrior_transform;
GeometryNode* warrior_geom;

// Shaders
// basic geometry shader
BasicGeometryShader* basic_geometry_shader;
// spotlight shader
SpotLightShader* spotlight_shader;
// shadow map shader
ShadowMapShader* shadowmap_shader;
// directional light shader
DirectionalLightShader* directionallight_shader;
// ambient light shader
AmbientLightShader* ambient_light_shader;
// omni light shader
OmniLightShader* omnilight_shader;

// Lights
glm::vec3  ambient_color;
DirectionalLight* sunlight;
SpotLight* spotlight;
SpotLight* spotlight2;
OmniLight* candlelight;

// light parameters (for animating the light)
float sunlight_rotationY;
float candlelight_rotationY;
float light_rotationY;

// frame buffer object
GLuint shadow_fbo;
GLuint shadow_tex;
float shadow_dimensions;

// forward declarations
bool CreateShadowFBO();
void DrawSceneToShadowFBO();
bool CreateShaders();
bool LoadObjModels();
void DrawOGLMesh(OGLMesh* mesh, glm::mat4x4& object_to_world_transform);
void SceneGraph();
void DrawSpotLightSource();
void SceneGraphDraw();

// This init function is called before FREEGLUT goes into its main loop.
bool InitializeRenderer(void)   
{ 
	PlaySound(TEXT("../../Desiderii_Marginis_-_The_Sleep_of_reason_produces_monsters"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
	
	// Initialize GLEW (openGL extensions)
	// GLEW is a library which determines which OpenGL extensions are supported on each platform
	// For example, in windows we need this since Microsoft does not support anything beyond OpenGL 1.1 (look at the gl/gl.h header file)
	// The code below uses GLEW to include any extensions supported in this platform
	glewExperimental = GL_TRUE;
	GLuint err = glewInit();
	// skip GLEW bug in glewInit
	unsigned int _enum = glGetError();	
	if (GLEW_OK != err)
	{
		PrintToOutputWindow("GLEW error %s", glewGetErrorString(err));
		return false;
	}
	else
		PrintToOutputWindow("Using GLEW %s", glewGetString(GLEW_VERSION));

	// check specifically for OpenGL 3.3 support
	bool ogl33_supported = (bool)(GLEW_GET_VAR(__GLEW_VERSION_3_3)!=0);
	if (!ogl33_supported)
	{
		PrintToOutputWindow("OpenGL 3.3 not supported. Exiting.");
		return false;
	}
	else
		PrintToOutputWindow("OpenGL 3.3 supported.");

	// define the lights here
	spotlight = new SpotLight();
	spotlight->m_name = "spotlight";
	spotlight2 = new SpotLight();
	spotlight2->m_name = "spotlight2";

		// define the lights here
	sunlight = new DirectionalLight();
	sunlight->m_name = "sun";
	sunlight->m_color = glm::vec3(0.4f, 0.6f, 0.9f);
	sunlight->m_initial_direction = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);

	candlelight = new OmniLight();
	candlelight->m_name = "candle";
	candlelight->m_color = glm::vec3(0.7f, 0.1f, 0.1f);
	candlelight->m_initial_position = glm::vec4(0.0f, 3.0f, -8.0f, 1.0f);

	up = glm::vec3(0.0f, 1.0f, 0.0f);

	world_translate = glm::vec3(0);

	glm::mat4x4 world_rotate = glm::rotate(world_rotate_y,0.0f,1.0f,0.0f);

	// Create the shaders here
	// Shader declaration is in the Shaders.h file
	// The CreateShaders function initializes the pointers, compiles the shader files
	// and checks for uniforms
	if (!CreateShaders())
	{
		return false;
	}

	// Load the OBJ models here
	if (!LoadObjModels())
	{
		PrintToOutputWindow("Error in loading obj models. Exiting");
		return false;
	}

	// Enable the depth buffer
	// Default is disabled
	glEnable(GL_DEPTH_TEST);

	// glDepthFunc tells OpenGL to accept fragments whose depth is less or equal than the current depth value
	// Note that 0.0 denotes the near field and 1.0 denotes the far field
	// Initial value is GL_LESS
	glDepthFunc(GL_LEQUAL);

	// Set the value to clear the depth buffer to value 1.0 (all far) (using glClear later on)
	glClearDepth(1.0f);

	// Enable Face Culling
	glEnable(GL_CULL_FACE);
	// Tell OpenGL to cull back faces
	glCullFace(GL_BACK);
	// Tell OpenGL that the front faces are the ones in counter-clockwise order
	glFrontFace(GL_CCW);

	// Initialize the FBO
	CreateShadowFBO();

	// Enable Scene Graph
	
	SceneGraph();

	// check if we have generated any OpenGL errors
	glError();

	return true;
}

bool CreateShadowFBO()
{
	// set the shadow dimensions
	shadow_dimensions = 2048.0f;

	// Create a framebuffer object (FBO)
	// When bound, rendering will happen on the FBO's attached textures
	glGenFramebuffers(1, &shadow_fbo);
	// set the fbo active
	glBindFramebuffer(GL_FRAMEBUFFER, shadow_fbo);

	// since we need to render only depth maps, we tell OpenGL that we do not need
	// to write to any color buffer
	glDrawBuffer(GL_NONE);
	// similarly, we do not need to read from any color buffer
	glReadBuffer(GL_NONE);

	// generate a texture to write to
	glGenTextures(1, &shadow_tex);
	// set the texture active
	glBindTexture(GL_TEXTURE_2D, shadow_tex);

	PrintToOutputWindow("%s, Generated Depth Texture: %i.", spotlight->m_name.c_str(), shadow_tex);

	// allocate space for a depth texture
	// each value will be stored in a single channel 32-bit float value
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, shadow_dimensions, shadow_dimensions, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	// we set linear interpolation for the filtering and clamp to edge for wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// FBO's do not have any default buffers to write to
	// instead, we need to set a number of images attached to them which will specify where to write
	// information such as color and depth
	// The common approach is to attach one or more color textures and one depth texture
	// For shadow mapping, only a depth texture needs to be attached (Which was created above)
	// the depth texture is attached to the depth attachment point of the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadow_tex, 0);

	// check for any FBO errors (similar to glError)
	// this checks for example, if the attachments that were set using glFramebufferTexture are valid
	if (checkFrameBufferError("(Depth) Incomplete SpotLight fbo")) return false;

	// set the texture id to the spotlight object
	// this is later used in the geometry node to pass it as a texture to the spotlight shader
	spotlight->m_shadow_map_texture_id = shadow_tex;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

void SceneGraph()
{
	// Scene graph example
	// background settings
	// Set the RGBA values to clear the color buffer (using glClear later on)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // for spot light
	ambient_color = glm::vec3(0.1, 0.12, 0.15);

	// light settings
	spotlight->m_color = glm::vec3(1.0f, 0.5f, 1.0f);
	spotlight->m_initial_target = myPlayer->myPosition;
	spotlight->m_initial_position =  myPlayer->myPosition + glm::vec3(0.0f,3.0f,0.0f);
	spotlight->m_near_range = 1.0f;
	spotlight->m_far_range = 5.0f;
	spotlight->m_aperture = 60.0f;

	spotlight2->m_color = glm::vec3(0.5f, 0.5f, 0.5f);
	spotlight2->m_initial_target =  glm::vec3(0.0f,0.0f,-11.0f);
	spotlight2->m_initial_position =  glm::vec3(0.0f,3.0f,-11.0f);
	spotlight2->m_near_range = 1.0f;
	spotlight2->m_far_range = 5.0f;
	spotlight2->m_aperture = 10.0f;

	//eye = glm::vec3(myPlayer->eyePosition.x, myPlayer->eyePosition.y, myPlayer->eyePosition.z);
	//target = glm::vec3(myPlayer->targetPosition.x, myPlayer->targetPosition.y, myPlayer->targetPosition.z);
	// scene settings
	root = new Root();
	root2 = new Root();
	world_transform = new TransformNode("world_transform");
	ground_transform = new TransformNode("ground_transform");
	ground_geom = new GeometryNode("ground_geom", groundwhiteMesh);

	roomSmall_transform = new TransformNode("roomMedium_transform");
	roomSmall_geom = new GeometryNode("roomMedium_geom", roomSmallMesh);
	roomSmall_transform2 = new TransformNode("roomMedium_transform2");
	roomSmall_geom2 = new GeometryNode("roomMedium_geom2", roomSmallMesh);

	roomMedium_transform = new TransformNode("roomMedium_transform");
	roomMedium_geom = new GeometryNode("roomMedium_geom", roomMediumMesh);
	roomMedium_transform2 = new TransformNode("roomMedium_transform2");
	roomMedium_geom2 = new GeometryNode("roomMedium_geom2", roomMediumMesh);
	
	corridorNarrow_transform = new TransformNode("corridorNarrow_transform");
	corridorNarrow_geom = new GeometryNode("corridorNarrow_geom", corridorNarrowMesh);
	corridorNarrow_transform2 = new TransformNode("corridorNarrow_transform2");
	corridorNarrow_geom2 = new GeometryNode("corridorNarrow_geom2", corridorNarrowMesh);
	corridorNarrow_transform3 = new TransformNode("corridorNarrow_transform3");
	corridorNarrow_geom3 = new GeometryNode("corridorNarrow_geom3", corridorNarrowMesh);
	corridorNarrow_transform4 = new TransformNode("corridorNarrow_transform4");
	corridorNarrow_geom4 = new GeometryNode("corridorNarrow_geom4", corridorNarrowMesh);
	corridorNarrow_transform5 = new TransformNode("corridorNarrow_transform5");
	corridorNarrow_geom5 = new GeometryNode("corridorNarrow_geom5", corridorNarrowMesh);
	corridorNarrow_transform6 = new TransformNode("corridorNarrow_transform6");
	corridorNarrow_geom6 = new GeometryNode("corridorNarrow_geom6", corridorNarrowMesh);
	corridorNarrow_transform7 = new TransformNode("corridorNarrow_transform7");
	corridorNarrow_geom7 = new GeometryNode("corridorNarrow_geom7", corridorNarrowMesh);
	corridorNarrow_transform8 = new TransformNode("corridorNarrow_transform8");
	corridorNarrow_geom8 = new GeometryNode("corridorNarrow_geom8", corridorNarrowMesh);
	corridorNarrow_transform9 = new TransformNode("corridorNarrow_transform9");
	corridorNarrow_geom9 = new GeometryNode("corridorNarrow_geom9", corridorNarrowMesh);
	corridorNarrow_transform10 = new TransformNode("corridorNarrow_transform10");
	corridorNarrow_geom10 = new GeometryNode("corridorNarrow_geom10", corridorNarrowMesh);
	corridorNarrow_transform11 = new TransformNode("corridorNarrow_transform11");
	corridorNarrow_geom11 = new GeometryNode("corridorNarrow_geom11", corridorNarrowMesh);
	corridorNarrow_transform12 = new TransformNode("corridorNarrow_transform12");
	corridorNarrow_geom12 = new GeometryNode("corridorNarrow_geom12", corridorNarrowMesh);
	corridorNarrow_transform13 = new TransformNode("corridorNarrow_transform13");
	corridorNarrow_geom13 = new GeometryNode("corridorNarrow_geom13", corridorNarrowMesh);
	corridorNarrow_transform14 = new TransformNode("corridorNarrow_transform14");
	corridorNarrow_geom14 = new GeometryNode("corridorNarrow_geom14", corridorNarrowMesh);
	corridorNarrow_transform15 = new TransformNode("corridorNarrow_transform15");
	corridorNarrow_geom15 = new GeometryNode("corridorNarrow_geom15", corridorNarrowMesh);
	corridorNarrow_transform16 = new TransformNode("corridorNarrow_transform16");
	corridorNarrow_geom16 = new GeometryNode("corridorNarrow_geom16", corridorNarrowMesh);
	corridorNarrow_transform17 = new TransformNode("corridorNarrow_transform17");
	corridorNarrow_geom17 = new GeometryNode("corridorNarrow_geom17", corridorNarrowMesh);
	corridorNarrow_transform18 = new TransformNode("corridorNarrow_transform18");
	corridorNarrow_geom18 = new GeometryNode("corridorNarrow_geom18", corridorNarrowMesh);
	corridorNarrow_transform19 = new TransformNode("corridorNarrow_transform19");
	corridorNarrow_geom19 = new GeometryNode("corridorNarrow_geom19", corridorNarrowMesh);
	corridorNarrow_transform20 = new TransformNode("corridorNarrow_transform20");
	corridorNarrow_geom20 = new GeometryNode("corridorNarrow_geom20", corridorNarrowMesh);
	corridorNarrow_transform21 = new TransformNode("corridorNarrow_transform21");
	corridorNarrow_geom21 = new GeometryNode("corridorNarrow_geom21", corridorNarrowMesh);
	corridorNarrow_transform22 = new TransformNode("corridorNarrow_transform22");
	corridorNarrow_geom22 = new GeometryNode("corridorNarrow_geom22", corridorNarrowMesh);
	
	corridorNarrowTurn_transform = new TransformNode("corridorNarrowTurn_transform");
	corridorNarrowTurn_geom = new GeometryNode("corridorNarrowTurn_geom", corridorNarrowTurnMesh);
	corridorNarrowTurn_transform2 = new TransformNode("corridorNarrowTurn_transform2");
	corridorNarrowTurn_geom2 = new GeometryNode("corridorNarrowTurn_geom2", corridorNarrowTurnMesh);
	corridorNarrowTurn_transform3 = new TransformNode("corridorNarrowTurn_transform3");
	corridorNarrowTurn_geom3 = new GeometryNode("corridorNarrowTurn_geom3", corridorNarrowTurnMesh);
	corridorNarrowTurn_transform4 = new TransformNode("corridorNarrowTurn_transform4");
	corridorNarrowTurn_geom4 = new GeometryNode("corridorNarrowTurn_geom4", corridorNarrowTurnMesh);
	corridorNarrowTurn_transform5 = new TransformNode("corridorNarrowTurn_transform5");
	corridorNarrowTurn_geom5 = new GeometryNode("corridorNarrowTurn_geom5", corridorNarrowTurnMesh);
	corridorNarrowTurn_transform6 = new TransformNode("corridorNarrowTurn_transform6");
	corridorNarrowTurn_geom6 = new GeometryNode("corridorNarrowTurn_geom6", corridorNarrowTurnMesh);
	corridorNarrowTurn_transform7 = new TransformNode("corridorNarrowTurn_transform7");
	corridorNarrowTurn_geom7 = new GeometryNode("corridorNarrowTurn_geom7", corridorNarrowTurnMesh);

	corridorNarrowTJ_transform = new TransformNode("corridorNarrowTJ_transform");
	corridorNarrowTJ_geom = new GeometryNode("corridorNarrowTJ_geom", corridorNarrowTJMesh);
	corridorNarrowTJ_transform2 = new TransformNode("corridorNarrowTJ_transform2");
	corridorNarrowTJ_geom2 = new GeometryNode("corridorNarrowTJ_geom2", corridorNarrowTJMesh);

	corridorMedium_transform = new TransformNode("corridorMedium_transform");
	corridorMedium_geom = new GeometryNode("corridorMedium_geom", corridorMediumMesh);
	corridorMedium_transform2 = new TransformNode("corridorMedium_transform2");
	corridorMedium_geom2 = new GeometryNode("corridorMedium_geom2", corridorMediumMesh);
	corridorMedium_transform3 = new TransformNode("corridorMedium_transform3");
	corridorMedium_geom3 = new GeometryNode("corridorMedium_geom3", corridorMediumMesh);
	corridorMedium_transform4 = new TransformNode("corridorMedium_transform4");
	corridorMedium_geom4 = new GeometryNode("corridorMedium_geom4", corridorMediumMesh);
	corridorMedium_transform5 = new TransformNode("corridorMedium_transform5");
	corridorMedium_geom5 = new GeometryNode("corridorMedium_geom5", corridorMediumMesh);
	corridorMedium_transform6 = new TransformNode("corridorMedium_transform6");
	corridorMedium_geom6 = new GeometryNode("corridorMedium_geom6", corridorMediumMesh);
	corridorMedium_transform7 = new TransformNode("corridorMedium_transform7");
	corridorMedium_geom7 = new GeometryNode("corridorMedium_geom7", corridorMediumMesh);
	corridorMedium_transform8 = new TransformNode("corridorMedium_transform8");
	corridorMedium_geom8 = new GeometryNode("corridorMedium_geom8", corridorMediumMesh);
	corridorMedium_transform9 = new TransformNode("corridorMedium_transform9");
	corridorMedium_geom9 = new GeometryNode("corridorMedium_geom9", corridorMediumMesh);
	corridorMedium_transform10 = new TransformNode("corridorMedium_transform10");
	corridorMedium_geom10 = new GeometryNode("corridorMedium_geom10", corridorMediumMesh);
	corridorMedium_transform11 = new TransformNode("corridorMedium_transform11");
	corridorMedium_geom11 = new GeometryNode("corridorMedium_geom11", corridorMediumMesh);
	corridorMedium_transform12 = new TransformNode("corridorMedium_transform12");
	corridorMedium_geom12 = new GeometryNode("corridorMedium_geom12", corridorMediumMesh);
	corridorMedium_transform13 = new TransformNode("corridorMedium_transform13");
	corridorMedium_geom13 = new GeometryNode("corridorMedium_geom13", corridorMediumMesh);
	corridorMedium_transform14 = new TransformNode("corridorMedium_transform14");
	corridorMedium_geom14 = new GeometryNode("corridorMedium_geom14", corridorMediumMesh);
	corridorMedium_transform15 = new TransformNode("corridorMedium_transform15");
	corridorMedium_geom15 = new GeometryNode("corridorMedium_geom15", corridorMediumMesh);
	corridorMedium_transform16 = new TransformNode("corridorMedium_transform16");
	corridorMedium_geom16 = new GeometryNode("corridorMedium_geom16", corridorMediumMesh);
	corridorMedium_transform17 = new TransformNode("corridorMedium_transform17");
	corridorMedium_geom17 = new GeometryNode("corridorMedium_geom17", corridorMediumMesh);
	corridorMedium_transform18 = new TransformNode("corridorMedium_transform18");
	corridorMedium_geom18 = new GeometryNode("corridorMedium_geom18", corridorMediumMesh);
	corridorMedium_transform19 = new TransformNode("corridorMedium_transform19");
	corridorMedium_geom19 = new GeometryNode("corridorMedium_geom19", corridorMediumMesh);

	corridorMediumTurn_transform = new TransformNode("corridorMediumTurn_transform");
	corridorMediumTurn_geom = new GeometryNode("corridorMediumTurn_geom", corridorMediumTurnMesh);
	corridorMediumTurn_transform2 = new TransformNode("corridorMediumTurn_transform2");
	corridorMediumTurn_geom2 = new GeometryNode("corridorMediumTurn_geom2", corridorMediumTurnMesh);
	corridorMediumTurn_transform3 = new TransformNode("corridorMediumTurn_transform3");
	corridorMediumTurn_geom3 = new GeometryNode("corridorMediumTurn_geom3", corridorMediumTurnMesh);
	corridorMediumTurn_transform4 = new TransformNode("corridorMediumTurn_transform4");
	corridorMediumTurn_geom4 = new GeometryNode("corridorMediumTurn_geom4", corridorMediumTurnMesh);
	corridorMediumTurn_transform5 = new TransformNode("corridorMediumTurn_transform5");
	corridorMediumTurn_geom5 = new GeometryNode("corridorMediumTurn_geom5", corridorMediumTurnMesh);
	corridorMediumTurn_transform6 = new TransformNode("corridorMediumTurn_transform6");
	corridorMediumTurn_geom6 = new GeometryNode("corridorMediumTurn_geom6", corridorMediumTurnMesh);

	corridorMediumTJ_transform = new TransformNode("corridorMediumTJ_transform");
	corridorMediumTJ_geom = new GeometryNode("corridorMediumTJ_geom", corridorMediumTJMesh);

	corridorWideTurn_transform = new TransformNode("corridorWideTurn_transform");
	corridorWideTurn_geom = new GeometryNode("corridorWideTurn_geom", corridorWideTurnMesh);
	corridorWideTurn_transform2 = new TransformNode("corridorWideTurn_transform2");
	corridorWideTurn_geom2 = new GeometryNode("corridorWideTurn_geom2", corridorWideTurnMesh);

	hall_transform = new TransformNode("hall_transform");
	hall_geom = new GeometryNode("hall_geom", hallMesh);
	hall_transform2 = new TransformNode("hall_transform2");
	hall_geom2 = new GeometryNode("hall_geom2", hallMesh);
	
	door_transform = new TransformNode("door_transform");
	door_geom = new GeometryNode("door_geom", doorMesh);
	doorSide_geom = new GeometryNode("doorSide_geom", doorSideMesh);
	doorSide_transform = new TransformNode("doorSide_transform");
	doorSide_geom2 = new GeometryNode("doorSide_geom2", doorSideMesh);
	doorSide_transform2 = new TransformNode("doorSide_transform2");
	
	door_transform2 = new TransformNode("door_transform2");
	door_geom2 = new GeometryNode("door_geom2", doorMesh);
	doorSide_geom21 = new GeometryNode("doorSide_geom21", doorSideMesh);
	doorSide_transform21 = new TransformNode("doorSide_transform21");
	doorSide_geom22 = new GeometryNode("doorSide_geom22", doorSideMesh);
	doorSide_transform22 = new TransformNode("doorSide_transform22");
	
	door_transform3 = new TransformNode("door_transform3");
	door_geom3 = new GeometryNode("door_geom3", doorMesh);
	doorSide_geom31 = new GeometryNode("doorSide_geom31", doorSideMesh);
	doorSide_transform31 = new TransformNode("doorSide_transform31");
	doorSide_geom32 = new GeometryNode("doorSide_geom32", doorSideMesh);
	doorSide_transform32 = new TransformNode("doorSide_transform32");

	door_transform4 = new TransformNode("door_transform4");
	door_geom4 = new GeometryNode("door_geom4", doorMesh);
	doorSide_geom41 = new GeometryNode("doorSide_geom41", doorSideMesh);
	doorSide_transform41 = new TransformNode("doorSide_transform41");
	doorSide_geom42 = new GeometryNode("doorSide_geom42", doorSideMesh);
	doorSide_transform42 = new TransformNode("doorSide_transform42");

	door_transform5 = new TransformNode("door_transform5");
	door_geom5 = new GeometryNode("door_geom5", doorMesh);
	doorSide_geom51 = new GeometryNode("doorSide_geom51", doorSideMesh);
	doorSide_transform51 = new TransformNode("doorSide_transform51");
	doorSide_geom52 = new GeometryNode("doorSide_geom52", doorSideMesh);
	doorSide_transform52 = new TransformNode("doorSide_transform52");

	door_transform6 = new TransformNode("door_transform6");
	door_geom6 = new GeometryNode("door_geom6", doorMesh);
	doorSide_geom61 = new GeometryNode("doorSide_geom61", doorSideMesh);
	doorSide_transform61 = new TransformNode("doorSide_transform61");
	doorSide_geom62 = new GeometryNode("doorSide_geom62", doorSideMesh);
	doorSide_transform62 = new TransformNode("doorSide_transform62");

	door_transform7 = new TransformNode("door_transform7");
	door_geom7 = new GeometryNode("door_geom7", doorMesh);
	doorSide_geom71 = new GeometryNode("doorSide_geom71", doorSideMesh);
	doorSide_transform71 = new TransformNode("doorSide_transform71");
	doorSide_geom72 = new GeometryNode("doorSide_geom72", doorSideMesh);
	doorSide_transform72 = new TransformNode("doorSide_transform72");

	door_transform8 = new TransformNode("door_transform");
	door_geom8 = new GeometryNode("door_geom", doorMesh);
	doorSide_geom81 = new GeometryNode("doorSide_geom81", doorSideMesh);
	doorSide_transform81 = new TransformNode("doorSide_transform81");
	doorSide_geom82 = new GeometryNode("doorSide_geom82", doorSideMesh);
	doorSide_transform82 = new TransformNode("doorSide_transform82");

	warrior_transform = new TransformNode("warrior_transform");
	warrior_geom = new GeometryNode("warrior_geom", warriorMesh);
	
	spikes_transform = new TransformNode("spikes_transform");
	spikes_geom = new GeometryNode("spikes_geom",spikesMesh);
	trap_transform = new TransformNode("trap_transform");
	trap_geom = new GeometryNode("trap_geom",trapMesh);
	
	spikes_transform2 = new TransformNode("spikes_transform2");
	spikes_geom2 = new GeometryNode("spikes_geom2",spikesMesh);
	trap_transform2 = new TransformNode("trap_transform2");
	trap_geom2 = new GeometryNode("trap_geom2",trapMesh);

	spikes_transform3 = new TransformNode("spikes_transform3");
	spikes_geom3 = new GeometryNode("spikes_geom3",spikesMesh);
	trap_transform3 = new TransformNode("trap_transform3");
	trap_geom3 = new GeometryNode("trap_geom3",trapMesh);

	spikes_transform4 = new TransformNode("spikes_transform4");
	spikes_geom4 = new GeometryNode("spikes_geom4",spikesMesh);
	trap_transform4 = new TransformNode("trap_transform4");
	trap_geom4 = new GeometryNode("trap_geom4",trapMesh);

	spikes_transform5 = new TransformNode("spikes_transform5");
	spikes_geom5 = new GeometryNode("spikes_geom5",spikesMesh);
	trap_transform5 = new TransformNode("trap_transform5");
	trap_geom5 = new GeometryNode("trap_geom5",trapMesh);

	spikes_transform6 = new TransformNode("spikes_transform6");
	spikes_geom6 = new GeometryNode("spikes_geom6",spikesMesh);
	trap_transform6 = new TransformNode("trap_transform6");
	trap_geom6 = new GeometryNode("trap_geom6",trapMesh);

	spikes_transform7 = new TransformNode("spikes_transform7");
	spikes_geom7 = new GeometryNode("spikes_geom7",spikesMesh);
	trap_transform7 = new TransformNode("trap_transform7");
	trap_geom7 = new GeometryNode("trap_geom7",trapMesh);

	spikes_transform8 = new TransformNode("spikes_transform8");
	spikes_geom8 = new GeometryNode("spikes_geom8",spikesMesh);
	trap_transform8 = new TransformNode("trap_transform8");
	trap_geom8 = new GeometryNode("trap_geom8",trapMesh);

	spikes_transform9 = new TransformNode("spikes_transform9");
	spikes_geom9 = new GeometryNode("spikes_geom9",spikesMesh);
	trap_transform9= new TransformNode("trap_transform9");
	trap_geom9 = new GeometryNode("trap_geom9",trapMesh);
	
	well_transform = new TransformNode("well_transform");
	well_geom = new GeometryNode("well_geom",wellMesh);
	totem_transform = new TransformNode("totem_transform");
	totem_geom = new GeometryNode("totem_geom",totemMesh);
	arrow_transform = new TransformNode("arrow_transform");
	arrow_geom = new GeometryNode("arrow_geom",arrowMesh);
	arrow_transform2 = new TransformNode("arrow_transform2");
	arrow_geom2 = new GeometryNode("arrow_geom2",arrowMesh);
	
	well_transform2 = new TransformNode("well_transform2");
	well_geom2 = new GeometryNode("well_geom2",wellMesh);
	totem_transform2 = new TransformNode("totem_transform2");
	totem_geom2 = new GeometryNode("totem_geom2",totemMesh);
	arrow_transform21 = new TransformNode("arrow_transform21");
	arrow_geom21 = new GeometryNode("arrow_geom21",arrowMesh);
	arrow_transform22 = new TransformNode("arrow_transform22");
	arrow_geom22 = new GeometryNode("arrow_geom22",arrowMesh);

	well_transform3 = new TransformNode("well_transform3");
	well_geom3 = new GeometryNode("well_geom3",wellMesh);
	totem_transform3 = new TransformNode("totem_transform3");
	totem_geom3 = new GeometryNode("totem_geom3",totemMesh);
	arrow_transform31 = new TransformNode("arrow_transform31");
	arrow_geom31 = new GeometryNode("arrow_geom31",arrowMesh);
	arrow_transform32 = new TransformNode("arrow_transform32");
	arrow_geom32 = new GeometryNode("arrow_geom32",arrowMesh);

	well_transform4 = new TransformNode("well_transform4");
	well_geom4 = new GeometryNode("well_geom4",wellMesh);
	totem_transform4 = new TransformNode("totem_transform4");
	totem_geom4 = new GeometryNode("totem_geom4",totemMesh);
	arrow_transform41 = new TransformNode("arrow_transform41");
	arrow_geom41 = new GeometryNode("arrow_geom41",arrowMesh);
	arrow_transform42 = new TransformNode("arrow_transform42");
	arrow_geom42 = new GeometryNode("arrow_geom42",arrowMesh);

	pedestal_transform = new TransformNode("pedestal_transform");
	pedestal_geom = new GeometryNode("pedestal_geom",pedestalMesh);
	dragon_transform = new TransformNode("dragon_transform");
	dragon_geom = new GeometryNode("dragon_geom",dragonMesh);

	pedestal_transform2 = new TransformNode("pedestal_transform2");
	pedestal_geom2 = new GeometryNode("pedestal_geom2",pedestalMesh);
	dragon_transform2 = new TransformNode("dragon_transform2");
	dragon_geom2 = new GeometryNode("dragon_geom2",dragonMesh);

	wall1_transform = new TransformNode("wall1_transform");
	wall1_geom = new GeometryNode("wall1_geom",wall1Mesh);

	wallHalf1_transform = new TransformNode("wallHalf1_transform");
	wallHalf1_geom = new GeometryNode("wallHalf1_geom",wallHalf1Mesh);
	wallHalf1_transform2 = new TransformNode("wallHalf1_transform2");
	wallHalf1_geom2 = new GeometryNode("wallHalf1_geom2",wallHalf1Mesh);
	wallHalf1_transform3 = new TransformNode("wallHalf1_transform3");
	wallHalf1_geom3 = new GeometryNode("wallHalf1_geom3",wallHalf1Mesh);
	wallHalf1_transform4 = new TransformNode("wallHalf1_transform4");
	wallHalf1_geom4 = new GeometryNode("wallHalf1_geom4",wallHalf1Mesh);
	wallHalf1_transform5 = new TransformNode("wallHalf1_transform5");
	wallHalf1_geom5 = new GeometryNode("wallHalf1_geom5",wallHalf1Mesh);

	column_transform = new TransformNode("column_transform");
	column_geom = new GeometryNode("column_geom",columnMesh);

	pillar1_transform = new TransformNode("pillar1_transform");
	pillar1_geom = new GeometryNode("pillar1_geom",pillar1Mesh);

	floortiles1_transform = new TransformNode("floortiles1_transform");
	floortiles1_geom = new GeometryNode("floortiles1_geom",floortiles1Mesh);
	floortiles1_transform2 = new TransformNode("floortiles1_transform2");
	floortiles1_geom2 = new GeometryNode("floortiles1_geom2",floortiles1Mesh);
	floortiles1_transform3 = new TransformNode("floortiles1_transform3");
	floortiles1_geom3 = new GeometryNode("floortiles1_geom3",floortiles1Mesh);
	floortiles1_transform4 = new TransformNode("floortiles1_transform4");
	floortiles1_geom4 = new GeometryNode("floortiles1_geom4",floortiles1Mesh);
	floortiles1_transform5 = new TransformNode("floortiles1_transform5");
	floortiles1_geom5 = new GeometryNode("floortiles1_geom5",floortiles1Mesh);
	//
	//RENDER TREE/////////////////////////////////////////////////////////////////////////////////////////////////
	//
	root->AddChild(world_transform);
	root->AddChild(warrior_transform);

	warrior_transform->AddChild(warrior_geom);
	
	world_transform->AddChild(ground_transform);
	
	world_transform->AddChild(roomSmall_transform);
	world_transform->AddChild(roomSmall_transform2);

	world_transform->AddChild(roomMedium_transform);
	world_transform->AddChild(roomMedium_transform2);

	world_transform->AddChild(corridorNarrow_transform);
	world_transform->AddChild(corridorNarrow_transform2);
	world_transform->AddChild(corridorNarrow_transform3);
	world_transform->AddChild(corridorNarrow_transform4);
	world_transform->AddChild(corridorNarrow_transform5);
	world_transform->AddChild(corridorNarrow_transform6);
	world_transform->AddChild(corridorNarrow_transform7);
	world_transform->AddChild(corridorNarrow_transform8);
	
	world_transform->AddChild(corridorNarrow_transform9);
	world_transform->AddChild(corridorNarrow_transform10);
	world_transform->AddChild(corridorNarrow_transform11);
	world_transform->AddChild(corridorNarrow_transform12);
	world_transform->AddChild(corridorNarrow_transform13);
	world_transform->AddChild(corridorNarrow_transform14);
	world_transform->AddChild(corridorNarrow_transform15);
	world_transform->AddChild(corridorNarrow_transform16);
	world_transform->AddChild(corridorNarrow_transform17);
	world_transform->AddChild(corridorNarrow_transform18);
	world_transform->AddChild(corridorNarrow_transform19);
	world_transform->AddChild(corridorNarrow_transform20);
	world_transform->AddChild(corridorNarrow_transform21);
	world_transform->AddChild(corridorNarrow_transform22);

	world_transform->AddChild(corridorNarrowTurn_transform);
	world_transform->AddChild(corridorNarrowTurn_transform2);
	world_transform->AddChild(corridorNarrowTurn_transform3);
	world_transform->AddChild(corridorNarrowTurn_transform4);
	world_transform->AddChild(corridorNarrowTurn_transform5);
	world_transform->AddChild(corridorNarrowTurn_transform6);
	world_transform->AddChild(corridorNarrowTurn_transform7);

	world_transform->AddChild(corridorNarrowTJ_transform);
	world_transform->AddChild(corridorNarrowTJ_transform2);

	world_transform->AddChild(corridorMedium_transform);
	world_transform->AddChild(corridorMedium_transform2);
	world_transform->AddChild(corridorMedium_transform3);
	world_transform->AddChild(corridorMedium_transform4);
	world_transform->AddChild(corridorMedium_transform5);
	world_transform->AddChild(corridorMedium_transform6);
	world_transform->AddChild(corridorMedium_transform7);
	world_transform->AddChild(corridorMedium_transform8);
	world_transform->AddChild(corridorMedium_transform9);
	world_transform->AddChild(corridorMedium_transform10);
	world_transform->AddChild(corridorMedium_transform11);
	world_transform->AddChild(corridorMedium_transform12);
	world_transform->AddChild(corridorMedium_transform13);
	world_transform->AddChild(corridorMedium_transform14);
	world_transform->AddChild(corridorMedium_transform15);
	world_transform->AddChild(corridorMedium_transform16);
	world_transform->AddChild(corridorMedium_transform17);
	world_transform->AddChild(corridorMedium_transform18);
	world_transform->AddChild(corridorMedium_transform19);

	world_transform->AddChild(corridorMediumTurn_transform);
	world_transform->AddChild(corridorMediumTurn_transform2);
	world_transform->AddChild(corridorMediumTurn_transform3);
	world_transform->AddChild(corridorMediumTurn_transform4);
	world_transform->AddChild(corridorMediumTurn_transform5);
	world_transform->AddChild(corridorMediumTurn_transform6);

	world_transform->AddChild(corridorMediumTJ_transform);

	world_transform->AddChild(corridorWideTurn_transform);
	world_transform->AddChild(corridorWideTurn_transform2);
	
	world_transform->AddChild(hall_transform);
	world_transform->AddChild(hall_transform2);

	world_transform->AddChild(door_transform);
	world_transform->AddChild(doorSide_transform);
	world_transform->AddChild(doorSide_transform2);
	
	world_transform->AddChild(door_transform2);
	world_transform->AddChild(doorSide_transform21);
	world_transform->AddChild(doorSide_transform22);
	
	world_transform->AddChild(door_transform3);
	world_transform->AddChild(doorSide_transform31);
	world_transform->AddChild(doorSide_transform32);
	
	world_transform->AddChild(door_transform4);
	world_transform->AddChild(doorSide_transform41);
	world_transform->AddChild(doorSide_transform42);
	
	world_transform->AddChild(door_transform5);
	world_transform->AddChild(doorSide_transform51);
	world_transform->AddChild(doorSide_transform52);

	world_transform->AddChild(door_transform6);
	world_transform->AddChild(doorSide_transform61);
	world_transform->AddChild(doorSide_transform62);

	world_transform->AddChild(door_transform7);
	world_transform->AddChild(doorSide_transform71);
	world_transform->AddChild(doorSide_transform72);

	world_transform->AddChild(door_transform8);
	world_transform->AddChild(doorSide_transform81);
	world_transform->AddChild(doorSide_transform82);
	
	world_transform->AddChild(well_transform);
	world_transform->AddChild(totem_transform);
	world_transform->AddChild(arrow_transform);
	world_transform->AddChild(arrow_transform2);
	
	world_transform->AddChild(well_transform2);
	world_transform->AddChild(totem_transform2);
	world_transform->AddChild(arrow_transform21);
	world_transform->AddChild(arrow_transform22);

	world_transform->AddChild(well_transform3);
	world_transform->AddChild(totem_transform3);
	world_transform->AddChild(arrow_transform31);
	world_transform->AddChild(arrow_transform32);

	world_transform->AddChild(well_transform4);
	world_transform->AddChild(totem_transform4);
	world_transform->AddChild(arrow_transform41);
	world_transform->AddChild(arrow_transform42);
	
	world_transform->AddChild(spikes_transform);
	world_transform->AddChild(trap_transform);
	
	world_transform->AddChild(spikes_transform2);
	world_transform->AddChild(trap_transform2);
	world_transform->AddChild(spikes_transform3);
	world_transform->AddChild(trap_transform3);
	world_transform->AddChild(spikes_transform4);
	world_transform->AddChild(trap_transform4);
	world_transform->AddChild(spikes_transform5);
	world_transform->AddChild(trap_transform5);
	world_transform->AddChild(spikes_transform6);
	world_transform->AddChild(trap_transform6);
	world_transform->AddChild(spikes_transform7);
	world_transform->AddChild(trap_transform7);
	world_transform->AddChild(spikes_transform8);
	world_transform->AddChild(trap_transform8);
	world_transform->AddChild(spikes_transform9);
	world_transform->AddChild(trap_transform9);
	
	world_transform->AddChild(pedestal_transform);
	world_transform->AddChild(dragon_transform);
	world_transform->AddChild(pedestal_transform2);
	world_transform->AddChild(dragon_transform2);
	
	world_transform->AddChild(wall1_transform);
	world_transform->AddChild(wallHalf1_transform);
	world_transform->AddChild(wallHalf1_transform2);
	world_transform->AddChild(wallHalf1_transform3);
	world_transform->AddChild(wallHalf1_transform4);
	world_transform->AddChild(wallHalf1_transform5);

	world_transform->AddChild(floortiles1_transform);
	world_transform->AddChild(floortiles1_transform2);
	world_transform->AddChild(floortiles1_transform3);
	world_transform->AddChild(floortiles1_transform4);
	world_transform->AddChild(floortiles1_transform5);

	world_transform->AddChild(column_transform);

	world_transform->AddChild(pillar1_transform);

	////////////////////////////////////////////////////////////
	ground_transform->AddChild(ground_geom);

	roomMedium_transform->AddChild(roomMedium_geom);
	roomMedium_transform2->AddChild(roomMedium_geom2);

	roomSmall_transform->AddChild(roomSmall_geom);
	roomSmall_transform2->AddChild(roomSmall_geom2);

	corridorNarrow_transform->AddChild(corridorNarrow_geom);
	corridorNarrow_transform2->AddChild(corridorNarrow_geom2);
	corridorNarrow_transform3->AddChild(corridorNarrow_geom3);
	corridorNarrow_transform4->AddChild(corridorNarrow_geom4);
	corridorNarrow_transform5->AddChild(corridorNarrow_geom5);
	corridorNarrow_transform6->AddChild(corridorNarrow_geom6);
	corridorNarrow_transform7->AddChild(corridorNarrow_geom7);
	corridorNarrow_transform8->AddChild(corridorNarrow_geom8);
	corridorNarrow_transform9->AddChild(corridorNarrow_geom9);
	corridorNarrow_transform10->AddChild(corridorNarrow_geom10);
	corridorNarrow_transform11->AddChild(corridorNarrow_geom11);
	corridorNarrow_transform12->AddChild(corridorNarrow_geom12);
	corridorNarrow_transform13->AddChild(corridorNarrow_geom13);
	corridorNarrow_transform14->AddChild(corridorNarrow_geom14);
	corridorNarrow_transform15->AddChild(corridorNarrow_geom15);
	corridorNarrow_transform16->AddChild(corridorNarrow_geom16);
	corridorNarrow_transform17->AddChild(corridorNarrow_geom17);
	corridorNarrow_transform18->AddChild(corridorNarrow_geom18);
	corridorNarrow_transform19->AddChild(corridorNarrow_geom19);
	corridorNarrow_transform20->AddChild(corridorNarrow_geom20);
	corridorNarrow_transform21->AddChild(corridorNarrow_geom21);
	corridorNarrow_transform22->AddChild(corridorNarrow_geom22);

	corridorNarrowTurn_transform->AddChild(corridorNarrowTurn_geom);
	corridorNarrowTurn_transform2->AddChild(corridorNarrowTurn_geom2);
	corridorNarrowTurn_transform3->AddChild(corridorNarrowTurn_geom3);
	corridorNarrowTurn_transform4->AddChild(corridorNarrowTurn_geom4);
	corridorNarrowTurn_transform5->AddChild(corridorNarrowTurn_geom5);
	corridorNarrowTurn_transform6->AddChild(corridorNarrowTurn_geom6);
	corridorNarrowTurn_transform7->AddChild(corridorNarrowTurn_geom7);

	corridorNarrowTJ_transform->AddChild(corridorNarrowTJ_geom);
	corridorNarrowTJ_transform2->AddChild(corridorNarrowTJ_geom2);

	corridorMedium_transform->AddChild(corridorMedium_geom);
	corridorMedium_transform2->AddChild(corridorMedium_geom2);
	corridorMedium_transform3->AddChild(corridorMedium_geom3);
	corridorMedium_transform4->AddChild(corridorMedium_geom4);
	corridorMedium_transform5->AddChild(corridorMedium_geom5);
	corridorMedium_transform6->AddChild(corridorMedium_geom6);
	corridorMedium_transform7->AddChild(corridorMedium_geom7);
	corridorMedium_transform8->AddChild(corridorMedium_geom8);
	corridorMedium_transform9->AddChild(corridorMedium_geom9);
	corridorMedium_transform10->AddChild(corridorMedium_geom10);
	corridorMedium_transform11->AddChild(corridorMedium_geom11);
	corridorMedium_transform12->AddChild(corridorMedium_geom12);
	corridorMedium_transform13->AddChild(corridorMedium_geom13);
	corridorMedium_transform14->AddChild(corridorMedium_geom14);
	corridorMedium_transform15->AddChild(corridorMedium_geom15);
	corridorMedium_transform16->AddChild(corridorMedium_geom16);
	corridorMedium_transform17->AddChild(corridorMedium_geom17);
	corridorMedium_transform18->AddChild(corridorMedium_geom18);
	corridorMedium_transform19->AddChild(corridorMedium_geom19);

	corridorMediumTurn_transform->AddChild(corridorMediumTurn_geom);
	corridorMediumTurn_transform2->AddChild(corridorMediumTurn_geom2);
	corridorMediumTurn_transform3->AddChild(corridorMediumTurn_geom3);
	corridorMediumTurn_transform4->AddChild(corridorMediumTurn_geom4);
	corridorMediumTurn_transform5->AddChild(corridorMediumTurn_geom5);
	corridorMediumTurn_transform6->AddChild(corridorMediumTurn_geom6);

	corridorMediumTJ_transform->AddChild(corridorMediumTJ_geom);

	corridorWideTurn_transform->AddChild(corridorWideTurn_geom);
	corridorWideTurn_transform2->AddChild(corridorWideTurn_geom2);

	hall_transform->AddChild(hall_geom);
	hall_transform2->AddChild(hall_geom2);

	door_transform->AddChild(door_geom);
	doorSide_transform->AddChild(doorSide_geom);
	doorSide_transform2->AddChild(doorSide_geom2);

	door_transform2->AddChild(door_geom2);
	doorSide_transform21->AddChild(doorSide_geom21);
	doorSide_transform22->AddChild(doorSide_geom22);

	door_transform3->AddChild(door_geom3);
	doorSide_transform31->AddChild(doorSide_geom31);
	doorSide_transform32->AddChild(doorSide_geom32);

	door_transform4->AddChild(door_geom4);
	doorSide_transform41->AddChild(doorSide_geom41);
	doorSide_transform42->AddChild(doorSide_geom42);

	door_transform5->AddChild(door_geom5);
	doorSide_transform51->AddChild(doorSide_geom51);
	doorSide_transform52->AddChild(doorSide_geom52);

	door_transform6->AddChild(door_geom6);
	doorSide_transform61->AddChild(doorSide_geom61);
	doorSide_transform62->AddChild(doorSide_geom62);

	door_transform7->AddChild(door_geom7);
	doorSide_transform71->AddChild(doorSide_geom71);
	doorSide_transform72->AddChild(doorSide_geom72);

	door_transform8->AddChild(door_geom8);
	doorSide_transform81->AddChild(doorSide_geom81);
	doorSide_transform82->AddChild(doorSide_geom82);

	spikes_transform->AddChild(spikes_geom);
	trap_transform->AddChild(trap_geom);
	spikes_transform2->AddChild(spikes_geom2);
	trap_transform2->AddChild(trap_geom2);
	spikes_transform3->AddChild(spikes_geom3);
	trap_transform3->AddChild(trap_geom3);
	spikes_transform4->AddChild(spikes_geom4);
	trap_transform4->AddChild(trap_geom4);
	spikes_transform5->AddChild(spikes_geom5);
	trap_transform5->AddChild(trap_geom5);
	spikes_transform6->AddChild(spikes_geom6);
	trap_transform6->AddChild(trap_geom6);
	spikes_transform7->AddChild(spikes_geom7);
	trap_transform7->AddChild(trap_geom7);
	spikes_transform8->AddChild(spikes_geom8);
	trap_transform8->AddChild(trap_geom8);
	spikes_transform9->AddChild(spikes_geom9);
	trap_transform9->AddChild(trap_geom9);

	well_transform->AddChild(well_geom);
	totem_transform->AddChild(totem_geom);
	arrow_transform->AddChild(arrow_geom);
	arrow_transform2->AddChild(arrow_geom2);

	well_transform2->AddChild(well_geom2);
	totem_transform2->AddChild(totem_geom2);
	arrow_transform21->AddChild(arrow_geom21);
	arrow_transform22->AddChild(arrow_geom22);

	well_transform3->AddChild(well_geom3);
	totem_transform3->AddChild(totem_geom3);
	arrow_transform31->AddChild(arrow_geom31);
	arrow_transform32->AddChild(arrow_geom32);

	well_transform4->AddChild(well_geom4);
	totem_transform4->AddChild(totem_geom4);
	arrow_transform41->AddChild(arrow_geom41);
	arrow_transform42->AddChild(arrow_geom42);

	pedestal_transform->AddChild(pedestal_geom);
	dragon_transform->AddChild(dragon_geom);
	pedestal_transform2->AddChild(pedestal_geom2);
	dragon_transform2->AddChild(dragon_geom2);

	wall1_transform->AddChild(wall1_geom);
	wallHalf1_transform->AddChild(wallHalf1_geom);
	wallHalf1_transform2->AddChild(wallHalf1_geom2);
	wallHalf1_transform3->AddChild(wallHalf1_geom3);
	wallHalf1_transform4->AddChild(wallHalf1_geom4);
	wallHalf1_transform5->AddChild(wallHalf1_geom5);

	floortiles1_transform->AddChild(floortiles1_geom);
	floortiles1_transform2->AddChild(floortiles1_geom2);
	floortiles1_transform3->AddChild(floortiles1_geom3);
	floortiles1_transform4->AddChild(floortiles1_geom4);
	floortiles1_transform5->AddChild(floortiles1_geom5);

	column_transform->AddChild(column_geom);

	pillar1_transform->AddChild(pillar1_geom);
	// initialize root (sets the parent->child relationships in the tree)
	root->Init();

	root->SetSpotlightShader(spotlight_shader);
	root->SetShadowMapShader(shadowmap_shader);
	root->SetAmbientLightShader(ambient_light_shader);
	root->SetAmbientLightColor(ambient_color);
	root->SetDirectionalLightShader(directionallight_shader);
	root->SetOmniLightShader(omnilight_shader);

	//
	//STATIC TRANSFORMATIONS////////////////////////////////////////////////////////////////////////////////////////////////
	//
	ground_transform->SetTranslation(0.0f, 0.0f, 0.0f);

	//ROOMS
	roomMedium_transform->SetTranslation(0.0f, 0.0f, 0.0f);
	roomMedium_transform->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);
	roomMedium_transform2->SetTranslation(5.0f, 0.0f, -16.0f);

	//
	roomSmall_transform->SetTranslation(5.0f, 0.0f, -1.0f);
	roomSmall_transform->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);
	roomSmall_transform2->SetTranslation(-6.0f, 0.0f, -11.0f);
	roomSmall_transform2->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);

	//
	hall_transform->SetTranslation(1.5f, 0.0f, -8.0f);
	hall_transform->SetRotation(270.0f, 0.0f, 1.0f, 0.0f);
	hall_transform2->SetTranslation(-8.0f, 0.0f, 0.0f);

	//CORRIDORS
	corridorNarrow_transform->SetTranslation(0.0f, 0.0f, -4.0f);
	corridorNarrow_transform2->SetTranslation(5.0f, 0.0f, -4.0f);
	corridorNarrow_transform3->SetTranslation(0.0f, 0.0f, -12.0f);
	corridorNarrow_transform4->SetTranslation(5.0f, 0.0f, -12.0f);
	corridorNarrow_transform5->SetTranslation(-4.0f, 0.0f, -8.0f);
	corridorNarrow_transform5->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform6->SetTranslation(-6.0f, 0.0f, -8.0f);
	corridorNarrow_transform6->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform7->SetTranslation(-6.0f, 0.0f, -14.0f);
	corridorNarrow_transform8->SetTranslation(-4.0f, 0.0f, -16.0f);
	corridorNarrow_transform8->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform9->SetTranslation(-12.0f, 0.0f, 1.5f);
	corridorNarrow_transform9->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform10->SetTranslation(-14.0f, 0.0f, -7.5f);
	corridorNarrow_transform11->SetTranslation(-14.0f, 0.0f, -9.5f);
	corridorNarrow_transform12->SetTranslation(-14.0f, 0.0f, -11.5f);
	corridorNarrow_transform13->SetTranslation(-14.0f, 0.0f, -13.5f);
	corridorNarrow_transform14->SetTranslation(-6.5f, 0.0f, -20.0f);
	corridorNarrow_transform14->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform15->SetTranslation(-4.5f, 0.0f, -20.0f);
	corridorNarrow_transform15->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform16->SetTranslation(-2.5f, 0.0f, -20.0f);
	corridorNarrow_transform16->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform17->SetTranslation(-0.5f, 0.0f, -20.0f);
	corridorNarrow_transform17->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform18->SetTranslation(1.5f, 0.0f, -20.0f);
	corridorNarrow_transform18->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform19->SetTranslation(3.5f, 0.0f, -20.0f);
	corridorNarrow_transform19->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform20->SetTranslation(5.5f, 0.0f, -20.0f);
	corridorNarrow_transform20->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform21->SetTranslation(7.5f, 0.0f, -20.0f);
	corridorNarrow_transform21->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrow_transform22->SetTranslation(9.5f, 0.0f, -20.0f);
	corridorNarrow_transform22->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);

	corridorNarrowTurn_transform->SetTranslation(-4.0f, 0.0f, 1.5f);
	corridorNarrowTurn_transform->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrowTurn_transform2->SetTranslation(-4.0f, 0.0f, -3.5f);
	corridorNarrowTurn_transform2->SetRotation(270.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrowTurn_transform3->SetTranslation(-14.0f, 0.0f, 1.5f);
	corridorNarrowTurn_transform3->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrowTurn_transform4->SetTranslation(-8.0f, 0.0f, -8.0f);
	corridorNarrowTurn_transform5->SetTranslation(-6.0f, 0.0f, -16.0f);
	corridorNarrowTurn_transform6->SetTranslation(-10.0f, 0.0f, -17.5f);
	corridorNarrowTurn_transform7->SetTranslation(-12.0f, 0.0f, -13.5f);
	corridorNarrowTurn_transform7->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);

	corridorNarrowTJ_transform->SetTranslation(-14.0f, 0.0f, -3.5f);
	corridorNarrowTJ_transform->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorNarrowTJ_transform2->SetTranslation(0.0f, 0.0f, -16.0f);

	corridorMedium_transform->SetTranslation(-8.0f, 0.0f, -6.0f);
	corridorMedium_transform2->SetTranslation(-2.5f, 0.0f, -8.0f);
	corridorMedium_transform2->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorMedium_transform3->SetTranslation(-8.0f, 0.0f, 4.0f);
	corridorMedium_transform4->SetTranslation(-6.0f, 0.0f, 6.0f);
	corridorMedium_transform4->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorMedium_transform5->SetTranslation(-4.0f, 0.0f, 6.0f);
	corridorMedium_transform5->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorMedium_transform6->SetTranslation(-2.0f, 0.0f, 6.0f);
	corridorMedium_transform6->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorMedium_transform7->SetTranslation(0.0f, 0.0f, 6.0f);
	corridorMedium_transform7->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorMedium_transform8->SetTranslation(2.0f, 0.0f, 6.0f);
	corridorMedium_transform8->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorMedium_transform9->SetTranslation(7.5f, 0.0f, 4.0f);
	corridorMedium_transform9->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorMedium_transform10->SetTranslation(9.5f, 0.0f, 4.0f);
	corridorMedium_transform10->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorMedium_transform11->SetTranslation(11.5f, 0.0f, 2.0f);
	corridorMedium_transform12->SetTranslation(11.5f, 0.0f, 0.0f);
	corridorMedium_transform13->SetTranslation(11.5f, 0.0f, -2.0f);
	corridorMedium_transform14->SetTranslation(11.5f, 0.0f, -4.0f);
	corridorMedium_transform15->SetTranslation(11.5f, 0.0f, -12.0f);
	corridorMedium_transform16->SetTranslation(11.5f, 0.0f, -14.0f);
	corridorMedium_transform17->SetTranslation(11.5f, 0.0f, -16.0f);
	corridorMedium_transform18->SetTranslation(11.5f, 0.0f, -18.0f);
	corridorMedium_transform19->SetTranslation(7.5f, 0.0f, -8.0f);
	corridorMedium_transform19->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);

	corridorMediumTurn_transform->SetTranslation(11.5f, 0.0f, 4.0f);
	corridorMediumTurn_transform->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);
	corridorMediumTurn_transform2->SetTranslation(5.0f, 0.0f, 6.0f);
	corridorMediumTurn_transform2->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);
	corridorMediumTurn_transform3->SetTranslation(4.5f, 0.0f, 4.0f);
	corridorMediumTurn_transform4->SetTranslation(-8.0f, 0.0f, 6.0f);
	corridorMediumTurn_transform4->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	corridorMediumTurn_transform5->SetTranslation(-8.5f, 0.0f, -19.5f);
	corridorMediumTurn_transform6->SetTranslation(11.5f, 0.0f, -20.0f);
	corridorMediumTurn_transform6->SetRotation(270.0f, 0.0f, 1.0f, 0.0f);

	corridorMediumTJ_transform->SetTranslation(11.5f, 0.0f, -8.0f);
	corridorMediumTJ_transform->SetRotation(-90.0f, 0.0f, 1.0f, 0.0f);

	corridorWideTurn_transform->SetTranslation(-13.0f, 0.0f, -16.5f);
	corridorWideTurn_transform2->SetTranslation(-9.0f, 0.0f, -16.5f);
	corridorWideTurn_transform2->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);

	//DOORS
	door_transform->SetTranslation(-0.4f, 0.0f, -5.0f);//0.0,-5
	doorSide_transform->SetTranslation(-0.5f, 0.0f, -5.0f);
	doorSide_transform2->SetTranslation(0.5f, 0.0f, -5.0f);
	doorSide_transform2->SetRotation(180.0f,0.0f, 1.0f, 0.0f);

	door_transform2->SetTranslation(4.6f, 0.0f, -5.0f);//5,-5
	doorSide_transform21->SetTranslation(4.5f, 0.0f, -5.0f);
	doorSide_transform22->SetTranslation(5.5f, 0.0f, -5.0f);
	doorSide_transform22->SetRotation(180.0f,0.0f, 1.0f, 0.0f);

	door_transform3->SetTranslation(-0.4f, 0.0f, -11.0f);//0.0,-11
	doorSide_transform31->SetTranslation(-0.5f, 0.0f, -11.0f);
	doorSide_transform32->SetTranslation(0.5f, 0.0f, -11.0f);
	doorSide_transform32->SetRotation(180.0f,0.0f, 1.0f, 0.0f);

	door_transform4->SetTranslation(4.6f, 0.0f, -11.0f);//5,-11
	doorSide_transform41->SetTranslation(4.5f, 0.0f, -11.0f);
	doorSide_transform42->SetTranslation(5.5f, 0.0f, -11.0f);
	doorSide_transform42->SetRotation(180.0f,0.0f, 1.0f, 0.0f);

	door_transform5->SetTranslation(-5.0f, 0.0f, 1.1f);//-5.0,+1.5
	door_transform5->SetRotation(270.0f,0.0f, 1.0f, 0.0f);
	doorSide_transform51->SetTranslation(-5.0f, 0.0f, 1.0f);
	doorSide_transform51->SetRotation(270.0f,0.0f, 1.0f, 0.0f);
	doorSide_transform52->SetTranslation(-5.0f, 0.0f, 2.0f);
	doorSide_transform52->SetRotation(90.0f,0.0f, 1.0f, 0.0f);

	door_transform6->SetTranslation(-5.0f, 0.0f, -3.9f);//-5.0,-3.5
	door_transform6->SetRotation(270.0f,0.0f, 1.0f, 0.0f);
	doorSide_transform61->SetTranslation(-5.0f, 0.0f, -4.0f);
	doorSide_transform61->SetRotation(270.0f,0.0f, 1.0f, 0.0f);
	doorSide_transform62->SetTranslation(-5.0f, 0.0f, -3.0f);
	doorSide_transform62->SetRotation(90.0f,0.0f, 1.0f, 0.0f);

	door_transform7->SetTranslation(-11.0f, 0.0f, -3.9f);//-11.0,-3.5
	door_transform7->SetRotation(-90.0f,0.0f, 1.0f, 0.0f);
	doorSide_transform71->SetTranslation(-11.0f, 0.0f, -4.0f);
	doorSide_transform71->SetRotation(270.0f,0.0f, 1.0f, 0.0f);
	doorSide_transform72->SetTranslation(-11.0f, 0.0f, -3.0f);
	doorSide_transform72->SetRotation(90.0f,0.0f, 1.0f, 0.0f);

	door_transform8->SetTranslation(-11.0f, 0.0f, 1.1f);//-11.0,1,5
	door_transform8->SetRotation(-90.0f,0.0f, 1.0f, 0.0f);
	doorSide_transform81->SetTranslation(-11.0f, 0.0f, 1.0f);
	doorSide_transform81->SetRotation(270.0f,0.0f, 1.0f, 0.0f);
	doorSide_transform82->SetTranslation(-11.0f, 0.0f, 2.0f);
	doorSide_transform82->SetRotation(90.0f,0.0f, 1.0f, 0.0f);

	//TRAPS
	spikes_transform->SetTranslation(9.5f, 0.0f, -8.0f);
	spikes_transform->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	trap_transform->SetTranslation(9.5f, 0.0f,-8.0f);
	trap_transform->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);

	spikes_transform2->SetTranslation(10.5f, 0.0f, -20.0f);
	spikes_transform2->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	trap_transform2->SetTranslation(10.5f, 0.0f,-20.0f);
	trap_transform2->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);

	spikes_transform3->SetTranslation(10.0f, 0.0f, 4.25f);
	spikes_transform3->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	trap_transform3->SetTranslation(10.0f, 0.0f, 4.25f);
	trap_transform3->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);

	spikes_transform4->SetTranslation(5.0f, 0.0f, -13.0f);
	trap_transform4->SetTranslation(5.0f, 0.0f,-13.0f);

	spikes_transform5->SetTranslation(-6.0f, 0.0f, -13.0f);
	trap_transform5->SetTranslation(-6.0f, 0.0f,-13.0f);

	spikes_transform6->SetTranslation(-6.5f, 0.0f, -8.0f);
	spikes_transform6->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	trap_transform6->SetTranslation(-6.5f, 0.0f,-8.0f);
	trap_transform6->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);

	spikes_transform7->SetTranslation(-8.0f, 0.0f, 5.0f);
	trap_transform7->SetTranslation(-8.0f, 0.0f, 5.0f);

	spikes_transform8->SetTranslation(-8.5f, 0.0f, -19.5f);
	trap_transform8->SetTranslation(-8.5f, 0.0f, -19.5f);

	spikes_transform9->SetTranslation(-14.0f, 0.0f, -1.0f);
	trap_transform9->SetTranslation(-14.0f, 0.0f,-1.0f);

	//
	well_transform->SetTranslation(-13.0f, 0.0f, -15.5f);
	totem_transform->SetTranslation(-13.0f, 0.0f, -15.5f);
	arrow_transform->SetTranslation(-13.0f, 0.0f, -15.5f);
	arrow_transform->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	arrow_transform2->SetTranslation(-13.0f, 0.0f, -15.5f);
	arrow_transform2->SetRotation(270.0f, 0.0f, 1.0f, 0.0f);

	well_transform2->SetTranslation(5.0f, 0.0f, -16.0f);
	totem_transform2->SetTranslation(5.0f, 0.0f, -16.0f);
	totem_transform2->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	arrow_transform21->SetTranslation(5.0f, 0.0f, -16.0f);
	arrow_transform21->SetRotation(180.0f, 0.0f, 1.0f, 0.0f);
	arrow_transform22->SetTranslation(5.0f, 0.0f, -16.0f);
	arrow_transform22->SetRotation(0.0f, 0.0f, 1.0f, 0.0f);

	well_transform3->SetTranslation(2.5f, 0.0f, -9.0f);
	totem_transform3->SetTranslation(2.5f, 0.0f, -9.0f);
	arrow_transform31->SetTranslation(2.5f, 0.0f, -9.0f);
	arrow_transform31->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	arrow_transform32->SetTranslation(2.5f, 0.0f, -9.0f);
	arrow_transform32->SetRotation(270.0f, 0.0f, 1.0f, 0.0f);

	well_transform4->SetTranslation(5.0f, 0.0f, 6.0f);
	totem_transform4->SetTranslation(5.0f, 0.0f, 6.0f);
	arrow_transform41->SetTranslation(5.0f, 0.0f, 6.0f); 
	arrow_transform41->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	arrow_transform42->SetTranslation(5.0f, 0.0f, 6.0f);
	arrow_transform42->SetRotation(270.0f, 0.0f, 1.0f, 0.0f);

	//TREA
	pedestal_transform->SetTranslation(-4.0f,0.0f,-1.0f);
	dragon_transform->SetTranslation(-4.0f,0.0f,-1.0f);

	pedestal_transform2->SetTranslation(-6.0f,0.0f,-11.0f);
	dragon_transform2->SetTranslation(-6.0f,0.0f,-11.0f);

	//MISC
	wall1_transform->SetTranslation(-3.5f, 0.0f, -1.5f);
	wall1_transform->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);

	wallHalf1_transform->SetTranslation(6.0f, 0.0f, 2.5f);
	wallHalf1_transform2->SetTranslation(3.5f, 0.0f, 7.0f);
	wallHalf1_transform3->SetTranslation(-15.0f, 0.0f, 0.0f);
	wallHalf1_transform3->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	wallHalf1_transform4->SetTranslation(-13.5f, 0.0f, 0.0f);
	wallHalf1_transform4->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);
	wallHalf1_transform5->SetTranslation(-3.5f, 0.0f, 0.0f);
	wallHalf1_transform5->SetRotation(90.0f, 0.0f, 1.0f, 0.0f);

	floortiles1_transform->SetTranslation(6.0f, 0.0f, 4.0f);
	floortiles1_transform2->SetTranslation(3.5f, 0.0f, 6.0f);
	floortiles1_transform3->SetTranslation(-14.0f, 0.0f, 0.0f);
	floortiles1_transform4->SetTranslation(-4.0f, 0.0f, 0.0f);
	floortiles1_transform5->SetTranslation(-4.0f, 0.0f, -1.5f);

	pillar1_transform->SetTranslation(-7.5f, 0.0f, -19.0f);

	column_transform->SetTranslation(-8.0f, 0.0f, -1.0f);
	
	warrior_transform->SetTranslation(myPlayer->myPosition.x, myPlayer->myPosition.y, myPlayer->myPosition.z);

}

bool LoadObjModels()
{
	OBJLoader* objLoader = new OBJLoader();

	// for all scenes
	spherewhiteMesh = objLoader->loadMesh("sphere_white.obj", "..\\..\\Data\\Other", true);
	groundwhiteMesh = objLoader->loadMesh("plane_white.obj", "..\\..\\Data\\Other", true);

	roomMediumMesh = objLoader->loadMesh("Room1_Simple_Medium.obj", "..\\..\\DungeonData", true);
	roomSmallMesh = objLoader->loadMesh("Room1_Simple_Small.obj", "..\\..\\DungeonData", true);

	corridorMediumMesh = objLoader->loadMesh("Corridor1_Medium.obj", "..\\..\\DungeonData", true);
	corridorNarrowMesh = objLoader->loadMesh("Corridor1_Narrow.obj", "..\\..\\DungeonData", true);
	corridorWideMesh = objLoader->loadMesh("Corridor1_Wide.obj", "..\\..\\DungeonData", true);
	//corridorMediumCrossMesh = objLoader->loadMesh("Corridor1_Medium_Cross.obj", "..\\..\\DungeonData", true);
	//corridorNarrowCrossMesh = objLoader->loadMesh("Corridor1_Narrow_Cross.obj", "..\\..\\DungeonData", true);
	corridorMediumTJMesh = objLoader->loadMesh("Corridor1_Medium_T_Junction.obj", "..\\..\\DungeonData", true);
	corridorNarrowTJMesh = objLoader->loadMesh("Corridor1_Narrow_T_Junction.obj", "..\\..\\DungeonData", true);
	corridorMediumTurnMesh = objLoader->loadMesh("Corridor1_Medium_Turn.obj", "..\\..\\DungeonData", true);
	corridorNarrowTurnMesh = objLoader->loadMesh("Corridor1_Narrow_Turn.obj", "..\\..\\DungeonData", true);
	corridorWideTurnMesh = objLoader->loadMesh("Corridor1_Wide_Turn.obj", "..\\..\\DungeonData", true);

	hallMesh = objLoader->loadMesh("Hall1.obj", "..\\..\\DungeonData", true);

	doorMesh = objLoader->loadMesh("Door1.obj", "..\\..\\DungeonData", true);
	doorExteMesh = objLoader->loadMesh("Doorway1_Extension.obj", "..\\..\\DungeonData", true);
	doorSideMesh = objLoader->loadMesh("Doorway1_Side.obj", "..\\..\\DungeonData", true);

	wall1Mesh = objLoader->loadMesh("Wall1_H1.0.obj", "..\\..\\DungeonData", true);
	wallHalf1Mesh = objLoader->loadMesh("Wall1_Half_H1.0.obj", "..\\..\\DungeonData", true);

	columnMesh = objLoader->loadMesh("Column1.obj", "..\\..\\DungeonData", true);
	pillar1Mesh = objLoader->loadMesh("Wall1_Pillar_H1.0.obj", "..\\..\\DungeonData", true);
	arrowMesh = objLoader->loadMesh("Arrow.obj", "..\\..\\DungeonData", true);
	dragonMesh = objLoader->loadMesh("GoldenDragon.obj", "..\\..\\DungeonData", true);
	pedestalMesh = objLoader->loadMesh("Pedestal.obj", "..\\..\\DungeonData", true);
	spikesMesh = objLoader->loadMesh("Spikes.obj", "..\\..\\DungeonData", true);
	trapMesh = objLoader->loadMesh("SpikeTrap.obj", "..\\..\\DungeonData", true);
	bloodMesh = objLoader->loadMesh("BloodFill.obj", "..\\..\\DungeonData", true);
	wellMesh = objLoader->loadMesh("Well.obj", "..\\..\\DungeonData", true);
	totemMesh = objLoader->loadMesh("Totem.obj", "..\\..\\DungeonData", true);
	floortiles1Mesh = objLoader->loadMesh("FloorTiles1.obj", "..\\..\\DungeonData", true);
	//floortiles2Mesh = objLoader->loadMesh("FloorTiles2.obj", "..\\..\\DungeonData", true);
	//floortiles3Mesh = objLoader->loadMesh("FloorTiles3.obj", "..\\..\\DungeonData", true);

	warriorMesh = objLoader->loadMesh("Warrior.obj", "..\\..\\DungeonData", true);

	return true;
}

bool CreateShaders()
{
	// Basic Geometry Shader (the shader with no lighting calculations, similar to the previous labs)
	// The only difference here is that we are storing the shader pointer, the program id and the uniforms in 
	// a struct instead of using global variables
	// All the shaders below are located in the Shaders.h file

	// Basic Geometry shader
	basic_geometry_shader = new BasicGeometryShader();
	basic_geometry_shader->shader = new ShaderGLSL("BasicGeometry");
	// compile
	bool shader_loaded = basic_geometry_shader->shader->LoadAndCompile();
	if (!shader_loaded) return false;
	// get the program id
	basic_geometry_shader->program_id = basic_geometry_shader->shader->GetProgram();
	// check for uniforms
	basic_geometry_shader->uniform_m = glGetUniformLocation(basic_geometry_shader->program_id, "uniform_m");
	basic_geometry_shader->uniform_v = glGetUniformLocation(basic_geometry_shader->program_id, "uniform_v");
	basic_geometry_shader->uniform_p = glGetUniformLocation(basic_geometry_shader->program_id, "uniform_p");
	basic_geometry_shader->uniform_color = glGetUniformLocation(basic_geometry_shader->program_id, "uniform_material_color");

	// these are for the samplers
	basic_geometry_shader->uniform_sampler_diffuse = glGetUniformLocation(basic_geometry_shader->program_id, "uniform_sampler_diffuse");
	basic_geometry_shader->uniform_has_sampler_diffuse = glGetUniformLocation(basic_geometry_shader->program_id, "uniform_has_sampler_diffuse");

	// Spotlight light shader
	// This is used for rendering geometry using a spotlight shader
	spotlight_shader = new SpotLightShader();
	spotlight_shader->shader = new ShaderGLSL("SpotLight");
	// compile
	shader_loaded = spotlight_shader->shader->LoadAndCompile();
	if (!shader_loaded) return false;
	// get the program id
	spotlight_shader->program_id = spotlight_shader->shader->GetProgram();
	// check for uniforms
	spotlight_shader->uniform_m = glGetUniformLocation(spotlight_shader->program_id, "uniform_m");
	spotlight_shader->uniform_v = glGetUniformLocation(spotlight_shader->program_id, "uniform_v");
	spotlight_shader->uniform_p = glGetUniformLocation(spotlight_shader->program_id, "uniform_p");
	spotlight_shader->uniform_color = glGetUniformLocation(spotlight_shader->program_id, "uniform_material_color");
	spotlight_shader->uniform_normal_matrix_ecs = glGetUniformLocation(spotlight_shader->program_id, "uniform_normal_matrix_ecs");
	spotlight_shader->uniform_light_color = glGetUniformLocation(spotlight_shader->program_id, "uniform_light_color");
	spotlight_shader->uniform_light_position_ecs = glGetUniformLocation(spotlight_shader->program_id, "uniform_light_position_ecs");
	spotlight_shader->uniform_light_direction_ecs = glGetUniformLocation(spotlight_shader->program_id, "uniform_light_direction_ecs");

	// these are for the samplers
	spotlight_shader->uniform_sampler_diffuse = glGetUniformLocation(spotlight_shader->program_id, "uniform_sampler_diffuse");
	spotlight_shader->uniform_sampler_normal = glGetUniformLocation(spotlight_shader->program_id, "uniform_sampler_normal");
	spotlight_shader->uniform_sampler_specular = glGetUniformLocation(spotlight_shader->program_id, "uniform_sampler_specular");
	spotlight_shader->uniform_sampler_emission = glGetUniformLocation(spotlight_shader->program_id, "uniform_sampler_emission");
	spotlight_shader->uniform_has_sampler_diffuse = glGetUniformLocation(spotlight_shader->program_id, "uniform_has_sampler_diffuse");
	spotlight_shader->uniform_has_sampler_normal = glGetUniformLocation(spotlight_shader->program_id, "uniform_has_sampler_normal");
	spotlight_shader->uniform_has_sampler_specular = glGetUniformLocation(spotlight_shader->program_id, "uniform_has_sampler_specular");
	spotlight_shader->uniform_has_sampler_emission = glGetUniformLocation(spotlight_shader->program_id, "uniform_has_sampler_emission");

	// these are for the shadow calculations
	spotlight_shader->uniform_sampler_shadow_map = glGetUniformLocation(spotlight_shader->program_id, "uniform_sampler_shadow_map");
	spotlight_shader->uniform_view_inverse = glGetUniformLocation(spotlight_shader->program_id, "uniform_view_inverse");
	spotlight_shader->uniform_light_view_projection = glGetUniformLocation(spotlight_shader->program_id, "uniform_light_view_projection");	
	
	// Shadow Map shader
	// This is used for rendering the geometry to the shadow map depth buffer
	shadowmap_shader = new ShadowMapShader();
	shadowmap_shader->shader = new ShaderGLSL("BasicShadow");
	// compile
	shader_loaded = shadowmap_shader->shader->LoadAndCompile();
	if (!shader_loaded) return false;
	// get the program id
	shadowmap_shader->program_id = shadowmap_shader->shader->GetProgram();
	// check for uniforms
	shadowmap_shader->uniform_mvp = glGetUniformLocation(shadowmap_shader->program_id, "uniform_mvp");

	// Directional light shader
	// This is used for rendering geometry using a directional light shader
	directionallight_shader = new DirectionalLightShader();
	directionallight_shader->shader = new ShaderGLSL("DirectionalLight");
	// compile
	shader_loaded = directionallight_shader->shader->LoadAndCompile();
	if (!shader_loaded) return false;
	// get the program id
	directionallight_shader->program_id = directionallight_shader->shader->GetProgram();
	// check for uniforms
	directionallight_shader->uniform_m = glGetUniformLocation(directionallight_shader->program_id, "uniform_m");
	directionallight_shader->uniform_v = glGetUniformLocation(directionallight_shader->program_id, "uniform_v");
	directionallight_shader->uniform_p = glGetUniformLocation(directionallight_shader->program_id, "uniform_p");
	directionallight_shader->uniform_color = glGetUniformLocation(directionallight_shader->program_id, "uniform_material_color");
	directionallight_shader->uniform_normal_matrix_ecs = glGetUniformLocation(directionallight_shader->program_id, "uniform_normal_matrix_ecs");
	directionallight_shader->uniform_light_color = glGetUniformLocation(directionallight_shader->program_id, "uniform_light_color");
	directionallight_shader->uniform_light_direction_ecs = glGetUniformLocation(directionallight_shader->program_id, "uniform_light_direction_ecs");

	// Ambient Light shader
	ambient_light_shader = new AmbientLightShader();
	// This is used for rendering geometry using a default ambient light
	ambient_light_shader->shader = new ShaderGLSL("AmbientShader");
	// compile
	shader_loaded = ambient_light_shader->shader->LoadAndCompile();
	if (!shader_loaded) return false;
	// get the program id
	ambient_light_shader->program_id = ambient_light_shader->shader->GetProgram();
	// check for uniforms
	ambient_light_shader->uniform_m = glGetUniformLocation(ambient_light_shader->program_id, "uniform_m");
	ambient_light_shader->uniform_v = glGetUniformLocation(ambient_light_shader->program_id, "uniform_v");
	ambient_light_shader->uniform_p = glGetUniformLocation(ambient_light_shader->program_id, "uniform_p");
	ambient_light_shader->uniform_material_color = glGetUniformLocation(ambient_light_shader->program_id, "uniform_material_color");
	ambient_light_shader->uniform_ambient_light_color = glGetUniformLocation(ambient_light_shader->program_id, "uniform_ambient_light_color");

	// these are for the samplers
	ambient_light_shader->uniform_sampler_diffuse = glGetUniformLocation(ambient_light_shader->program_id, "uniform_sampler_diffuse");
	ambient_light_shader->uniform_has_sampler_diffuse = glGetUniformLocation(ambient_light_shader->program_id, "uniform_has_sampler_diffuse");

		// Omni light shader
	// This is used for rendering geometry using an omnidirectional light shader
	omnilight_shader = new OmniLightShader();
	omnilight_shader->shader = new ShaderGLSL("OmniLight");
	// compile
	shader_loaded = omnilight_shader->shader->LoadAndCompile();
	if (!shader_loaded) return false;
	// get the program id
	omnilight_shader->program_id = omnilight_shader->shader->GetProgram();
	// check for uniforms
	omnilight_shader->uniform_m = glGetUniformLocation(omnilight_shader->program_id, "uniform_m");
	omnilight_shader->uniform_v = glGetUniformLocation(omnilight_shader->program_id, "uniform_v");
	omnilight_shader->uniform_p = glGetUniformLocation(omnilight_shader->program_id, "uniform_p");
	omnilight_shader->uniform_color = glGetUniformLocation(omnilight_shader->program_id, "uniform_material_color");
	omnilight_shader->uniform_normal_matrix_ecs = glGetUniformLocation(omnilight_shader->program_id, "uniform_normal_matrix_ecs");
	omnilight_shader->uniform_light_color = glGetUniformLocation(omnilight_shader->program_id, "uniform_light_color");
	omnilight_shader->uniform_light_position_ecs = glGetUniformLocation(omnilight_shader->program_id, "uniform_light_position_ecs");

	// all shaders loaded OK
	return true;
}

// Render function. Every time our window has to be drawn, this is called.
void Render(void)
{
	if (root == nullptr) return;

	// Set the rendering mode
	glPolygonMode(GL_FRONT_AND_BACK, rendering_mode);

	// CAMERA SETUP
	world_to_camera_matrix = glm::lookAt(eye, target, up);

	// change the rotation angle for the lights
	// this allows for the lights to be rotated
	//light_rotationY += 0.4f;
	//if (light_rotationY > 360.0f) light_rotationY -= 360.0f;
	//sunlight_rotationY += 3.4f;
	//if (sunlight_rotationY > 360.0f) sunlight_rotationY -= 360.0f;
	//candlelight_rotationY += 0.8f;
	//if (candlelight_rotationY > 360.0f) candlelight_rotationY -= 360.0f;

	sunlight->m_transformed_direction = sunlight->m_initial_direction;
	candlelight->m_tranformed_position = glm::vec4((myPlayer->myPosition + glm::vec3(0.0f,2.0f,0.0f)),1.0f);
	spotlight->m_transformed_position = myPlayer->myPosition + glm::vec3(0.0f,10.0f,0.0f);
	spotlight->m_transformed_target = myPlayer->myPosition;
	spotlight2->m_transformed_position = spotlight2->m_initial_position;
	spotlight2->m_transformed_target = spotlight2->m_initial_target;
	// Uncomment this to rotate light (also need to uncomment the DrawSpotLightSource to get the sphere that rotates the light to rotate as well)
	//spotlight->m_transformed_position = glm::vec3(glm::rotate(light_rotationY, 0.0f, 1.0f, 0.0f) * glm::vec4(spotlight->m_initial_position, 1.0f));

	// Write to Shadow Map FBO
	DrawSceneToShadowFBO();

	// now, render the scene as usual
	SceneGraphDraw();

	// Remember that we are using double-buffering, all the drawing we just did
	// took place in the "hidden" back-buffer. Calling glutSwapBuffers makes the
	// back buffer "visible".
	glutSwapBuffers();     

	glError();
}

// Release all memory allocated by pointers using new
void ReleaseGLUT()
{
	
}

void DrawSceneToShadowFBO()
{
	// switch the rendering to happen on the FBO rather than the default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, shadow_fbo);
	// clear the depth color for this framebuffer
	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Create the worldviewprojection matrix for the light source
	// Again, since a light node is missing, the world transformation needs to be applied
	glm::mat4x4 wld = glm::translate(-myPlayer->myPosition);// * glm::rotate(world_rotate_x, 0.0f, 1.0f, 0.0f);
	spotlight->m_transformed_position = glm::vec3(wld * glm::vec4(myPlayer->myPosition + glm::vec3(0.0f,3.0f,0.0f), 1.0f));
	spotlight->m_transformed_target = glm::vec3(wld * glm::vec4(myPlayer->myPosition, 1.0f));

	// Create the light's world to view space matrix
	// we need to build a "camera" as viewed from the light
	// so we need an up vector, a target and a light "eye" position
	// create the direction vector
	glm::vec3 light_direction = glm::normalize(spotlight->m_transformed_target - spotlight->m_transformed_position);
	
	// this check is simply a sanity check for the internal cross product in glm::lookAt
	// just in case the light direction vector is 0,1,0
	// if it is, the up vector is set to 0,0,1
	glm::vec3 up;
	if (fabs(light_direction.z) < 0.001 && fabs(light_direction.x) < 0.001)
		up = glm::vec3(0,0,1);
	else
		up = glm::vec3(0,1,0);

	// construct the light view matrix that transforms world space to light view space (WCS -> LCS)
	// LCS is the view space of the light, similar to ECS which is the view space for the camera
	glm::mat4x4 world_to_light_view_matrix = glm::lookAt(spotlight->m_transformed_position, spotlight->m_transformed_target, up);

	//float h = spotlight->m_near_range *glm::tan(glm::radians(spotlight->m_aperture * 0.5f));
	//glm::mat4x4 light_projection_matrix = glm::frustum(-h, h, -h, h, spotlight->m_near_range, spotlight->m_far_range);
	// aspect ratio is 1 since both width and height are the same (dimensions of the texture)
	glm::mat4x4 light_projection_matrix = glm::perspective(90.0f, 1.0f, spotlight->m_near_range, spotlight->m_far_range);

	// also we need to set a new viewport
	// this viewport has the dimensions of the target depth texture (the shadow texture)
	glViewport(0.0f, 0.0f, shadow_dimensions, shadow_dimensions);

	// now draw the scene as usual

	// USE SCENE GRAPH
	root->SetLightViewMat(world_to_light_view_matrix);
	root->SetLightProjectionMat(light_projection_matrix);

	// also set the world transformations here since they will be retrieved as part of the M matrix in the GeometryNode
	world_transform->SetTranslation(myPlayer->myPosition.x, myPlayer->myPosition.y, myPlayer->myPosition.z);
	world_transform->SetRotation(world_rotate_x, 0.0f, 1.0f, 0.0f);

	// Draw the scene by traversing the scene graph
	// 0 renders the geometry using the spotlight shader
	// 1 renders the geometry to the shadow map
	root->Draw(1);

	// unbind the FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DrawSpotLightSource()
{
	// draw the light source
	// we draw the light source (for the omni light) by translating a small sphere onto the light's position
	// this is the local transform (S T R) which scales, translates and rotates on the translated orbit
	glm::mat4x4 obj = glm::translate(myPlayer->myPosition + glm::vec3(0.0f,3.0f,0.0f)) * glm::scale(0.02f, 0.02f, 0.02f);
	// rotate the sphere so that it follows the light
	//obj = glm::rotate(light_rotationY, 0.0f, 1.0f, 0.0f) * obj;

	// we also need to build the world transform (since we can rotate the scene with the mouse or move the world with the arrow keys)
	glm::mat4x4 wld = glm::translate(-myPlayer->myPosition);// * glm::rotate(world_rotate_x, 0.0f, 1.0f, 0.0f);
	obj = wld * obj;
		
	// draw the mesh
	DrawOGLMesh(spherewhiteMesh, obj);
}

void SceneGraphDraw()
{
	// right before rendering we need to set the target framebuffer to
	// the default framebuffer
	// this is because we used an FBO to switch the rendering to another location
	// set the back buffer as the target framebuffer
	glDrawBuffer(GL_BACK);
	glViewport(0.0f, 0.0f, current_width, current_height);

	// Clear depth and color buffers.
	// We can clear both using an | operand to create the buffer-clear mask.
	// glClear is called here as well because we are working on the default framebuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE,GL_ONE);

	//root->Draw(3);

	DrawSpotLightSource();
	
	// draw the light source for the spot light
	// USE SCENE GRAPH
	root->SetViewMat(world_to_camera_matrix);
	root->SetProjectionMat(perspective_projection_matrix);

	root->SetActiveSpotlight(spotlight);
	root->SetActiveOmnilLight(candlelight);
	root->SetActiveDirectionalLight(sunlight);

	//world_transform->SetRotation(world_rotate_y,0.0f,1.0f,0.0f);

	float timer_elapsed = glutGet(GLUT_ELAPSED_TIME) * 0.05f;
	float timer_elapsed_360 = int(timer_elapsed) % 360;
	timer_elapsed_360 = glm::radians(timer_elapsed);

	//DOORS ////////////////////////////////////////////////////////////////////
	//player position = -door_transform
	//8  -90
	//7  -90
	//6  270
	//5  270
	//1
	door_dist = abs(door_transform->GetTranslation().z + myPlayer->myPosition.z); 
	if(door_dist < 1.5f)
	{
		door_rotangle += 1.4f;
		if(door_rotangle > 90.0f)
			{door_rotangle = 90.0f;}
		door_transform->SetRotation(door_rotangle, 0.0f,1.0f,0.0f);
	}
	else 
	{
		door_rotangle = 0.0f;
		door_transform->SetRotation(door_rotangle, 0.0f,1.0f,0.0f);
	}
	//2
	door_dist2 = abs(door_transform2->GetTranslation().z + myPlayer->myPosition.z); 
	if(door_dist2 < 1.5f)
	{
		door_rotangle2 += 1.4f;
		if(door_rotangle2 > 90.0f)
			{door_rotangle2 = 90.0f;}
		door_transform2->SetRotation(door_rotangle2, 0.0f,1.0f,0.0f);
	}
	else 
	{
		door_rotangle2 = 0.0f;
		door_transform2->SetRotation(door_rotangle2, 0.0f,1.0f,0.0f);
	}
	//3
	door_dist3 = abs(door_transform3->GetTranslation().z + myPlayer->myPosition.z); 
	if(door_dist3 < 1.5f)
	{
		door_rotangle3 += 1.4f;
		if(door_rotangle3 > 90.0f)
			{door_rotangle3 = 90.0f;}
		door_transform3->SetRotation(door_rotangle3, 0.0f,1.0f,0.0f);
	}
	else 
	{
		door_rotangle3 = 0.0f;
		door_transform3->SetRotation(door_rotangle3, 0.0f,1.0f,0.0f);
	}
	//4
	door_dist4 = abs(door_transform4->GetTranslation().z + myPlayer->myPosition.z); 
	if(door_dist4 < 1.5f)
	{
		door_rotangle4 += 1.4f;
		if(door_rotangle4 > 90.0f)
			{door_rotangle4 = 90.0f;}
		door_transform4->SetRotation(door_rotangle4, 0.0f,1.0f,0.0f);
	}
	else 
	{
		door_rotangle4 = 0.0f;
		door_transform4->SetRotation(door_rotangle4, 0.0f,1.0f,0.0f);
	}
	//5
	door_dist5 = abs(door_transform5->GetTranslation().x + myPlayer->myPosition.x); 
	if(door_dist5 < 1.5f)
	{
		door_rotangle5 += 1.4f;
		if(door_rotangle5 > 360.0f)
			{door_rotangle5 = 360.0f;}
		door_transform5->SetRotation(door_rotangle5, 0.0f,1.0f,0.0f);
	}
	else 
	{
		door_rotangle5 = 270.0f;
		door_transform5->SetRotation(door_rotangle5, 0.0f,1.0f,0.0f);
	}
	//6
	door_dist6 = abs(door_transform6->GetTranslation().x + myPlayer->myPosition.x); 
	if(door_dist6 < 1.5f)
	{
		door_rotangle6 += 1.4f;
		if(door_rotangle6 > 360.0f)
			{door_rotangle6 = 360.0f;}
		door_transform6->SetRotation(door_rotangle6, 0.0f,1.0f,0.0f);
	}
	else 
	{
		door_rotangle6 = 270.0f;
		door_transform6->SetRotation(door_rotangle6, 0.0f,1.0f,0.0f);
	}
	//7
	door_dist7 = abs(door_transform7->GetTranslation().x + myPlayer->myPosition.x); 
	if(door_dist7 < 1.5f)
	{
		door_rotangle7 -= 1.4f;
		if(door_rotangle7 < -180.0f)
			{door_rotangle7 = -180.0f;}
		door_transform7->SetRotation(door_rotangle7, 0.0f,1.0f,0.0f);
	}
	else 
	{
		door_rotangle7 = -90.0f;
		door_transform7->SetRotation(door_rotangle7, 0.0f,1.0f,0.0f);
	}
	//8
	door_dist8 = abs(door_transform8->GetTranslation().x + myPlayer->myPosition.x); 
	if(door_dist8 < 1.5f)
	{
		door_rotangle8 -= 1.4f;
		if(door_rotangle8 < -180.0f)
			{door_rotangle8 = -180.0f;}
		door_transform8->SetRotation(door_rotangle8, 0.0f,1.0f,0.0f);
	}
	else 
	{
		door_rotangle8 = -90.0f;
		door_transform8->SetRotation(door_rotangle8, 0.0f,1.0f,0.0f);
	}

	//TOTEMS ///////////////////////////////////////////////////////////////////
	//arrow_transform41->SetTranslation(5.0f, 0.0f, 6.0f); 
	//arrow_transform21->SetTranslation(5.0f, 0.0f, -16.0f); 
	//arrow_transform31->SetTranslation(2.5f, 0.0f, -9.0f); 
	//arrow_transform->SetTranslation(-13.0f, 0.0f, -15.5f);
	//1
	if (totem_rotangle > 360.0f) totem_rotangle -= 360.0f;
	totem_rotangle += 0.4f;
	totem_transform->SetRotation(totem_rotangle ,0.0f, 1.0f, 0.0f);

	if (int(totem_rotangle)%90 == 0) 
	{
		thrownR = 0;
		thrownL = 0;
		arrowpos = -13.0f;
		arrowpos2 = -13.0f;
	}
	if ((totem_rotangle > 90.0f) && (totem_rotangle < 180.0f) && (thrownR < 1))
	{
		if(arrowpos > -7.5f) 
			{
				thrownR = 1;
			}
		arrowpos+= 0.5f * 0.1f;
		arrow_transform->SetTranslation(arrowpos, 0.0f, -15.0f);
	}
	if ((totem_rotangle > 270.0f) && (thrownR < 1))
	{
		if(arrowpos > -7.5f) 
			{
				thrownR = 1;
			}
		arrowpos+= 0.5f * 0.1f;
		arrow_transform->SetTranslation(arrowpos, 0.0f, -15.0f);
	}

	if ((totem_rotangle > 90.0f) && (totem_rotangle < 180.0f) && (thrownL < 1))
	{
		if(arrowpos2 < -14.5f) 
			{
				thrownL = 1;
			}
		arrowpos2 = arrowpos2-(0.5f * 0.1f);
		arrow_transform2->SetTranslation(arrowpos2, 0.0f, -15.0f);
	}
	if ((totem_rotangle > 270.0f) && (thrownL < 1))
	{
		if(arrowpos2 < -14.5f) 
			{
				thrownL = 1;
			}
		arrowpos2 = arrowpos2-(0.5f * 0.1f);
		arrow_transform2->SetTranslation(arrowpos2, 0.0f, -15.0f);
	}
	//2
	totem_transform2->SetRotation((totem_rotangle) ,0.0f, 1.0f, 0.0f);

	if (int(totem_rotangle)%90 == 0) 
	{
		thrownR2 = 0;
		thrownL2 = 0;
		arrowpos21 = -16.0f;
		arrowpos22 = -16.0f;
	}
	if ((totem_rotangle > 180.0f) && (totem_rotangle < 270.0f) && (thrownR2 < 1))
	{
		if(arrowpos21 < -18.5f) 
			{
				thrownR2 = 1;
			}
		arrowpos21 -= 0.5f * 0.1f;
		arrow_transform21->SetTranslation(5.0f, 0.0f, arrowpos21);
	}
	if ((totem_rotangle > 0.0f) && (totem_rotangle < 90.0f) && (thrownR2 < 1))
	{
		if(arrowpos21 < -18.5f) 
			{
				thrownR2 = 1;
			}
		arrowpos21-= 0.5f * 0.1f;
		arrow_transform21->SetTranslation(5.0f, 0.0f, arrowpos21);
	}

	if ((totem_rotangle > 180.0f) && (totem_rotangle < 270.0f) && (thrownL2 < 1))
	{
		if(arrowpos22 > -11.0f) 
			{
				thrownL2 = 1;
			}
		arrowpos22 += 0.5f * 0.1f;
		arrow_transform22->SetTranslation(5.0f, 0.0f, arrowpos22);
	}
	if ((totem_rotangle > 0.0f) && (totem_rotangle < 90.0f)  && (thrownL2 < 1))
	{
		if(arrowpos22 > -11.0f) 
			{
				thrownL2 = 1;
			}
		arrowpos22 += 0.5f * 0.1f;
		arrow_transform22->SetTranslation(5.0f, 0.0f, arrowpos22);
	}
	//3
	totem_transform3->SetRotation(totem_rotangle ,0.0f, 1.0f, 0.0f);

	if (int(totem_rotangle)%90 == 0) 
	{
		thrownR3 = 0;
		thrownL3 = 0;
		arrowpos31 = 2.5f;
		arrowpos32 = 2.5f;
	}
	if ((totem_rotangle > 90.0f) && (totem_rotangle < 180.0f) && (thrownR3 < 1))
	{
		if(arrowpos31 > 6.0f) 
			{
				thrownR3 = 1;
			}
		arrowpos31+= 0.5f * 0.1f;
		arrow_transform31->SetTranslation(arrowpos31, 0.0f, -9.0f);
	}
	if ((totem_rotangle > 270.0f) && (thrownR3< 1))
	{
		if(arrowpos31 > 6.0f) 
			{
				thrownR3 = 1;
			}
		arrowpos31+= 0.5f * 0.1f;
		arrow_transform31->SetTranslation(arrowpos31, 0.0f, -9.0f);
	}

	if ((totem_rotangle > 90.0f) && (totem_rotangle < 180.0f) && (thrownL3 < 1))
	{
		if(arrowpos32 < -1.0f) 
			{
				thrownL3 = 1;
			}
		arrowpos32 = arrowpos32-(0.5f * 0.1f);
		arrow_transform32->SetTranslation(arrowpos32, 0.0f, -9.0f);
	}
	if ((totem_rotangle > 270.0f) && (thrownL3 < 1))
	{
		if(arrowpos32 < -1.0f) 
			{
				thrownL3 = 1;
			}
		arrowpos32 = arrowpos32-(0.5f * 0.1f);
		arrow_transform32->SetTranslation(arrowpos32, 0.0f, -9.0f);
	}
	//4
	totem_transform4->SetRotation(totem_rotangle ,0.0f, 1.0f, 0.0f);

	if (int(totem_rotangle)%90 == 0) 
	{
		thrownR4 = 0;
		thrownL4 = 0;
		arrowpos41 = 5.0f;
		arrowpos42 = 5.0f;
	}
	if ((totem_rotangle > 90.0f) && (totem_rotangle < 180.0f) && (thrownR4 < 1))
	{
		if(arrowpos41 > 6.0f) 
			{
				thrownR4 = 1;
			}
		arrowpos41+= 0.5f * 0.1f;
		arrow_transform41->SetTranslation(arrowpos41, 0.0f, 6.0f);
	}
	if ((totem_rotangle > 270.0f) && (thrownR4 < 1))
	{
		if(arrowpos41 > 6.0f) 
			{
				thrownR4 = 1;
			}
		arrowpos41+= 0.5f * 0.1f;
		arrow_transform41->SetTranslation(arrowpos41, 0.0f, 6.0f);
	}

	if ((totem_rotangle > 90.0f) && (totem_rotangle < 180.0f) && (thrownL4 < 1))
	{
		if(arrowpos42 < -9.0f) 
			{
				thrownL4 = 1;
			}
		arrowpos42 = arrowpos42-(0.5f * 0.1f);
		arrow_transform42->SetTranslation(arrowpos42, 0.0f, 6.0f);
	}
	if ((totem_rotangle > 270.0f) && (thrownL4 < 1))
	{
		if(arrowpos42 < -9.0f) 
			{
				thrownL4 = 1;
			}
		arrowpos42 = arrowpos42-(0.5f * 0.1f);
		arrow_transform42->SetTranslation(arrowpos42, 0.0f, 6.0f);
	}

	arrowdistX = abs(arrow_transform->GetTranslation().x + myPlayer->myPosition.x);
	arrowdistX2 = abs(arrow_transform2->GetTranslation().x + myPlayer->myPosition.x);
	arrowdistX21 = abs(arrow_transform21->GetTranslation().x + myPlayer->myPosition.x);
	arrowdistX22 = abs(arrow_transform22->GetTranslation().x + myPlayer->myPosition.x);
	arrowdistX31 = abs(arrow_transform31->GetTranslation().x + myPlayer->myPosition.x);
	arrowdistX32 = abs(arrow_transform32->GetTranslation().x + myPlayer->myPosition.x);
	arrowdistX41 = abs(arrow_transform41->GetTranslation().x + myPlayer->myPosition.x);
	arrowdistX42 = abs(arrow_transform42->GetTranslation().x + myPlayer->myPosition.x);

	arrowdistZ = abs(arrow_transform->GetTranslation().z + myPlayer->myPosition.z);
	arrowdistZ2 = abs(arrow_transform2->GetTranslation().z + myPlayer->myPosition.z);
	arrowdistZ21 = abs(arrow_transform21->GetTranslation().z + myPlayer->myPosition.z);
	arrowdistZ22 = abs(arrow_transform22->GetTranslation().z + myPlayer->myPosition.z);
	arrowdistZ31 = abs(arrow_transform31->GetTranslation().z + myPlayer->myPosition.z);
	arrowdistZ32 = abs(arrow_transform32->GetTranslation().z + myPlayer->myPosition.z);
	arrowdistZ41 = abs(arrow_transform41->GetTranslation().z + myPlayer->myPosition.z);
	arrowdistZ42 = abs(arrow_transform42->GetTranslation().z + myPlayer->myPosition.z);

	if ((arrowdistX < 0.2) && (arrowdistZ < 0.2))
		myPlayer->Die();
	if ((arrowdistX2 < 0.2) && (arrowdistZ2 < 0.2))
		myPlayer->Die();
	if ((arrowdistX21 < 0.2) && (arrowdistZ21 < 0.2))
		myPlayer->Die();
	if ((arrowdistX22 < 0.2) && (arrowdistZ22 < 0.2))
		myPlayer->Die();
	if ((arrowdistX31 < 0.2) && (arrowdistZ31 < 0.2))
		myPlayer->Die();
	if ((arrowdistX32 < 0.2) && (arrowdistZ32 < 0.2))
		myPlayer->Die();
	if ((arrowdistX41 < 0.2) && (arrowdistZ41 < 0.2))
		myPlayer->Die();
	if ((arrowdistX42 < 0.2) && (arrowdistZ42 < 0.2))
		myPlayer->Die();

	//SPIKES /////////////////////////////////////////////////////////////////////
	spikespos = sin(timer_elapsed_360);

	spikes_transform->SetTranslation(9.5f, spikespos, -8.0f);
	spikes_transform2->SetTranslation(10.5f, spikespos, -20.0f);
	spikes_transform3->SetTranslation(10.0f, spikespos, 4.25f);
	spikes_transform4->SetTranslation(5.0f, spikespos, -13.0f);
	spikes_transform5->SetTranslation(-6.0f, spikespos, -13.0f);
	spikes_transform6->SetTranslation(-6.5f, spikespos, -8.0f);
	spikes_transform7->SetTranslation(-8.0f, spikespos, 5.0f);
	spikes_transform8->SetTranslation(-8.5f, spikespos, -19.5f);
	spikes_transform9->SetTranslation(-14.0f, spikespos, -1.0f);

	if(spikespos>0)
	{
		myPlayer->xz[6][30]=2;//1
		myPlayer->xz[6][31]=2;
		myPlayer->xz[4][54]=2;//2
		myPlayer->xz[4][55]=2;
		myPlayer->xz[5][5]=2;//3
		myPlayer->xz[5][6]=2;
		myPlayer->xz[16][40]=2;//5
		myPlayer->xz[15][40]=2;
		myPlayer->xz[37][40]=2;//5
		myPlayer->xz[38][40]=2;
		myPlayer->xz[38][30]=2;//6
		myPlayer->xz[38][31]=2;
		myPlayer->xz[41][4]=2;//7
		myPlayer->xz[42][4]=2;
		myPlayer->xz[42][53]=2;//8
		myPlayer->xz[43][53]=2;
		myPlayer->xz[54][16]=2;//9
		myPlayer->xz[53][16]=2;

	}
	else
	{
		myPlayer->xz[6][30]=1;//1
		myPlayer->xz[6][31]=1;
		myPlayer->xz[4][54]=1;//2
		myPlayer->xz[4][55]=1;
		myPlayer->xz[5][5]=1;//3
		myPlayer->xz[5][6]=1;
		myPlayer->xz[16][40]=1;//5
		myPlayer->xz[15][40]=1;
		myPlayer->xz[37][40]=1;//5
		myPlayer->xz[38][40]=1;
		myPlayer->xz[38][30]=1;//6
		myPlayer->xz[38][31]=1;
		myPlayer->xz[41][4]=1;//7
		myPlayer->xz[42][4]=1;
		myPlayer->xz[42][53]=1;//8
		myPlayer->xz[43][53]=1;
		myPlayer->xz[54][16]=1;//9
		myPlayer->xz[53][16]=1;
	}

	//warrior_transform->SetTranslation(myPlayer->myPosition.x, myPlayer->myPosition.y, myPlayer->myPosition.z);
	warrior_transform->SetRotation(myPlayer->rotangle, 0.0f,1.0f,0.0f);

	// set current active light
	// in this example, the sunlight is set as the active directional light
	// and the candle light as the active omni light
	// to draw using the directional light, we pass 0 to the Draw function
	// and to draw using the omni light, we pass 1 to the Draw function
	// to draw using multiple lights, we simply need to enable blending
	// and use an additive blend function glBlendFunc(GL_ONE, GL_ONE)
	// since lights are additive

	// Draw the scene by traversing the scene graph
	// 0 renders the geometry using the spotlight shader
	// 1 renders the geometry to the shadow map
	//directi 2
	//ambient 3
	//omni 4
	root->Draw(0);
	glDisable(GL_BLEND);
}

// Keyboard callback function.
// When a key is pressed, GLUT calls this, passing the keys character in the key parameter. 
// The x,y values are the window mouse coordinates when the key was pressed
void Keyboard(unsigned char key, int x, int y)
{
	PrintToOutputWindow("Keyboard");
	switch(key)
	{
	case 'w':
	case 'W':
		myPlayer->moveForward();

		if (myPlayer->Trap())
		{
			PrintToOutputWindow("SPIKES!");
			PrintToOutputWindow("--------");
			PrintToOutputWindow("--------");
			PrintToOutputWindow("CONGRATS YOU ARE DEAD");
			glutLeaveMainLoop();
		}
		if (myPlayer->Win())
		{
			PrintToOutputWindow("--------");
			PrintToOutputWindow("--------");
			PrintToOutputWindow("OK YOU WON");
			glutLeaveMainLoop();
		}
		break;
	case 's':
	case 'S':
		myPlayer->moveBack();

		if (myPlayer->Trap())
		{
			PrintToOutputWindow("SPIKES!");
			PrintToOutputWindow("--------");
			PrintToOutputWindow("--------");
			PrintToOutputWindow("CONGRATS YOU ARE DEAD");
			glutLeaveMainLoop();
		}
		if (myPlayer->Win())
		{
			glutLeaveMainLoop();
			PrintToOutputWindow("YOU WON");
		}
		break;
	case 'a':
	case 'A':
		myPlayer->moveLeft();
		
		target = warrior_transform->GetTranslation();
		eye = warrior_transform->GetTranslation();
		target = target + myPlayer->front + glm::vec3(0.0f,1.2f,0.0f);
		target.x = -target.x;
		target.z = -target.z;
		eye = eye + glm::vec3(0.0f,1.5f,0.0f);
		break;
	case 'd':
	case 'D':
		myPlayer->moveRight();
		
		target = warrior_transform->GetTranslation();
		eye = warrior_transform->GetTranslation();
		target = target + myPlayer->front + glm::vec3(0.0f,1.2f,0.0f);
		target.x = -target.x;
		target.z = -target.z;
		eye = eye + glm::vec3(0.0f,1.5f,0.0f);
		break;
	case 'r':
	case 'R':
		eye.y += 1.0f;
		break;
	case 'f':
	case 'F':
		eye.y -= 1.0f;
		break;
	case 27: // escape
		glutLeaveMainLoop();
		return;
	default:
		return;
	}
}

// Special Keyboard callback function.
// When a special key is pressed (such as arrows or function keys), GLUT calls this, passing the keys character in the key parameter. 
// The x,y values are the window mouse coordinates when the key was pressed
void KeyboardSpecial(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_F1:
		if (rendering_mode == GL_POINT) rendering_mode = GL_LINE;
		else if (rendering_mode == GL_LINE) rendering_mode = GL_FILL;
		else if (rendering_mode == GL_FILL) rendering_mode = GL_POINT;
	case GLUT_KEY_F2:
		break;
	case GLUT_KEY_PAGE_UP:
		eye=myPlayer->eyePosition;
		target=myPlayer->targetPosition;
		break;
	case GLUT_KEY_PAGE_DOWN:
		eye=myPlayer->eyePosition + glm::vec3(0.0f,-0.5f,-1.5f);
		target=myPlayer->targetPosition + glm::vec3(0.0f,-0.4f,-2.0f);
		//world_translate.y -= 1.0f;
		break;
	case GLUT_KEY_UP:
		//eye.z -= 1.0f;
		//world_translate.z += 1.0f;
		break;
	case GLUT_KEY_DOWN:
		//eye.z += 1.0f;
		//world_translate.z -= 1.0f;
		break;
	case GLUT_KEY_LEFT:
		//eye.x -= 1.0f;
		//world_translate.x -= 1.0f;
		break;
	case GLUT_KEY_RIGHT:
		//eye.x += 1.0f;
		//world_translate.x += 1.0f;
		break;
	default:
		return;
	}
}

// This function redraws the scene every 16ms
void TimerSync(int ms)
{
	glutPostRedisplay();
	glutTimerFunc(16, TimerSync, 16);
}

// Mouse callback function
// button refers to the mouse button, state refers to whether button is in up or down state
// and x, y are the new mouse coordinates
void Mouse(int button, int state, int x, int y)
{
	//OutputDebugString("Entered Mouse\n");
	if (state == GLUT_DOWN)
	{
		prev_x = x;
		prev_y = y;
	}
	mouse_button = button;
}

// Method to handle the mouse motion
void MouseMotion(int x, int y)
{
	//OutputDebugString("Entered Mouse Motion\n");
	switch (mouse_button)
	{
	case GLUT_LEFT_BUTTON:
		//?


		glutPostRedisplay();
		break;
	case GLUT_RIGHT_BUTTON:

		//world_rotate_x += (x - prev_x) * 0.1f;
		target.x += (x - prev_x) * 0.01f;
		target.y -= (y - prev_y) * 0.01f;

		prev_x = x;
		prev_y = y;

		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void MouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
	    eye.z += 1.0f;
		target.z += 1.0f;
    }
    else
    {
		eye.z -= 1.0f;
		target.z -= 1.0f;
    }

    return;
}

// Resize callback function
// The parameters indicate the new width and height.
void Resize(int width, int height)
{ 
	// Hack to void zero height
	if (height == 0) height = 1;


	// -------------------------------------------VIEWPORT----------------------------------------------//
	// Set up the viewport (the part of the window where the rendering happens)
	// 0, 0 are the coordinates at the LOWER LEFT corner of the viewport rectangle, in pixels
	// Width, height Specify the width and height of the viewport, in pixels.
	// Typically, this is the size of the window
	// This information will be used for the viewport transformation
	glViewport(0, 0, width, height);
	// -------------------------------------------------------------------------------------------------//
	
	
	// aspect ratio of the window
	float aspect_ratio = (float) width / (float) height;
	// value for the near clipping plane. Anything before that will be clipped
	float near_field_value = 1.0f;
	// value for the far clipping plane. Anything beyond that will be clipped
	float far_field_value = 1000.0f;

	// --------------------------------PERSPECTIVE PROJECTION-------------------------------------------//
	// each time we resize the window, a new projection matrix must be defined
	// use GLM to create a perspective projection matrix (good for 3D rendering)
	// vertical field of view angle
	float vertical_FOV = 30.0f;

	// use GLM to create a perspective projection matrix
	perspective_projection_matrix = glm::perspective(vertical_FOV, aspect_ratio, near_field_value, far_field_value);

	// -------------------------------------------------------------------------------------------------//

	// keep these values globally to reset the viewport after rendering to an FBO
	current_width = width;
	current_height = height;
}

// This is the rendering code (taken from the Draw in the GeometryNode) that renders a mesh
// loaded from an OBJ file
// This is used for the Blending example and since this is shown better without any lighting effects
// we only use the Basic Geometry shader
void DrawOGLMesh(OGLMesh* mesh, glm::mat4x4& object_to_world_transform)
{
	// bind the VAO
	glBindVertexArray(mesh->vao);

	// get the world transformation
	glm::mat4x4& M = object_to_world_transform;
	// get the view transformation
	glm::mat4x4& V = world_to_camera_matrix;
	// get the projection transformation
	glm::mat4x4& P = perspective_projection_matrix;

	std::vector<OBJMaterial*>& materials = mesh->materials;

	// set the shader active
	glUseProgram(basic_geometry_shader->program_id);

	// pass any global shader parameters (independent of material attributes)
	glUniformMatrix4fv(basic_geometry_shader->uniform_m, 1, false, &M[0][0]);
	glUniformMatrix4fv(basic_geometry_shader->uniform_v, 1, false, &V[0][0]);
	glUniformMatrix4fv(basic_geometry_shader->uniform_p, 1, false, &P[0][0]);

	// loop through all the elements
	for (GLint i=0; i < mesh->num_elements; i++)
	{
		if (mesh->elements[i].triangles==0)
			continue;

		// Material and texture goes here.
		int mtrIdx = mesh->elements[i].material_index;
		OBJMaterial& cur_material = *materials[mtrIdx];

		// use the material color
		glUniform4f(basic_geometry_shader->uniform_color, cur_material.m_diffuse[0], cur_material.m_diffuse[1], cur_material.m_diffuse[2], cur_material.m_opacity);

		// draw within a range in the index buffer
		glDrawRangeElements(
			GL_TRIANGLES, 
			mesh->elements[i].start_index, 
			mesh->elements[i].start_index+mesh->elements[i].triangles*3, 
			mesh->elements[i].triangles*3, 
			GL_UNSIGNED_INT, 
			(void*)(mesh->elements[i].start_index*sizeof(GLuint))
			);
	}

	glBindVertexArray(0);
}