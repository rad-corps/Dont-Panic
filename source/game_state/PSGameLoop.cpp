#include "PSGameLoop.h"

//#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <iostream>
#include <list>
#include <vector>
#include <string>

#include "../game_objects/Player.h"
#include "../game_objects/Platform.h"
#include "../spritesheet/UVTranslator.h"
#include "../spritesheet/SpriteSheet.h"
#include "../data/DBLevel.h"
#include "PSMainMenu.h"


PSGameLoop::PSGameLoop(int level_) : newProgramState(nullptr)
{
	AddInputListener(this);
	cout << "PSGameLoop" << endl;
	level = level_;
	cout << endl << "-------Playing Game: ESC to quit-----------" << endl;
	DBLevel dbLevel;
	dbLevel.FillData(level, platforms, player, cannon, enemySpawners, goal);

	gameTimer = 0.f;
	
	cannon.RegisterCannonListener(this);	

	//maximum of 3 player projectiles on screen at once
	playerProjectiles.resize(3);
	player.InitListener(this);
}


PSGameLoop::~PSGameLoop(void)
{}

void PSGameLoop::KeyDown(SDL_Keycode key_)
{
	if ( key_ == SDLK_ESCAPE ) 
		newProgramState = new PSMainMenu();

	if ( key_ == SDLK_r ) 
		newProgramState = new PSGameLoop(level);
}



ProgramState* PSGameLoop::Update(float delta_)
{
	//update player
	player.Update(delta_, platforms, enemies, goal);

	//update Camera
	camera.pos = player.Pos();
	MoveCamera(camera.pos.x, camera.pos.y);
	
	//update cannon
	//cannon.Update(delta_);

	//update platforms
	for ( auto &env : platforms )
		env.Update(delta_, shells);		

	//update enemies
	for ( auto &enemy : enemies )
		enemy.Update(delta_, platforms, shells);

	//update the spawners
	for ( auto &spawner : enemySpawners )
		spawner.Update(delta_, enemies);
	
	//update shells
	for (auto &shell : shells )
		shell.Update(delta_);

	for ( auto &projectiles : playerProjectiles)
		projectiles.Update(delta_);

	//update goal
	goal.Update(delta_);



	return newProgramState;
}

//Draw Game
void PSGameLoop::Draw()
{

	//cannon.Draw();

	player.Draw();

	for ( auto &projectiles : playerProjectiles)
		projectiles.Draw();

	for ( auto &enemy : enemies )
		enemy.Draw();

	for (auto &env : platforms )
		env.Draw();		

	for (auto &shell : shells )
		shell.Draw();	

	for ( auto &es : enemySpawners )
		es.Draw();

	goal.Draw();	
		
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

void PSGameLoop::PlayerProjectileFired(Vector2 pos_, Vector2 velocity_)
{
	//find an inactive shell
	for ( auto &projectile : playerProjectiles )
	{
		if ( !projectile.IsActive() )
		{
			projectile.Shoot(pos_, velocity_);
			return;
		}
	}
}