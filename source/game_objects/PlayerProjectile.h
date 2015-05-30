//PlayerProjectile

#include "GameObject.h"

#pragma once

class PlayerProjectile : public GameObject
{

public:
	PlayerProjectile();
	~PlayerProjectile();	

	void Shoot(Vector2 pos_, Vector2 direction_);
	virtual void Draw();
	void Update(float delta_);

private:
	Vector2 velocity;
	//float* sprite;
	static float uv[4];
	static bool init;
};