//////////////////////////////////////////////////////////////////////////
//\ Space Invaders Pt 1
//\  This code is the first step in creating a Space Invaders clone, in this tutorial we will be looking at 
//\  setting up some of the on screen elements for a space invaders game and getting our players cannon
//\  moving around the screen and responding to user input.
//\
/////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#if !defined(OSX)
	#include <crtdbg.h>
#endif
#include <iostream>
#include <list>
#include <vector>
#include <string>

#include "Player.h"
#include "Environment.h"
#include "spritesheet\UVTranslator.h"
#include "spritesheet\spritesheet.h"
#include "tests\SpriteSheetTests.h"

//The Original resolution of Space Invaders was 224 x 260 
//For comparison the Nintendo DS has a resolution of 292 x 192
//We're going to render this out at three times the original resolution (because we can)
const int iScreenWidth = 1024;
const int iScreenHeight = 768;

//update at 60-FPS
const float UPDATE_INTERVAL = 0.0166666666666666667f;

int main( int argc, char* argv[] )
{			
	//\ Lets initialise the AIE Framework and give the window it creates an appropriate title
	Initialise( iScreenWidth, iScreenHeight, false, "Gerant Adam Alpha" );

	SpriteSheet::Init();

	SetBackgroundColour( SColour( 0x00, 0x00, 0x00, 0xFF ) );
	AddFont( "./fonts/invaders.fnt" );

	float gameTimer = 0.f;


	Player player;
	vector<Environment> environment;
	environment.push_back(Environment(Vector2(500,50), ENVIRO_TILE::RED_BRICK_SURFACE));
	environment.push_back(Environment(Vector2(200,150), ENVIRO_TILE::ROCK_SURFACE));
		
	do 
	{
		ClearScreen();
		float delta = GetDeltaTime();
		SetFont( "./fonts/invaders.fnt" );

		//runs at 60FPS
		gameTimer += delta;
		if ( gameTimer > UPDATE_INTERVAL ) 
		{
			gameTimer -= UPDATE_INTERVAL;
			player.Update(UPDATE_INTERVAL);
			
			for (auto &env : environment )
			{
				env.Update(UPDATE_INTERVAL);		
			}

		}
		player.Draw();
		for (auto &env : environment )
		{
			env.Draw();		
		}

		SetFont( nullptr );	
	} while ( FrameworkUpdate() == false );
	
	
	Shutdown();

	return 0;
}
