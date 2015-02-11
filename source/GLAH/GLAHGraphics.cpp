//GLAHGraphics.cpp
//Author: Adam Hulbert
//

#include <GL/glew.h>
#include <GL/wglew.h>
#include "GLAH/GLAHGraphics.h"
//#include "GLAH/GLAHInput.h"
#include "GLAH/Shaders.h"
#include <iostream>
//glfw include
#include <GLFW/glfw3.h>
#include "GLAH/SOIL.h"
#include "GLAH/Vertex.h"
#include <chrono> //std::chrono::time_point
#include <fstream>

using namespace std::chrono; 


//used internally by DrawSprite
void CreateSpriteVertexData(Vertex* verticesOut_, Vector3 tl, Vector3 tr, Vector3 bl, Vector3 br, float* UV_, bool xFlip_);
	
//Create the SpriteMatrix on the fly
Matrix3x3		CreateSpriteTransformation	( unsigned int spriteID_ );
	
//contains additional information about sprite rotation, scale, position etc.
std::map<unsigned int, GLAHEntity> spriteList;

GLFWwindow* window;

GLuint VBO;
GLuint IBO;

//timers for delta time
std::chrono::time_point<high_resolution_clock> timeBegin;
std::chrono::time_point<high_resolution_clock> timeEnd;

double delta;

	

//orthographic projection matrix
Matrix4x4 ortho;


//unsigned int	GLAHGraphics::CreateSprite	
// textureName_		: filename/path of the texture to load
// width_			: width of texture
// height_			: height of texture
// parentSpriteID_	: sprite ID of sprite to parent to (0 if no parent)
// originOffset_	: the point of rotation, this is relative to the sprites own space. 
//						Default value is Vector3
// colour_			: not implemented
unsigned int CreateSprite	( const char* textureName_, 
									 int width_, int height_, 
									 unsigned int parentSpriteID_, 
									 Vector3 originOffset_, 
									 SColour colour_ )
 {
	//Create the texture and get the handle. 
	GLuint texture_handle = SOIL_load_OGL_texture(textureName_, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, NULL);

	//Setup the translation matrix for the sprite
	//Matrix3x3 translation;
	//translation.SetupTranslation(Vector3((float)x_, (float)y_, 0.0f));

	//Create an entity with position, scale, rotation info
	GLAHEntity glahEntity;
	glahEntity.size.x = (float)width_;
	glahEntity.size.y = (float)height_;
	glahEntity.parentSpriteID = parentSpriteID_;
	glahEntity.spriteID = texture_handle;
	//glahEntity.position = Vector3((float)x_, (float)y_, 1.f);
	glahEntity.origin = originOffset_;

	//add to the spriteList (map) using the texture_handle as the key
	spriteList[texture_handle] = glahEntity;
	
	//return the sprites ID/Handle
	return texture_handle;
 }

//returns the transform matrix based on the sprite
Matrix3x3		
CreateSpriteTransformation( unsigned int spriteID_ )
{
	Matrix3x3 translationMat = Matrix3x3::CreateTranslationMatrix(spriteList[spriteID_].position);
	Matrix3x3 rotationMat = Matrix3x3::CreateRotationMatrix(spriteList[spriteID_].rotation);
	Matrix3x3 scaleMatrix = Matrix3x3::CreateScaleMatrix(spriteList[spriteID_].scale);
	return scaleMatrix * rotationMat * translationMat;
}

//modify the scale of the sprite
void			
ScaleSprite( unsigned int spriteID_, float scalar_ )
{
	spriteList[spriteID_].scale = scalar_;
}

void GLAHErroCallback(int errorCode_, const char *errStr_)
{
	cout << "GLFW error: " << errStr_ << endl;
}

//Calculate Delta time (time in miliseconds since last update)
void CalculateDelta()
{
	timeEnd = high_resolution_clock::now();
	delta =  duration_cast<duration<double>>(timeEnd - timeBegin).count();
	timeBegin = high_resolution_clock::now();
}

