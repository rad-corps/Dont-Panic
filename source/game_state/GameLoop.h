#pragma once

#include <vector>
#include "GLAH\GLAHGraphics.h"
#include "../game_objects/Environment.h"
#include "../game_objects/Player.h"
#include "../game_objects/Cannon.h"
#include "../game_objects/Shell.h"
#include "../listeners/CannonListener.h"
#include "GLAH/Vector.h"

class GameLoop : public CannonListener
{
public:
	//updateInterval defaults to 1/60th of a second (60FPS)
	GameLoop(int screenW_, int screenH_, float updateInterval = 0.0166666666666666667f);
	//GameLoop();
	~GameLoop(void);

	void Run();

	virtual void ShotFired(Vector2 pos_, Vector2 velocity_);

private:
	float updateInterval;
	float gameTimer;
	
	Player player;
	Cannon cannon;
	std::vector<Environment> environment;
	std::vector<Shell> shells;

	//updates the entire game world
	void Update(float delta_);
	void Draw();


	//World world;
};

