#pragma once

#include <vector>
#include "GLAH\GLAHGraphics.h"
#include "../game_objects/Environment.h"
#include "../game_objects/Player.h"
#include "../game_objects/World.h"

class GameLoop
{
public:
	virtual void Update(float delta_);
	virtual void Draw();

	//updateInterval defaults to 1/60th of a second (60FPS)
	GameLoop(int screenW_, int screenH_, float updateInterval = 0.0166666666666666667f);
	//GameLoop();
	~GameLoop(void);

	void Run();

private:
	float updateInterval;
	float gameTimer;
	//Player player;
	//std::vector<Environment> environment;

	World world;
};

