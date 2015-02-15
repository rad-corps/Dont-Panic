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

float* Platform::UV()
{
	return uv;
}

void Platform::InitialiseGraphic()
{
	UVTranslator translator(800, 1280, 16, 16);
	

	//	RED_BRICK_SURFACE,
	//BLUE_BRICK_SURFACE,
	//GREY_BRICK_SURFACE,
	//GOLD_BRICK_SURFACE,
	//GREEN_BRICK_SURFACE,
	//RED2_BRICK_SURFACE,
	//SILVER_BRICK_SURFACE,
	//RED3_BRICK_SURFACE,
	//GOLD2_BRICK_SURFACE,
	//GOLD3_BRICK_SURFACE,

	switch ( tileType )
	{
	case RED_BRICK_SURFACE : translator.GetUV(uv, 4, 0); break;
	case BLUE_BRICK_SURFACE : translator.GetUV(uv, 4, 1);	break;
	case GREY_BRICK_SURFACE : translator.GetUV(uv, 4, 2);	break;
	case GOLD_BRICK_SURFACE : translator.GetUV(uv, 4, 3);	break;
	case GREEN_BRICK_SURFACE : translator.GetUV(uv, 4, 4);	break;
	case RED2_BRICK_SURFACE : translator.GetUV(uv, 4, 5);	break;
	case SILVER_BRICK_SURFACE : translator.GetUV(uv, 4, 6);	break;
	case RED3_BRICK_SURFACE : translator.GetUV(uv, 4, 7);	break;
	case GOLD2_BRICK_SURFACE : translator.GetUV(uv, 4, 8);	break;
	case GOLD3_BRICK_SURFACE : translator.GetUV(uv, 4, 9);	break;
	case ROCK_SURFACE : translator.GetUV(uv, 6, 0);	break;
	case DIRT_SURFACE : translator.GetUV(uv, 6, 1);	break;
	case MUD_SURFACE : translator.GetUV(uv, 6, 2);	break;
	case DENSE_MUD_SURFACE : translator.GetUV(uv, 6, 3);	break;

	case RED_BRICK_BASE : translator.GetUV(uv, 5, 0); break;
	case BLUE_BRICK_BASE : translator.GetUV(uv, 5, 1);	break;
	case GREY_BRICK_BASE : translator.GetUV(uv, 5, 2);	break;
	case GOLD_BRICK_BASE : translator.GetUV(uv, 5, 3);	break;
	case GREEN_BRICK_BASE : translator.GetUV(uv, 5, 4);	break;
	case RED2_BRICK_BASE : translator.GetUV(uv, 5, 5);	break;
	case SILVER_BRICK_BASE : translator.GetUV(uv, 5, 6);	break;
	case RED3_BRICK_BASE : translator.GetUV(uv, 5, 7);	break;
	case GOLD2_BRICK_BASE : translator.GetUV(uv, 5, 8);	break;
	case GOLD3_BRICK_BASE : translator.GetUV(uv, 5, 9);	break;
	case ROCK_BASE : translator.GetUV(uv, 7, 0);	break;
	case DIRT_BASE : translator.GetUV(uv, 7, 1);	break;
	case MUD_BASE : translator.GetUV(uv, 7, 2);	break;
	case DENSE_MUD_BASE : translator.GetUV(uv, 7, 3);	break;
	}
}

void Platform::IncrementTileType()
{
	tileType = (ENVIRO_TILE)((int)tileType + 1);
	
	if ( tileType == ENVIRO_TILE::ENVIRO_TILE_END )
	{
		tileType = ENVIRO_TILE::RED_BRICK_SURFACE;
	}
	InitialiseGraphic();
}

void Platform::DecrementTileType()
{
	tileType = (ENVIRO_TILE)((int)tileType - 1);
	
	if ( (int) tileType < 0 )
	{		
		tileType = ENVIRO_TILE::ENVIRO_TILE_END;
		return DecrementTileType();
	}
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

void Platform::Draw(float alpha_)
{
	SetSpriteUVCoordinates(SpriteSheet::Sprite(), uv);
	MoveSprite(SpriteSheet::Sprite(), centre.x, centre.y);
	DrawSprite(SpriteSheet::Sprite(), false, alpha_);
}

void Platform::Update(float delta_)
{

}
