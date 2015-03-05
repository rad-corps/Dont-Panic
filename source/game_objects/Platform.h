#pragma once

#include "../math/Rect.h"
#include "GLAH\GLAHGraphics.h"
#include "GLAH\Vector.h"
#include "Shell.h"
#include <vector>

enum ENVIRO_TILE
{
	//player/enemy can touch 
	PLATFORMS_START=-1,
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
	PLATFORMS_END,

	//decoration tiles
	DECORATION_BEGIN=1024,
	TREE_SM_SIL_1,
	TREE_SM_SIL_2,
	TREE_SM_SIL_3,
	TREE_SM_SIL_4,
	TREE_SM_SIL_5,
	TREE_LG_SILVER,
	DECORATION_END,

	//Hazards begin



};

class Platform : public Rect
{
public:
	Platform(int col_, int row_, ENVIRO_TILE tileType_);
	~Platform(void);

	void Draw(float alpha_ = 1.0f);
	void Update(float delta_, std::vector<Shell>& shells_);

	void Fall();
	bool Active();

	void IncrementTileType();
	void DecrementTileType();
	void SetTileset(ENVIRO_TILE);
	ENVIRO_TILE TileType();

	int Row();
	int Col();

	float* UV();

private:
	void InitialiseGraphic();
	float uv[4];
	int scaleX, scaleY;
	unsigned int sprite;
	ENVIRO_TILE tileType;
	int row, col;
	bool isFalling;
	bool active;

//	GLAHGraphics * gfx;
};

