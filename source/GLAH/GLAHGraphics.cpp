//GLAHGraphics.cpp
//Author: Adam Hulbert
//


#include <stdio.h>

#include "../GLAH/GLAHGraphics.h"
#include "../globals/consts.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_gamecontroller.h>
//#include "GLAH/GLAHInput.h"
//#include "GLAH/Shaders.h"
#include <iostream>
//glfw include

//#include "GLAH/SOIL.h"
//#include "GLAH/Vertex.h"
#include <chrono> //std::chrono::time_point
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>


using namespace std::chrono; 

float camX;
float camY;

std::map<SDL_Keycode, bool> keyDownList; //key, isDown
std::map<SDL_GameControllerButton, bool> gcButtonDownList; //button, isDown
std::map<int, bool> msBtnDwn;

//used internally by DrawSprite
//void CreateSpriteVertexData(Vertex* verticesOut_, Vector3 tl, Vector3 tr, Vector3 bl, Vector3 br, float* UV_, bool xFlip_, float alpha_ = 1.0f);

	
//contains additional information about sprite rotation, scale, position etc.
std::map<SDL_Texture*, GLAHEntity> spriteList;

//gamepads
SDL_GameController* gGameController = NULL;
//const int JOYSTICK_DEAD_ZONE = 8000;

InputListener* inputListener;

//GLFWwindow* window;

//SDL Specific
/////////////////////////////
//Main loop flag
bool quit = false;

//Event handler
SDL_Event e;

//The window we'll be rendering to
SDL_Window* window = NULL;
    
//The surface contained by the window
SDL_Surface* screenSurface = NULL;

SDL_Renderer* renderer;

//GLuint VBO;
//GLuint IBO;

//timers for delta time
std::chrono::time_point<high_resolution_clock> timeBegin;
std::chrono::time_point<high_resolution_clock> timeEnd;

double delta;

int Initialise(int a_iWidth, int a_iHeight, bool a_bFullscreen, const char* a_pWindowTitle  )
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER   ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
	else
    {
		//load gamepads
		if( SDL_NumJoysticks() < 1 )
        {
            printf( "Warning: No joysticks connected!\n" );
        }
        else
        {
            //Load joystick
            gGameController = SDL_GameControllerOpen( 0 );
            if( gGameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            }
        }

        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, a_iWidth, a_iHeight, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
		else
        {
			//Create renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            }
			else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0x2C, 0x2C, 0x2C, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }
            }
        }
	}

	//initialise common keys used
	//keyDownList[

	timeBegin = high_resolution_clock::now();

	return 0;
}

void SetBGColour(int r_, int g_, int b_)
{
	SDL_SetRenderDrawColor( renderer, r_, g_, b_, 0xFF );
}

Vector2			GetCameraPos()
{
	return Vector2(camX, camY);
}

void			AddInputListener(InputListener* inputListener_)
{
	inputListener = inputListener_;
}
void			RemoveInputListener()
{
	inputListener = nullptr;
}


SDL_Window*		GetWindow()
{
	return window;
}

Rect			GetScreenRect()
{
	Rect ret;
	ret.centre = Vector2(camX, camY);
	ret.width = SCREEN_W;
	ret.height = SCREEN_H;
	return ret;
}

//unsigned int	GLAHGraphics::CreateSprite	
// textureName_		: filename/path of the texture to load
// width_			: width of texture
// height_			: height of texture
// parentSpriteID_	: sprite ID of sprite to parent to (0 if no parent)
// originOffset_	: the point of rotation, this is relative to the sprites own space. 
//						Default value is Vector3
// colour_			: not implemented
SDL_Texture* CreateSprite	( const char* textureName_, 
									 int width_, int height_, 
									 unsigned int parentSpriteID_, 
									 /*Vector3 originOffset_, */
									 SColour colour_ )
 {
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( textureName_ );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", textureName_, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", textureName_, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

	//Create an entity with position, scale, rotation info
	GLAHEntity glahEntity;
	glahEntity.size.x = (float)width_;
	glahEntity.size.y = (float)height_;
	glahEntity.parentSpriteID = parentSpriteID_;
	//glahEntity.spriteID = newTexture;
	//glahEntity.position = Vector3((float)x_, (float)y_, 1.f);
	//glahEntity.origin = originOffset_;

	//add to the spriteList (map) using the texture_handle as the key
	spriteList[newTexture] = glahEntity;

    return newTexture;
}

//GLAH::DrawSprite ( unsigned int spriteID_)
void DrawSprite(SDL_Texture* sprite_, bool xFlip_, float alpha_, bool effectedByCamera_)
{
	int xpos, ypos;
	//Render texture to screen
	GLAHEntity entity = spriteList[sprite_];

	int breakpointCondition = spriteList[sprite_].size.x;

	SDL_Rect src = { (int)entity.UV[0], (int)entity.UV[1], (int)entity.UV[2], (int)entity.UV[3] };
	
	//destination draw point needs to be -(int)entity.size.x/2 - (int)entity.size.y/2
	
	if ( effectedByCamera_ )
	{
		xpos = (int)entity.position.x - (int)camX + (int)(SCREEN_W * 0.5f) - (int)(entity.size.x * 0.5f);
		ypos = (int)(SCREEN_H * 0.5f) - (int)entity.position.y + (int)camY - (int)(entity.size.y * 0.5f);
	}
	else
	{
		xpos = (int)entity.position.x - (int)(entity.size.x * 0.5f);
		ypos = (int)entity.position.y - (int)(entity.size.y * 0.5f);
	}

	SDL_Rect dst = {xpos, ypos, (int)entity.size.x, (int)entity.size.y };

	

	//flipping horizontally?
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if ( xFlip_ )
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	SDL_RenderCopyEx( renderer, sprite_, &src, &dst, entity.rotation * 57.2957795f, NULL, flip );
}