float GetDeltaTime()
{
	return delta;
}

bool FrameworkUpdate()
{
	if (glfwWindowShouldClose(window))
		return true;

	CalculateDelta();

	//swap front and back buffers
	glfwSwapBuffers(window);
 
    //poll for and process events
	glfwPollEvents();

	glClearColor(0.1, 0.1, 0.1, 0.1);
    glClear(GL_COLOR_BUFFER_BIT);
 
	return false;
}

int Initialise(int a_iWidth, int a_iHeight, bool a_bFullscreen, const char* a_pWindowTitle  )
{
	glfwSetErrorCallback(GLAHErroCallback);

	//Initialise GLFW
    if(!glfwInit())
    {
            return -1;
    }

	//TODO not currently using a_bFullscreen.
    //create a windowed mode window and it's OpenGL context    
    window = glfwCreateWindow(a_iWidth, a_iHeight, a_pWindowTitle, NULL, NULL);

    if(!window)
    {
            glfwTerminate();
            return -1;
    }
 
    //make the window's context current
    glfwMakeContextCurrent(window);

	//initialise input lib
//	GLAHInput* input = GLAHInput::Instance();
//	input->Initialise(window);
 
    //init glew
    if (glewInit() != GLEW_OK)
    {
            // OpenGL didn't start-up! shutdown GLFW and return an error code
            glfwTerminate();
            return -1;
    }

	//create shader program
    GLuint uiProgramFlat = CreateProgram("./Resources/VertexShader.glsl", "./Resources/FlatFragmentShader.glsl");
 
    //find the position of the matrix variable in the shader so we can send info there later
    GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");
 
    //set up the mapping of the screen to pixel co-ordinates. Try changing these values to see what happens.	
    float* orthographicProjection = Matrix4x4::GetOrtho(0.f, (float)a_iWidth, 0.f, (float)a_iHeight, 0.f, 100.f);
	//float* orthographicProjection2 = getOrtho(0, a_iWidth, 0, a_iHeight, 0, 100);
	//orthographicProjection = getOrtho(-1, 1, -1, 1, 0, 100);

	//GenerateVBO();

	//create VBO/IBO	
    glGenBuffers(1, &VBO);                                                                                                                                  //generate VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                                                                             //Binds VBO once
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*4, NULL, GL_STREAM_DRAW);                  //Reserves the memory on graphics card
    //glBindBuffer(GL_ARRAY_BUFFER, NULL);                                                                                                  //We won't unbind as we'll pass data using glBufferSubData
    glEnableVertexAttribArray(0);                                                                                                                           //position - location
    glEnableVertexAttribArray(1);              
	glEnableVertexAttribArray(2); //texture coordinates//colour
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*4));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector4)*2));	

	//turn on transparency
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//texture filtering
	//
 
    //if(IBO == NULL)
    //{
    //        glGenBuffers(1, &IBO);                                                                                                                                  //generate IBO
    //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);                                                     //binds IBO
    //        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(char), NULL, GL_STATIC_DRAW);                    //reserves memory on graphics card
    //        GLvoid *iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);                          //Gets pointer to space on graphics card
 
    //        ((char*)iBuffer)[0] = 3;                                                                                                                        //Populate indices - done here as only required once.
    //        ((char*)iBuffer)[1] = 0;
    //        ((char*)iBuffer)[2] = 2;
    //        ((char*)iBuffer)[3] = 1;
 
    //        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(char), iBuffer, GL_STATIC_DRAW);                 //copy data to graphics card
    //        //No need to unbind as IBO is not changing and will be used every call
    //}	

	glUseProgram(uiProgramFlat); 

	glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

	timeBegin = high_resolution_clock::now();

	return 0;
}

