#pragma once

#include "../GLAH/GLAHGraphics.h"
#include "UVTranslator.h"

//#include "AIE.h"

enum SPRITE_TYPE
{
	M_P1_STAT = 76,
	M_P1_MOVE1 = 77,
	M_P1_MOVE2 = 78,
	M_P1_CLIMB = 79,
	M_P1_THROW = 80,
	M_P1_DEATH = 81,
	M_P2_STAT =  82,
	M_P2_MOVE1 = 83,
	M_P2_MOVE2 = 84,
	M_P2_CLIMB = 85,
	M_P2_THROW = 86,
	M_P2_DEATH = 87,
	M_P3_STAT =  88,
	M_P3_MOVE1 = 89,
	M_P3_MOVE2 = 90,
	M_P3_CLIMB = 91,
	M_P3_THROW = 92,
	M_P3_DEATH = 93,
};

class SpriteSheet
{
public:
	~SpriteSheet(void);
	static void Init();
	static SDL_Texture* Sprite();
	static SDL_Texture* FontSprite();
	static SDL_Texture* PlayerSprite();
	static SDL_Texture* PlatformSprite();

	static void FillUV(float* uv_, SPRITE_TYPE st_);


private:
	static SDL_Texture* sprite;
	static SDL_Texture* fontSprite;
	static SDL_Texture* playerSprite;
	static SDL_Texture* platformSprite;
	static bool init;
	static UVTranslator translator;
	SpriteSheet(void);
//	static GLAHGraphics* gfx;
};

