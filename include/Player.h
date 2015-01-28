#pragma once

#include "GameObject.h"
#include "Vector.h"

enum PLAYER_STATUS
{
	JUMPING,
	STATIONARY,
	RUNNING
};

class Player : public GameObject
{
public:
	Player(void);
	~Player(void);

	virtual void Update(float delta_);
	virtual void Draw();

private:
	Vector2 pos;
	Vector2 velocity;
	PLAYER_STATUS status;

	float animStationary[4];
	float animMove1[4];
	float animMove2[4];
	float animMove3[4]; //copy of move1
	float* currentAnimation;

	float animationTimer;

	float FPS;
};