//GLAH::DrawSprite ( unsigned int spriteID_)
void DrawSprite(unsigned int spriteID_, bool xFlip_)
{
	//get width and height variables
	GLAHEntity entity = spriteList[spriteID_];

	float width = entity.size.x;
	float height = entity.size.y;

	//get parent translation (already populated with rotation/position)
	Matrix3x3 parentTrans;
	if ( spriteList[spriteID_].parentSpriteID != 0 )
	{
//		parentTrans = spriteList[entity.parentSpriteID].translation;
		parentTrans = CreateSpriteTransformation(spriteList[spriteID_].parentSpriteID);
	}
	else //if no parent, use an identity matrix for simplicity
	{
		parentTrans.SetupIdentity();
	}
	
	//get the offset from parent and add it to the translatedPosition Vector3
	//Vector3 offset = entity.translation.GetPosition();
	Vector3 offset = entity.position;
	Vector3 translatedPosition = parentTrans * offset;
	
	//translation matrix
	Matrix3x3 translationMat;
	translationMat.SetupTranslation(Vector3(translatedPosition.x, translatedPosition.y, 0.0));
	
	//add the child and parent rotations together
	Matrix3x3 rotationMat;
	float rotation = spriteList[spriteList[spriteID_].parentSpriteID].rotation + spriteList[spriteID_].rotation;
	rotationMat.SetupRotation(rotation);

	//Scale Matric
	Matrix3x3 scaleMatrix;
	scaleMatrix.SetupScale(entity.scale);
	
	//create the final transform
	Matrix3x3 transform = scaleMatrix * rotationMat * translationMat;

	//get the locations of the 4 corners of the sprite considering x, y, width, height and rotation
	Vector3 bl = transform * Vector3(0 - spriteList[spriteID_].origin.x, 0 - spriteList[spriteID_].origin.y, 1);
	Vector3 br = transform * Vector3(width - spriteList[spriteID_].origin.x, 0 - spriteList[spriteID_].origin.y, 1);
	Vector3 tl = transform * Vector3(0 - spriteList[spriteID_].origin.x, height - spriteList[spriteID_].origin.y, 1);
	Vector3 tr = transform * Vector3(width - spriteList[spriteID_].origin.x, height - spriteList[spriteID_].origin.y, 1);

	//create the Vertices and send to the GPU
	Vertex vertices[4];
	CreateSpriteVertexData(vertices, tl, tr, bl, br, spriteList[spriteID_].UV, xFlip_);
	glBindTexture(GL_TEXTURE_2D, spriteID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex)*4, vertices);//Updates VBO's data on the fly 
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

//GLAH::DrawSprite
//spriteID_		: The ID of the sprite to draw
//x_			: the absolute (world space) x coordinate to draw 
//y_			: the absolute (world space) y coordinate to draw 
void MoveSprite(unsigned int spriteID_, float x_, float y_)
{
	spriteList[spriteID_].position = Vector3(x_, y_, 1);
}

//GLAH::DrawSpriteRelative
//spriteID_		: The ID of the sprite to draw
//xMovement_	: The Relative x movement (current x position + xMovement_)
//yMovement_	: The Relative y movement (current y position + yMovement_)
//rotation_		: Amount to rotate sprite by expressed as radians (current rotation + rotation_)
void MoveSpriteRelative(unsigned int spriteID_, float xMovement_, float yMovement_, float rotation_)
{			
	Matrix3x3 spriteMat = CreateSpriteTransformation(spriteID_);
	spriteList[spriteID_].position = spriteMat * Vector3 (xMovement_, yMovement_, 1.f);
	spriteList[spriteID_].rotation += rotation_;
}

void RotateSpriteRelative(unsigned int spriteID_, float rotation_ )
{
	spriteList[spriteID_].rotation += rotation_;
}

void RotateSprite(unsigned int spriteID_, float rotation_ )
{
	spriteList[spriteID_].rotation = rotation_;
}

GLAHEntity GetGLAHEntity(unsigned int spriteID_)
{
	return spriteList[spriteID_];
}

void SetSpriteUVCoordinates	( unsigned int spriteID_, float* UVVec4_ )
{
	for ( int i = 0; i < 4; ++i )
	{
		spriteList[spriteID_].UV[i] = UVVec4_[i];
	}
}

