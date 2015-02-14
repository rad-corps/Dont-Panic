#include "Platform.h"
//#include "aie.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"

Platform::Platform(int col_, int row_, ENVIRO_TILE tileType_) : tileType(tileType_), row(row_), col(col_)
{
//	gfx = GLAHGraphics::Instance();
	width = 32;
	height = 32;
	centre = Vector2(col_ * 32, row_ * 32);
	InitialiseGraphic();
}


Platform::~Platform(void)
{
}

void Platform::InitialiseGraphic()
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

void Platform::IncrementTileType()
{
	tileType = (ENVIRO_TILE)((int)tileType + 1);
	InitialiseGraphic();
}

ENVIRO_TILE Platform::TileType()
{
	return tileType;
}

int Platform::Row()
{
	return row;
}

int Platform::Col()
{
	return col;
}

void Platform::Draw()
{
	SetSpriteUVCoordinates(SpriteSheet::Sprite(), UV);
	MoveSprite(SpriteSheet::Sprite(), centre.x, centre.y);
	DrawSprite(SpriteSheet::Sprite());
}

void Platform::Update(float delta_)
{

}
