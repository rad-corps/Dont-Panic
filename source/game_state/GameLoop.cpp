#include "GameLoop.h"

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

#include "../game_objects/Player.h"
#include "../game_objects/Environment.h"
#include "../spritesheet/UVTranslator.h"
#include "../spritesheet/spritesheet.h"
#include "../tests/SpriteSheetTests.h"


GameLoop::GameLoop(int screenW_, int screenH_, float updateInterval_)
	: updateInterval(updateInterval_)
{
	//\ Lets initialise the AIE Framework and give the window it creates an appropriate title
	Initialise( screenW_, screenH_, false, "Dont Panic" );

	SpriteSheet::Init();

	SetBackgroundColour( SColour( 0x00, 0x00, 0x00, 0xFF ) );
	AddFont( "./fonts/invaders.fnt" );

	gameTimer = 0.f;

	for ( int y = 32; y < 500; y += 32 )
	{
		world.environment.push_back(Environment(Vector2(50,y), ENVIRO_TILE::RED_BRICK_SURFACE));
	}
	for ( int x = 50; x < 1000; x += 32 )
	{
		world.environment.push_back(Environment(Vector2(x,32), ENVIRO_TILE::RED_BRICK_SURFACE));
	}

	for ( int x = 300; x < 800; x += 32 )
	{
		world.environment.push_back(Environment(Vector2(x,128), ENVIRO_TILE::ROCK_SURFACE));
	}
	for ( int y = 128; y < 500; y += 32 )
	{
		world.environment.push_back(Environment(Vector2(800,y), ENVIRO_TILE::ROCK_SURFACE));
	}

}


GameLoop::~GameLoop(void)
{
	Shutdown();
}

void
GameLoop::Run()
{
	do 
	{
		ClearScreen();
		float delta = GetDeltaTime();
		SetFont( "./fonts/invaders.fnt" );

		//runs at 60FPS
		gameTimer += delta;
		if ( gameTimer > updateInterval ) 
		{
			gameTimer -= updateInterval;
			world.player.Update(updateInterval, world.environment);
			
			for (auto &env : world.environment )
			{
				env.Update(updateInterval);		
			}

		}
		
		world.player.Draw();
		for (auto &env : world.environment )
		{
			env.Draw();		
		}

		SetFont( nullptr );	
	} while ( FrameworkUpdate() == false );
}