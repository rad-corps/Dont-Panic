#include "PSGameLoop.h"

//#include "AIE.h"
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
#include "../data/DBLevel.h"
#include "PSMainMenu.h"

//GameLoop::GameLoop(int screenW_, int screenH_, float updateInterval_)
//	: updateInterval(updateInterval_)
//{
//		//\ Lets initialise the AIE Framework and give the window it creates an appropriate title
//	Initialise( screenW_, screenH_, false, "Dont Panic" );
//
//	SpriteSheet::Init();
//
//	DBLevel dbLevel;
//	dbLevel.FillData(1, environment, player);
//
//	//SetBackgroundColour( SColour( 0x00, 0x00, 0x00, 0xFF ) );
//	//AddFont( "./fonts/invaders.fnt" );
//
//	gameTimer = 0.f;
//	
//	cannon.RegisterCannonListener(this);
//}

//PSGameLoop::PSGameLoop()
//{
//	cout << endl << "-------Playing Game: ESC to quit-----------" << endl;
//	DBLevel dbLevel;
//	dbLevel.FillData(5, environment, player);
//
//	gameTimer = 0.f;
//	
//	cannon.RegisterCannonListener(this);
//}

PSGameLoop::PSGameLoop(int level_)
{
	cout << endl << "-------Playing Game: ESC to quit-----------" << endl;
	DBLevel dbLevel;
	dbLevel.FillData(level_, environment, player, cannon);

	enemies.push_back(Enemy(ENEMY_TYPE::SKELETON, DIRECTION::DIR_LEFT, Vector2(500, 200)));

	gameTimer = 0.f;
	
	cannon.RegisterCannonListener(this);
	
}


PSGameLoop::~PSGameLoop(void)
{
	//Shutdown();
}

//void
//GameLoop::Run()
//{
//	do 
//	{
//		
//		//not yet implemented
//		//ClearScreen();
//
//		float delta = GetDeltaTime();
//		
//		//not yet implemented
//		//SetFont( "./fonts/invaders.fnt" );
//
//		//runs at 60FPS
//		gameTimer += delta;
//		if ( gameTimer > updateInterval ) 
//		{
//			gameTimer -= updateInterval;
//			Update(delta);
//		}
//		
//		Draw();
//
//		//not yet implemented
//		//SetFont( nullptr );
//
//	} while ( FrameworkUpdate() == false );
//}

ProgramState* PSGameLoop::Update(float delta_)
{
	//update player
	player.Update(delta_, environment);
	
	//update cannon
	cannon.Update(delta_);

	//update environment
	for ( auto &env : environment )
		env.Update(delta_);		

	//update enemies
	for ( auto &enemy : enemies )
		enemy.Update(delta_, environment);

	
	//update shells
	for (auto &shell : shells )
		shell.Update(delta_);

	if ( IsKeyDown(KEY_ESCAPE) ) 
		return new PSMainMenu();

	return nullptr;
}

//Draw Game
void PSGameLoop::Draw()
{

	for (auto &env : environment )
		env.Draw();		

	for (auto &shell : shells )
		shell.Draw();

		//update enemies
	for ( auto &enemy : enemies )
		enemy.Draw();

	
	cannon.Draw();
	player.Draw();
}

void PSGameLoop::ShotFired(Vector2 pos_, Vector2 velocity_)
{
	//find an inactive shell
	for ( auto &shell : shells )
	{
		if ( !shell.IsActive() )
		{
			shell.Shoot(pos_, velocity_);
			return;
		}
	}

	//if we got this far, than we need to push back a new one	
	shells.push_back(Shell(pos_, velocity_));
}