#include "Environment.h"
//#include "aie.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"

Environment::Environment(int col_, int row_, ENVIRO_TILE tileType_) : tileType(tileType_), row(row_), col(col_)
{
//	gfx = GLAHGraphics::Instance();
	width = 32;
	height = 32;
	centre = Vector2(col_ * 32, row_ * 32);
	InitialiseGraphic();
}


Environment::~Environment(void)
{
}

void Environment::InitialiseGraphic()
{
	UVTranslator translator(800, 1280, 16, 16);
	switch ( tileType )
	{
	case RED_BRICK_SURFACE :
		translator.GetUV(UV, 4, 0);
		break;
	case ROCK_SURFACE :
		translator.GetUV(UV, 6, 0);
		break;
	}
}

void Environment::IncrementTileType()
{
	tileType = (ENVIRO_TILE)((int)tileType + 1);
	InitialiseGraphic();
}

ENVIRO_TILE Environment::TileType()
{
	return tileType;
}

int Environment::Row()
{
	return row;
}

int Environment::Col()
{
	return col;
}

void Environment::Draw()
{
	SetSpriteUVCoordinates(SpriteSheet::Sprite(), UV);
	MoveSprite(SpriteSheet::Sprite(), centre.x, centre.y);
	DrawSprite(SpriteSheet::Sprite());
}

void Environment::Update(float delta_)
{

}
