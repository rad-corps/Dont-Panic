#pragma once

#include "GameObject.h"
#include <vector>
#include "Environment.h"

enum ENEMY_TYPE
{
	ZOMBIE,
	SKELETON
};

enum DIRECTION
{
	DIR_LEFT,
	DIR_RIGHT
};

class Enemy : public GameObject
{
public:
	Enemy(ENEMY_TYPE type_, DIRECTION initialDirection_, Vector2 pos_);
	Enemy(const Enemy& enemy_); //copy ctor
	~Enemy(void);

	void Update(float delta_, std::vector<Environment>& environment_);
	void Draw();

private:

	void GetNextAnimation();

	float walk1[4];
	float walk2[4];
	float walk3[4];
	float* currentAnimation;

	DIRECTION dir;
	bool xFlip;
	float timer;
};

