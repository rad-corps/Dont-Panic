#pragma once

#include "GameObject.h"
#include "Platform.h"
#include "Enemy.h"
#include "Goal.h"
#include "../math/Vector.h"
#include "../math/Rect.h"
#include <vector>
#include "GLText.h"

//#include "GLAH\GLAHInput.h"
#include "GLAH\GLAHGraphics.h"


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

	virtual void Update(float delta_, std::vector<Platform>& platform_, std::vector<Enemy>& enemies, Goal& goal_);
	virtual void Draw();

	

private:
	void ApplyVelocity(Vector2 velocity_);
	void MoveTo(Vector2 pos_);
	void UndoX();
	void UndoY();
	void HandleCollision(std::vector<Platform>& platform_, std::vector<Enemy>& enemies, Goal& goal_);
	void HandleInput(float delta_);
	void UpdateAnimation(float delta_);
	void ApplyGravity();
	void UpdateColliders();
	//Vector2 pos;
	float prevY;
	float prevX;
	Vector2 velocity;
	PLAYER_STATUS status;

	Rect topCollider;
	Rect bottomCollider;
	Rect leftCollider;
	Rect rightCollider;
	Rect hitCollider;

	float animStationary[4];
	float animMove1[4];
	float animMove2[4];
	float animMove3[4]; //copy of move1
	float animDead[4];
	float* currentAnimation;

	float animationTimer;

	float FPS;

	bool onPlatform;
	bool faceLeft;
	bool alive;

	GLText playerSpeak;


};

