#include "Platform.h"
//#include "aie.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"
#include "../math/Collision.h"

Platform::Platform(int col_, int row_, ENVIRO_TILE tileType_) : tileType(tileType_), row(row_), col(col_), scaleX(1), scaleY(1)
{
//	gfx = GLAHGraphics::Instance();
	width = 32;
	height = 32;
	centre = Vector2(col_ * 32, row_ * 32);
	InitialiseGraphic();
	isFalling = false;
	active = true;
}


Platform::~Platform(void)
{
}

float* Platform::UV()
{
	return uv;
}

bool Platform::Active()
{
	return active;
}

void Platform::InitialiseGraphic()
{
	UVTranslator translator(800, 1280, 16, 16);
	scaleX = 1;
	scaleY = 1;
	switch ( tileType )
	{
	//player / enemy can touch
	case RED_BRICK_SURFACE :	translator.GetUV(uv, 4, 0); break;
	case BLUE_BRICK_SURFACE :	translator.GetUV(uv, 4, 1);	break;
	case GREY_BRICK_SURFACE :	translator.GetUV(uv, 4, 2);	break;
	case GOLD_BRICK_SURFACE :	translator.GetUV(uv, 4, 3);	break;
	case GREEN_BRICK_SURFACE :	translator.GetUV(uv, 4, 4);	break;
	case RED2_BRICK_SURFACE :	translator.GetUV(uv, 4, 5);	break;
	case SILVER_BRICK_SURFACE : translator.GetUV(uv, 4, 6);	break;
	case RED3_BRICK_SURFACE :	translator.GetUV(uv, 4, 7);	break;
	case GOLD2_BRICK_SURFACE :	translator.GetUV(uv, 4, 8);	break;
	case GOLD3_BRICK_SURFACE :	translator.GetUV(uv, 4, 9);	break;
	case ROCK_SURFACE :			translator.GetUV(uv, 6, 0);	break;
	case DIRT_SURFACE :			translator.GetUV(uv, 6, 1);	break;
	case MUD_SURFACE :			translator.GetUV(uv, 6, 2);	break;
	case DENSE_MUD_SURFACE :	translator.GetUV(uv, 6, 3);	break;

	case RED_BRICK_BASE :		translator.GetUV(uv, 5, 0); break;
	case BLUE_BRICK_BASE :		translator.GetUV(uv, 5, 1);	break;
	case GREY_BRICK_BASE :		translator.GetUV(uv, 5, 2);	break;
	case GOLD_BRICK_BASE :		translator.GetUV(uv, 5, 3);	break;
	case GREEN_BRICK_BASE :		translator.GetUV(uv, 5, 4);	break;
	case RED2_BRICK_BASE :		translator.GetUV(uv, 5, 5);	break;
	case SILVER_BRICK_BASE :	translator.GetUV(uv, 5, 6);	break;
	case RED3_BRICK_BASE :		translator.GetUV(uv, 5, 7);	break;
	case GOLD2_BRICK_BASE :		translator.GetUV(uv, 5, 8);	break;
	case GOLD3_BRICK_BASE :		translator.GetUV(uv, 5, 9);	break;
	case ROCK_BASE :			translator.GetUV(uv, 7, 0);	break;
	case DIRT_BASE :			translator.GetUV(uv, 7, 1);	break;
	case MUD_BASE :				translator.GetUV(uv, 7, 2);	break;
	case DENSE_MUD_BASE :		translator.GetUV(uv, 7, 3);	break;

	//decoration tiles
	case TREE_SM_SIL_1 : 		translator.GetUV(uv, 35, 3); break;
	case TREE_SM_SIL_2 : 		translator.GetUV(uv, 35, 4); break;
	case TREE_SM_SIL_3 : 		translator.GetUV(uv, 35, 7); break;
	case TREE_SM_SIL_4 : 		translator.GetUV(uv, 35, 9); break;
	case TREE_SM_SIL_5 : 		translator.GetUV(uv, 35, 10); break;
	case TREE_LG_SILVER: 		translator.GetUV(uv, 34, 5, 2, 2); scaleX = 2; scaleY = 2; break;
	}

}

void Platform::Fall()
{
	isFalling = true;
}

//scroll down
void Platform::IncrementTileType()
{
	tileType = (ENVIRO_TILE)((int)tileType + 1);
	
	if ( tileType == ENVIRO_TILE::PLATFORMS_END ) 
	{
		tileType = (ENVIRO_TILE)((int)ENVIRO_TILE::PLATFORMS_START + 1);
	}
	if ( tileType == ENVIRO_TILE::DECORATION_END ) 
	{
		tileType = (ENVIRO_TILE)((int)ENVIRO_TILE::DECORATION_BEGIN + 1);
	}
	InitialiseGraphic();
}

//scroll up
void Platform::DecrementTileType()
{
	tileType = (ENVIRO_TILE)((int)tileType - 1);
	
	if ( tileType == ENVIRO_TILE::PLATFORMS_START )
	{		
		tileType = (ENVIRO_TILE)((int)ENVIRO_TILE::PLATFORMS_END - 1);
	}
	if ( tileType == ENVIRO_TILE::DECORATION_BEGIN)
	{		
		tileType = (ENVIRO_TILE)((int)ENVIRO_TILE::DECORATION_END - 1);
	}
	InitialiseGraphic();
}

void Platform::SetTileset(ENVIRO_TILE tile_)
{
	if ( tile_ == ENVIRO_TILE::PLATFORMS_START ) 
	{
		tileType = (ENVIRO_TILE)((int)ENVIRO_TILE::PLATFORMS_START + 1);
	}
	if ( tile_ == ENVIRO_TILE::DECORATION_BEGIN )
	{
		tileType = (ENVIRO_TILE)((int)ENVIRO_TILE::DECORATION_BEGIN + 1);
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
	if ( !active ) 
		return;

	SetSpriteUVCoordinates(SpriteSheet::Sprite(), uv);
	MoveSprite(SpriteSheet::Sprite(), centre.x, centre.y);
	ScaleSprite(SpriteSheet::Sprite(), scaleX, scaleY);
	DrawSprite(SpriteSheet::Sprite(), false, alpha_);
	ScaleSprite(SpriteSheet::Sprite(), 1, 1);
}

void Platform::Update(float delta_, std::vector<Shell>& shells_)
{
	if ( !active ) 
		return;

	if ( isFalling ) 
	{
		centre.y -= delta_ * 100;
	}

	if ( tileType == ENVIRO_TILE::ROCK_BASE || tileType == ENVIRO_TILE::ROCK_SURFACE ) 
	{
		for ( auto& shell : shells_ )
		{
			if ( Collision::RectCollision(shell.GetRect(), *this) ) 
			{
				active = false;
				shell.SetActive(false);
			}
		}
	}
	if ( tileType == ENVIRO_TILE::GREY_BRICK_BASE|| tileType == ENVIRO_TILE::GREY_BRICK_SURFACE) 
	{
		for ( auto& shell : shells_ )
		{
			if ( Collision::RectCollision(shell.GetRect(), *this) ) 
			{
				shell.SetActive(false);
			}
		}
	}
}