void			
ScaleSprite( SDL_Texture* sprite_, float scalarX_, float scalarY_ )
{
	spriteList[sprite_].scaleX = scalarX_;
	spriteList[sprite_].scaleY = scalarY_;
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
    CalculateDelta();
	//Update screen
    SDL_RenderPresent( renderer );

	//While application is running
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
		else if( e.type == SDL_CONTROLLERBUTTONDOWN )
        {   
			gcButtonDownList[(SDL_GameControllerButton)e.cbutton.button] = true;
			if ( inputListener != nullptr ) 
			{
				inputListener->GamePadButtonDown((SDL_GameControllerButton)e.cbutton.button);
			}
		}
		else if( e.type == SDL_CONTROLLERBUTTONUP )
        {   
			gcButtonDownList[(SDL_GameControllerButton)e.cbutton.button] = false;
		}
		else if ( e.type == SDL_KEYDOWN ) 
		{
			if ( inputListener != nullptr ) 
			{
				inputListener->KeyDown(e.key.keysym.sym);
				keyDownList[e.key.keysym.sym] = true;
			}
		}
		else if ( e.type == SDL_KEYUP ) 
		{
			if ( inputListener != nullptr ) 
			{
				keyDownList[e.key.keysym.sym] = false;
			}
		}
		else if ( e.type == SDL_MOUSEBUTTONDOWN ) 
		{			
			if ( e.button.button == SDL_BUTTON_LEFT )
			{
				msBtnDwn[0] = true;
			}
			if ( e.button.button == SDL_BUTTON_RIGHT )
			{
				msBtnDwn[1] = true;
			}
			
		}
		else if ( e.type == SDL_MOUSEBUTTONUP ) 
		{
			if ( e.button.button == SDL_BUTTON_LEFT )
			{
				msBtnDwn[0] = false;
			}
			if ( e.button.button == SDL_BUTTON_RIGHT )
			{
				msBtnDwn[1] = false;
			}
		}
    }

    //Clear screen
    SDL_RenderClear( renderer );

	return quit;
}

void Shutdown()
{
	//Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
}





//GLAH::DrawSprite
//spriteID_		: The ID of the sprite to draw
//x_			: the absolute (world space) x coordinate to draw 
//y_			: the absolute (world space) y coordinate to draw 
void MoveSprite(SDL_Texture* sprite_, float x_, float y_)
{
	spriteList[sprite_].position.x = x_;
	spriteList[sprite_].position.y = y_;
}

void MoveCamera	(float xPos_, float yPos_)
{
	camX = xPos_;
	camY = yPos_;
}

//GLAH::DrawSpriteRelative
//spriteID_		: The ID of the sprite to draw
//xMovement_	: The Relative x movement (current x position + xMovement_)
//yMovement_	: The Relative y movement (current y position + yMovement_)
//rotation_		: Amount to rotate sprite by expressed as radians (current rotation + rotation_)
void MoveSpriteRelative(unsigned int spriteID_, float xMovement_, float yMovement_, float rotation_)
{			
	
}

void RotateSpriteRelative(SDL_Texture* sprite_, float rotation_ )
{
	spriteList[sprite_].rotation += rotation_;
}

void RotateSprite(SDL_Texture* sprite_, float rotation_ )
{
	spriteList[sprite_].rotation = rotation_;
	
}

GLAHEntity GetGLAHEntity(SDL_Texture* sprite_)
{
	return spriteList[sprite_];
}

void SetSpriteUVCoordinates	( SDL_Texture* sprite_, float* UVVec4_ )
{
	for ( int i = 0; i < 4; ++i )
	{
		spriteList[sprite_].UV[i] = UVVec4_[i];
	}
	//cout << "stubbed: SetSpriteUVCoordinates" << endl;
}

////GLAH::CreateSpriteVertexData(Vertex* verticesOut_, Vector3 tl, Vector3 tr, Vector3 bl, Vector3 br)
////verticesOut_	: a pointer to the vertex array to write to (must have space for 4 vertices)
////tl			: top left position
////tr			: top right position
////bl			: bottom left position
////br			: bottom right position
//void CreateSpriteVertexData(Vertex* verticesOut_, Vector3 tl, Vector3 tr, Vector3 bl, Vector3 br, float* UV_, bool xFlip_, float alpha_)
//{
//	
//}

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
bool IsKeyDown( SDL_Keycode key_ )
{
	return keyDownList[key_];
}

bool IsGamePadButtonDown(SDL_GameControllerButton button_)
{
	return gcButtonDownList[button_];
}

bool GetMouseButtonDown( int a_iMouseButtonToTest )
{
	return msBtnDwn[a_iMouseButtonToTest];
}

void GetMouseLocation( int& a_iMouseX, int& a_iMouseY )
{
	SDL_GetMouseState( &a_iMouseX, &a_iMouseY );
	a_iMouseY = 768 - a_iMouseY;
	//cout << "mousex: " << x << "  mousey:" << y << endl;
}
//END INPUT HANDLING
///////////////////////////////////////////////////////////////////////