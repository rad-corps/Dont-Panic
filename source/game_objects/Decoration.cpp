#include "Decoration.h"
//#include "aie.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"

Decoration::Decoration(int col_, int row_, DECORATION_TYPE decorationType_) 
	: scaleX(1), scaleY(1), decorationType(decorationType_)
{
	centre = Vector2(col_ * 32, row_ * 32);
	InitialiseGraphic();		
}


Decoration::~Decoration(void)
{
}

float* Decoration::UV()
{
	return uv;
}

void Decoration::InitialiseGraphic()
{
	UVTranslator translator(800, 1280, 16, 16);

	switch ( decorationType )
	{
		case TREE_SM_SIL_1 : 
			translator.GetUV(uv, 35, 3, scaleX, scaleY); break;
		case TREE_SM_SIL_2 : 
			translator.GetUV(uv, 35, 4, scaleX, scaleY); break;
		case TREE_SM_SIL_3 : 
			translator.GetUV(uv, 35, 7, scaleX, scaleY); break;
		case TREE_SM_SIL_4 : 
			translator.GetUV(uv, 35, 9, scaleX, scaleY); break;
		case TREE_SM_SIL_5 : 
			translator.GetUV(uv, 35, 10, scaleX, scaleY); break;
		case TREE_LG_SILVER: 
			scaleX = 2; scaleY = 2;
			translator.GetUV(uv, 34, 5, scaleX, scaleY); break;
	}
}

void Decoration::IncrementTileType()
{
	//tileType = (ENVIRO_TILE)((int)tileType + 1);
	//
	//if ( tileType == ENVIRO_TILE::ENVIRO_TILE_END )
	//{
	//	tileType = ENVIRO_TILE::RED_BRICK_SURFACE;
	//}
	//InitialiseGraphic();
}

void Decoration::DecrementTileType()
{
	//tileType = (ENVIRO_TILE)((int)tileType - 1);
	//
	//if ( (int) tileType < 0 )
	//{		
	//	tileType = ENVIRO_TILE::ENVIRO_TILE_END;
	//	return DecrementTileType();
	//}
	//InitialiseGraphic();
}

DECORATION_TYPE Decoration::DecorationType()
{
	return decorationType;
}

int Decoration::Row()
{
	return row;
}

int Decoration::Col()
{
	return col;
}

void Decoration::Draw(float alpha_)
{
	SetSpriteUVCoordinates(SpriteSheet::Sprite(), uv);
	ScaleSprite(SpriteSheet::Sprite(), scaleX, scaleY);
	MoveSprite(SpriteSheet::Sprite(), centre.x, centre.y);
	DrawSprite(SpriteSheet::Sprite(), false, alpha_);
	ScaleSprite(SpriteSheet::Sprite(), 1, 1);
}

void Decoration::Update(float delta_)
{

}
