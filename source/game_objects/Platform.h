#pragma once

#include "../math/Rect.h"
#include "GLAH\GLAHGraphics.h"
#include "GLAH\Vector.h"

enum ENVIRO_TILE
{
	RED_BRICK_SURFACE,RED_BRICK_BASE,
	BLUE_BRICK_SURFACE,BLUE_BRICK_BASE,
	GREY_BRICK_SURFACE,GREY_BRICK_BASE,
	GOLD_BRICK_SURFACE,GOLD_BRICK_BASE,
	GREEN_BRICK_SURFACE,GREEN_BRICK_BASE,
	RED2_BRICK_SURFACE,RED2_BRICK_BASE,
	SILVER_BRICK_SURFACE,SILVER_BRICK_BASE,
	RED3_BRICK_SURFACE,RED3_BRICK_BASE,
	GOLD2_BRICK_SURFACE,GOLD2_BRICK_BASE,
	GOLD3_BRICK_SURFACE,GOLD3_BRICK_BASE,
	ROCK_SURFACE,ROCK_BASE,
	DIRT_SURFACE,DIRT_BASE,
	MUD_SURFACE,MUD_BASE,
	DENSE_MUD_SURFACE,DENSE_MUD_BASE,
	ENVIRO_TILE_END
};

class Platform :	public Rect
{
public:
	Platform(int col_, int row_, ENVIRO_TILE tileType_);
	~Platform(void);

	void Draw(float alpha_ = 1.0f);
	void Update(float delta_);

	void IncrementTileType();
	void DecrementTileType();
	ENVIRO_TILE TileType();

	int Row();
	int Col();

	float* UV();

private:
	void InitialiseGraphic();
	float uv[4];
	unsigned int sprite;
	ENVIRO_TILE tileType;
	int row;
	int col;

//	GLAHGraphics * gfx;
};

