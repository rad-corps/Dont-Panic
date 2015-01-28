#pragma once

#include "Rect.h"

enum ENVIRO_TILE
{
	RED_BRICK_SURFACE,
	ROCK_SURFACE,
};

class Environment :	public Rect
{
public:
	Environment(Vector2 pos_, ENVIRO_TILE tileType_);
	~Environment(void);

	void Draw();
	void Update(float delta_);

	Vector2 pos;

private:
	float UV[4];
	unsigned int sprite;
};

