#pragma once

#include "../math/Rect.h"
#include "GLAH\GLAHGraphics.h"
#include "GLAH\Vector.h"

enum ENVIRO_TILE
{
	RED_BRICK_SURFACE = 0,
	ROCK_SURFACE = 1,
};

class Environment :	public Rect
{
public:
	Environment(int col_, int row_, ENVIRO_TILE tileType_);
	~Environment(void);

	void Draw();
	void Update(float delta_);

	Vector2 pos;

private:
	float UV[4];
	unsigned int sprite;

//	GLAHGraphics * gfx;
};

