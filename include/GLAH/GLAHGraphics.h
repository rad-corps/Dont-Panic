#pragma once

#include <map>
#include "Vertex.h"
#include "GLAHEntity.h"
#include "GLAHColour.h"

using namespace std;


	//create a sprite (returns a spriteID)
	//This also creates a GLAHEntity that maps to the sprite ID
	//See GLAHEntity for more info
	unsigned int CreateSprite( const char* textureName_, //the filename/path of the sprite
								int width_, int height_, //width and height in pixels
								int x_ = 0, int y_ = 0,			 //starting positions
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
	void			DrawSprite				( unsigned int spriteID_, bool xFlip_ = false);

	//Get information about the sprite based on spriteID_ 
	GLAHEntity		GetGLAHEntity			(unsigned int spriteID_);

	//Scale sprite (both x and y scaled by scalar_)
	void			ScaleSprite				( unsigned int spriteID_, float scalar_ );

	bool			FrameworkUpdate();

	int				Initialise( int a_iWidth, int a_iHeight, bool a_bFullscreen = false, const char* a_pWindowTitle = nullptr );

	float			GetDeltaTime();

	//NOT YET IMPLEMENTED
	void			ClearScreen();	
	unsigned int	DuplicateSprite			( unsigned int spriteID_ );
	void			DestroySprite			( unsigned int spriteID_ );
	void			SetSpriteColour			( unsigned int spriteID_, SColour& colour_ );
	void			GetSpriteColour			( unsigned int spriteID_, SColour& colour_ );
	void			DrawString( const char* text_, int xPos_, int yPos_, float size_ = 1.f, SColour colour_ = SColour(0xFF,0xFF,0xFF,0xFF));
	void			AddFont( const char* fontName_ );
	void			SetFont( const char* fontName_ );
	void			RemoveFont( const char* fontName_ );
	//END OF NOT YET IMPLEMENTED
