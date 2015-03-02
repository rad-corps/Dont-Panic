#pragma once

#include "GameObject.h"
#include "GLAH\GLAHGraphics.h"
#include "GLAH\Vector.h"

enum DECORATION_TYPE
{
	TREE_SM_SIL_1,
	TREE_SM_SIL_2,
	TREE_SM_SIL_3,
	TREE_SM_SIL_4,
	TREE_SM_SIL_5,
	TREE_LG_SILVER,
};

class Decoration :	public Rect
{
public:
	Decoration(int col_, int row_, DECORATION_TYPE decorationType_);
	~Decoration(void);

	void Draw(float alpha_ = 1.0f);
	void Update(float delta_);

	void IncrementTileType();
	void DecrementTileType();
	DECORATION_TYPE DecorationType();

	int Row();
	int Col();

	float* UV();

private:
	void InitialiseGraphic();
	float uv[4];
	unsigned int sprite;
	DECORATION_TYPE decorationType;
	int row;
	int col;
	int scaleX, scaleY;

//	GLAHGraphics * gfx;
};

