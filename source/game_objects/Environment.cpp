#include "Environment.h"
//#include "aie.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"

Environment::Environment(int col_, int row_, ENVIRO_TILE tileType_)
{
//	gfx = GLAHGraphics::Instance();
	width = 32;
	height = 32;
	centre = Vector2(col_ * 32, row_ * 32);

	UVTranslator translator(800, 1280, 16, 16);

	switch ( tileType_ )
	{
	case RED_BRICK_SURFACE :
		translator.GetUV(UV, 4, 0);
		break;
	case ROCK_SURFACE :
		translator.GetUV(UV, 6, 0);
		break;
	}
}


Environment::~Environment(void)
{
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
