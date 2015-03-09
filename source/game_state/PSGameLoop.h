#pragma once

#include <vector>
#include "ProgramState.h"
#include "GLAH/GLAHGraphics.h"
#include "GLAH/InputListener.h"
#include "../game_objects/Platform.h"
#include "../game_objects/Player.h"
#include "../game_objects/Cannon.h"
#include "../game_objects/Shell.h"
#include "../game_objects/Enemy.h"
#include "../game_objects/EnemySpawner.h"
#include "../game_objects/Goal.h"
#include "../listeners/CannonListener.h"
#include "GLAH/Vector.h"

class PSGameLoop : public ProgramState, public CannonListener, public InputListener
{
public:
	//updateInterval defaults to 1/60th of a second (60FPS)
	//GameLoop(int screenW_, int screenH_, float updateInterval = 0.0166666666666666667f);
	PSGameLoop(int startingLevel);
	//PSGameLoop();
	~PSGameLoop(void);

	//void Run();

	//updates the entire game world
	virtual ProgramState* Update(float delta_);
	void Draw();

	virtual void ShotFired(Vector2 pos_, Vector2 velocity_);
	virtual void KeyDown(SDL_Keycode key_);

private:
	//float updateInterval;
	float gameTimer;
	
	Player player;
	Cannon cannon;
	Goal goal;
	int level;


	std::vector<Enemy> enemies;
	std::vector<Platform> platforms;
	std::vector<Shell> shells;
	std::vector<EnemySpawner> enemySpawners;

	ProgramState* newProgramState;
	//World world;
};