//GLAH::CreateSpriteVertexData(Vertex* verticesOut_, Vector3 tl, Vector3 tr, Vector3 bl, Vector3 br)
//verticesOut_	: a pointer to the vertex array to write to (must have space for 4 vertices)
//tl			: top left position
//tr			: top right position
//bl			: bottom left position
//br			: bottom right position
void CreateSpriteVertexData(Vertex* verticesOut_, Vector3 tl, Vector3 tr, Vector3 bl, Vector3 br, float* UV_, bool xFlip_)
{
	const int VERTICES = 4;
	
	//find the vertices (draw from center)
	verticesOut_[0].position.x = bl.x;              //x - vert0
	verticesOut_[0].position.y = bl.y;             //y - vert0
	verticesOut_[1].position.x = br.x;              //x - vert1
	verticesOut_[1].position.y = br.y;             //y - vert1
	verticesOut_[2].position.x = tr.x;               //x
	verticesOut_[2].position.y = tr.y;             //y
	verticesOut_[3].position.x = tl.x;              //x
	verticesOut_[3].position.y = tl.y;             //y
    for(int i = 0; i < VERTICES; i++)
    {
            verticesOut_[i].position.z = 0.0f;                          //z
			verticesOut_[i].position.w = 1.0f;                          //w
			verticesOut_[i].colour.x = 1.0f;                            //R
            verticesOut_[i].colour.y = 1.0f;                            //G
			verticesOut_[i].colour.z = 1.0f;                            //B
			verticesOut_[i].colour.w = 1.0f;                            //A
    }

	////THIS IS WHERE TO PROGRAM UV'S!!!!!!!!!
	if ( !xFlip_ ) 
	{
		verticesOut_[3].textureCoordinate = Vector2(UV_[0], UV_[1]); //BL
		verticesOut_[0].textureCoordinate = Vector2(UV_[0], UV_[3]); //TL
		verticesOut_[1].textureCoordinate = Vector2(UV_[2], UV_[3]); //TR
		verticesOut_[2].textureCoordinate = Vector2(UV_[2], UV_[1]); //BR
	}
	else
	{
		verticesOut_[3].textureCoordinate = Vector2(UV_[2], UV_[1]); //BR
		verticesOut_[0].textureCoordinate = Vector2(UV_[2], UV_[3]); //TR
		verticesOut_[1].textureCoordinate = Vector2(UV_[0], UV_[3]); //TL
		verticesOut_[2].textureCoordinate = Vector2(UV_[0], UV_[1]); //BL
	}
}

void			ClearScreen(){cout << "not yet implemented" << endl;}	
unsigned int	DuplicateSprite			( unsigned int spriteID_ ){cout << "not yet implemented" << endl; return 0;}
void			DestroySprite			( unsigned int spriteID_ ){cout << "not yet implemented" << endl;}
void			SetSpriteColour			( unsigned int spriteID_, SColour& colour_ ){cout << "not yet implemented" << endl;}
void			GetSpriteColour			( unsigned int spriteID_, SColour& colour_ ){cout << "not yet implemented" << endl;}

void			DrawString( char* text_, int xPos_, int yPos_, float size_, SColour colour_)
{

}

void			AddFont( char* fontName_)
{

}

void			SetFont( char* fontName_ )
{
	
}

void			RemoveFont( char* fontName_ )
{
	
}


//INPUT HANDLING-------------------------------------------------------
///////////////////////////////////////////////////////////////////////
bool IsKeyDown( int key_ )
{
	if (glfwGetKey(window,key_))
		return true;
	return false;
}

bool GetMouseButtonDown( int a_iMouseButtonToTest )
{
	if(glfwGetMouseButton(window, a_iMouseButtonToTest) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

void GetMouseLocation( double& a_iMouseX, double& a_iMouseY )
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &a_iMouseX, &a_iMouseY);
	a_iMouseY = height - a_iMouseY;
}
//END INPUT HANDLING
///////////////////////////////////////////////////////////////////////