#include "Platform.h"
//#include "aie.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"
#include "../math/Collision.h"
#include "../globals/consts.h"

Platform::Platform(int col_, int row_, int tileType_) : tileType(tileType_), row(row_), col(col_), scaleX(1), scaleY(1)
{
//	gfx = GLAHGraphics::Instance();
	width = TILE_S;
	height = TILE_S;
	centre = Vector2(col_ * TILE_S, row_ * TILE_S);
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
	UVTranslator translator(48, 64, 16, 16);
	
	//get row and col based on tileType
	int spriteSheetRow = tileType / 3;
	int spriteSheetCol = tileType % 3;

	translator.GetUV(uv, spriteSheetRow, spriteSheetCol);

	//switch ( tileType )
	//{
	////player / enemy can touch
	//case RED_BRICK_SURFACE :	translator.GetUV(uv, 4, 0); break;
	//case BLUE_BRICK_SURFACE :	translator.GetUV(uv, 4, 1);	break;
	//case GREY_BRICK_SURFACE :	translator.GetUV(uv, 4, 2);	break;
	//case GOLD_BRICK_SURFACE :	translator.GetUV(uv, 4, 3);	break;
	//case GREEN_BRICK_SURFACE :	translator.GetUV(uv, 4, 4);	break;
	//case RED2_BRICK_SURFACE :	translator.GetUV(uv, 4, 5);	break;
	//case SILVER_BRICK_SURFACE : translator.GetUV(uv, 4, 6);	break;
	//case RED3_BRICK_SURFACE :	translator.GetUV(uv, 4, 7);	break;
	//case GOLD2_BRICK_SURFACE :	translator.GetUV(uv, 4, 8);	break;
	//case GOLD3_BRICK_SURFACE :	translator.GetUV(uv, 4, 9);	break;
	//case ROCK_SURFACE :			translator.GetUV(uv, 6, 0);	break;
	//case DIRT_SURFACE :			translator.GetUV(uv, 6, 1);	break;
	//case MUD_SURFACE :			translator.GetUV(uv, 6, 2);	break;
	//case DENSE_MUD_SURFACE :	translator.GetUV(uv, 6, 3);	break;

	//case RED_BRICK_BASE :		translator.GetUV(uv, 5, 0); break;
	//case BLUE_BRICK_BASE :		translator.GetUV(uv, 5, 1);	break;
	//case GREY_BRICK_BASE :		translator.GetUV(uv, 5, 2);	break;
	//case GOLD_BRICK_BASE :		translator.GetUV(uv, 5, 3);	break;
	//case GREEN_BRICK_BASE :		translator.GetUV(uv, 5, 4);	break;
	//case RED2_BRICK_BASE :		translator.GetUV(uv, 5, 5);	break;
	//case SILVER_BRICK_BASE :	translator.GetUV(uv, 5, 6);	break;
	//case RED3_BRICK_BASE :		translator.GetUV(uv, 5, 7);	break;
	//case GOLD2_BRICK_BASE :		translator.GetUV(uv, 5, 8);	break;
	//case GOLD3_BRICK_BASE :		translator.GetUV(uv, 5, 9);	break;
	//case ROCK_BASE :			translator.GetUV(uv, 7, 0);	break;
	//case DIRT_BASE :			translator.GetUV(uv, 7, 1);	break;
	//case MUD_BASE :				translator.GetUV(uv, 7, 2);	break;
	//case DENSE_MUD_BASE :		translator.GetUV(uv, 7, 3);	break;

	////decoration tiles
	//case TREE_SM_SIL_1 : 		translator.GetUV(uv, 35, 3); break;
	//case TREE_SM_SIL_2 : 		translator.GetUV(uv, 35, 4); break;
	//case TREE_SM_SIL_3 : 		translator.GetUV(uv, 35, 7); break;
	//case TREE_SM_SIL_4 : 		translator.GetUV(uv, 35, 9); break;
	//case TREE_SM_SIL_5 : 		translator.GetUV(uv, 35, 10); break;
	//case TREE_LG_SILVER: 		translator.GetUV(uv, 34, 5, 2, 2); break;
	//}

}

void Platform::Fall()
{
	isFalling = true;
}

//scroll down
void Platform::IncrementTileType()
{
	++tileType;	
	InitialiseGraphic();
}

//scroll up
void Platform::DecrementTileType()
{
	--tileType;
	InitialiseGraphic();
}

void Platform::SetTileset(int tile_)
{
	tileType = tile_;
	InitialiseGraphic();
}

int Platform::TileType()
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

	SetSpriteUVCoordinates(SpriteSheet::PlatformSprite(), uv);
	MoveSprite(SpriteSheet::PlatformSprite(), centre.x, centre.y);
	//ScaleSprite(SpriteSheet::Sprite(), scaleX, scaleY);
	DrawSprite(SpriteSheet::PlatformSprite(), false, alpha_);
	//ScaleSprite(SpriteSheet::Sprite(), 1, 1);
}

void Platform::Update(float delta_, std::vector<Shell>& shells_)
{
	//if ( !active ) 
	//	return;

	//if ( isFalling ) 
	//{
	//	centre.y -= delta_ * 100;
	//}

	//if ( tileType == ENVIRO_TILE::ROCK_BASE || tileType == ENVIRO_TILE::ROCK_SURFACE ) 
	//{
	//	for ( auto& shell : shells_ )
	//	{
	//		if ( Collision::RectCollision(shell.GetRect(), *this) ) 
	//		{
	//			active = false;
	//			shell.SetActive(false);
	//		}
	//	}
	//}
	//if ( tileType == ENVIRO_TILE::GREY_BRICK_BASE|| tileType == ENVIRO_TILE::GREY_BRICK_SURFACE) 
	//{
	//	for ( auto& shell : shells_ )
	//	{
	//		if ( Collision::RectCollision(shell.GetRect(), *this) ) 
	//		{
	//			shell.SetActive(false);
	//		}
	//	}
	//}
}
