#pragma once

#include "../math/Rect.h"
#include "GLAH\GLAHGraphics.h"
#include "GLAH\Vector.h"

enum ENVIRO_TILE
{
	RED_BRICK_SURFACE,
	ROCK_SURFACE,
	ENVIRO_TILE_END
};

class Environment :	public Rect
{
public:
	Environment(int col_, int row_, ENVIRO_TILE tileType_);
	~Environment(void);

	void Draw();
	void Update(float delta_);

	void IncrementTileType();
	ENVIRO_TILE TileType();

	int Row();
	int Col();

private:
	void InitialiseGraphic();
	float UV[4];
	unsigned int sprite;
	ENVIRO_TILE tileType;
	int row;
	int col;

//	GLAHGraphics * gfx;
};

