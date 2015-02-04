#pragma once
#include "GameObject.h"

class Shell : public GameObject
{
public:
	Shell(Vector2 pos_, Vector2 velocity_);
	~Shell(void);

	void Shoot(Vector2 pos_, Vector2 velocity_);

	void Update(float delta_);
	virtual void Draw();

private:
	Vector2 velocity;

	static float uv[4];
	static bool init;
	float timer;
};

