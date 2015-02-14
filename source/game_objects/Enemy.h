#pragma once

#include "GameObject.h"
#include <vector>
#include "Platform.h"
#include "Shell.h"

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

enum ENEMY_STATUS
{
	WALKING,
	FALLING,
};

class Enemy : public GameObject
{
public:
	Enemy(ENEMY_TYPE type_, DIRECTION initialDirection_, int col_, int row_);
	Enemy(ENEMY_TYPE type_, DIRECTION initialDirection_, Vector2 pos_);
	Enemy(const Enemy& enemy_); //copy ctor
	~Enemy(void);

	void Update(float delta_, std::vector<Platform>& platform_, std::vector<Shell>& shells_);
	void Draw();

private:

	void GetNextAnimation();
	void UpdateColliders();
	void MoveTo(Vector2 pos_);
	void ApplyGravity();
	void ApplyVelocity(Vector2 velocity_);
	void HandleCollision(std::vector<Platform>& platform_, std::vector<Shell>& shells_);
	void UndoX();
	void UndoY();

	float prevY;
	float prevX;

	float walk1[4];
	float walk2[4];
	float walk3[4];
	float* currentAnimation;

	DIRECTION dir;
	ENEMY_STATUS status;

	Vector2 velocity;

	bool xFlip;
	bool onPlatform;
	float timer;

	Rect topCollider;
	Rect bottomCollider;
	Rect leftCollider;
	Rect rightCollider;
};

