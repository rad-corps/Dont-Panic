#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
//#include "SpriteFont.h"
#include "Vertex.h"
#include "GLAHEntity.h"
#include "GLAHColour.h"

using namespace std;

typedef enum
{
	/* The unknown key */
	KEY_UNKNOWN           = -1 ,
	MOUSE_LEFT            = 0,
	MOUSE_RIGHT           = 1,
	MOUSE_MIDDLE          = 2,
	KEY_SPACE             = 32 ,
	KEY_APOSTROPHE        = 39 , /* ' */
	KEY_COMMA             = 44 , /* , */
	KEY_MINUS             = 45 , /* - */
	KEY_PERIOD            = 46 , /* . */
	KEY_SLASH             = 47 , /* / */
	KEY_0                 = 48 ,
	KEY_1                 = 49 ,
	KEY_2                 = 50 ,
	KEY_3                 = 51 ,
	KEY_4                 = 52 ,
	KEY_5                 = 53 ,
	KEY_6                 = 54 ,
	KEY_7                 = 55 ,
	KEY_8                 = 56 ,
	KEY_9                 = 57 ,
	KEY_SEMICOLON         = 59 , /* ; */
	KEY_EQUAL             = 61 , /* = */
	KEY_A                 = 65 ,
	KEY_B                 = 66 ,
	KEY_C                 = 67 ,
	KEY_D                 = 68 ,
	KEY_E                 = 69 ,
	KEY_F                 = 70 ,
	KEY_G                 = 71 ,
	KEY_H                 = 72 ,
	KEY_I                 = 73 ,
	KEY_J                 = 74 ,
	KEY_K                 = 75 ,
	KEY_L                 = 76 ,
	KEY_M                 = 77 ,
	KEY_N                 = 78 ,
	KEY_O                 = 79 ,
	KEY_P                 = 80 ,
	KEY_Q                 = 81 ,
	KEY_R                 = 82 ,
	KEY_S                 = 83 ,
	KEY_T                 = 84 ,
	KEY_U                 = 85 ,
	KEY_V                 = 86 ,
	KEY_W                 = 87 ,
	KEY_X                 = 88 ,
	KEY_Y                 = 89 ,
	KEY_Z                 = 90 ,
	KEY_LEFT_BRACKET      = 91 , /* [ */
	KEY_BACKSLASH         = 92 , /* \ */
	KEY_RIGHT_BRACKET     = 93 , /* ] */
	KEY_GRAVE_ACCENT      = 96 , /* ` */
	KEY_WORLD_1           = 161, /* non-US #1 */
	KEY_WORLD_2           = 162, /* non-US #2 */
	KEY_ESCAPE            = 256,
	KEY_ENTER             = 257,
	KEY_TAB               = 258,
	KEY_BACKSPACE         = 259,
	KEY_INSERT            = 260,
	KEY_DELETE            = 261,
	KEY_RIGHT             = 262,
	KEY_LEFT              = 263,
	KEY_DOWN              = 264,
	KEY_UP                = 265,
	KEY_PAGE_UP           = 266,
	KEY_PAGE_DOWN         = 267,
	KEY_HOME              = 268,
	KEY_END               = 269,
	KEY_CAPS_LOCK         = 280,
	KEY_SCROLL_LOCK       = 281,
	KEY_NUM_LOCK          = 282,
	KEY_PRINT_SCREEN      = 283,
	KEY_PAUSE             = 284,
	KEY_F1                = 290,
	KEY_F2                = 291,
	KEY_F3                = 292,
	KEY_F4                = 293,
	KEY_F5                = 294,
	KEY_F6                = 295,
	KEY_F7                = 296,
	KEY_F8                = 297,
	KEY_F9                = 298,
	KEY_F10               = 299,
	KEY_F11               = 300,
	KEY_F12               = 301,
	KEY_F13               = 302,
	KEY_F14               = 303,
	KEY_F15               = 304,
	KEY_F16               = 305,
	KEY_F17               = 306,
	KEY_F18               = 307,
	KEY_F19               = 308,
	KEY_F20               = 309,
	KEY_F21               = 310,
	KEY_F22               = 311,
	KEY_F23               = 312,
	KEY_F24               = 313,
	KEY_F25               = 314,
	KEY_KP_0              = 320,
	KEY_KP_1              = 321,
	KEY_KP_2              = 322,
	KEY_KP_3              = 323,
	KEY_KP_4              = 324,
	KEY_KP_5              = 325,
	KEY_KP_6              = 326,
	KEY_KP_7              = 327,
	KEY_KP_8              = 328,
	KEY_KP_9              = 329,
	KEY_KP_DECIMAL        = 330,
	KEY_KP_DIVIDE         = 331,
	KEY_KP_MULTIPLY       = 332,
	KEY_KP_SUBTRACT       = 333,
	KEY_KP_ADD            = 334,
	KEY_KP_ENTER          = 335,
	KEY_KP_EQUAL          = 336,
	KEY_LEFT_SHIFT        = 340,
	KEY_LEFT_CONTROL      = 341,
	KEY_LEFT_ALT          = 342,
	KEY_LEFT_SUPER        = 343,
	KEY_RIGHT_SHIFT       = 344,
	KEY_RIGHT_CONTROL     = 345,
	KEY_RIGHT_ALT         = 346,
	KEY_RIGHT_SUPER       = 347,
	KEY_MENU              = 348,
	KEY_LAST              = KEY_MENU
};

	//input handling
 bool			IsKeyDown( int a_iKey );

 void			GetMouseLocation( double& a_iMouseX, double& a_iMouseY );

 bool			GetMouseButtonDown( int a_iMouseButtonToTest );

 bool			GetMouseButtonReleased( int a_iMouseButtonToTest );

	//create a sprite (returns a spriteID)
	//This also creates a GLAHEntity that maps to the sprite ID
	//See GLAHEntity for more info
	unsigned int CreateSprite( const char* textureName_, //the filename/path of the sprite
								int width_, int height_, //width and height in pixels
								unsigned int parentSpriteID_ = 0, //sprite to parent to (0 if none)
								Vector3 originOffset_ = Vector3(0.f,0.f,0.f), //rotation origin (bottom left by default)
								SColour colour_ = SColour(0xFF,0xFF,0xFF,0xFF)); //RGBA (white default)
								

	//Move the sprite in world space to the absolute coordinate xPos_, yPos_
	void			MoveSprite				( unsigned int spriteID_, float xPos_, float yPos_ );
	
	//move the sprite relative to its current position
	void			MoveSpriteRelative		( unsigned int spriteID_, float xMovement_, float yMovement_ = 0.0f, float rotation_ = 0.0f);
	
	//rotate the sprite to this rotation_
	void			RotateSprite					( unsigned int spriteID_, float rotation_ );
	
	//rotate the sprite relative to current rotation
	void			RotateSpriteRelative			( unsigned int spriteID_, float rotation_ );
		
	void			SetSpriteUVCoordinates	( unsigned int a_uiSpriteID, float* a_fUVVec4 );

	//draw the sprite to screen
	void			DrawSprite				( unsigned int spriteID_, bool xFlip_ = false, float alpha_ = 1.0f);

	//Get information about the sprite based on spriteID_ 
	GLAHEntity		GetGLAHEntity			(unsigned int spriteID_);

	//Scale sprite (both x and y scaled by scalar_)
	void			ScaleSprite				( unsigned int spriteID_, float scalar_ );

	bool			FrameworkUpdate();

	int				Initialise( int a_iWidth, int a_iHeight, bool a_bFullscreen = false, const char* a_pWindowTitle = nullptr );

	float			GetDeltaTime();

	GLFWwindow*		GetWindow();

	//NOT YET IMPLEMENTED
	void			ClearScreen();	
	unsigned int	DuplicateSprite			( unsigned int spriteID_ );
	void			DestroySprite			( unsigned int spriteID_ );
	void			SetSpriteColour			( unsigned int spriteID_, SColour& colour_ );
	void			GetSpriteColour			( unsigned int spriteID_, SColour& colour_ );
	void			DrawString(char *, int xPos_, int yPos_, float size_ = 1.f, SColour colour_ = SColour(0xFF,0xFF,0xFF,0xFF));
	void			AddFont( char* fontName_ );
	void			SetFont( char* fontName_ );
	void			RemoveFont( char* fontName_ );
	//END OF NOT YET IMPLEMENTED
