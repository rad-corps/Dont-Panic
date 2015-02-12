#pragma once

#include "GLAH\GLAHGraphics.h"
#include "UVTranslator.h"

//#include "AIE.h"

enum SPRITE_TYPE
{
	M_P1_STAT = 76,
	M_P1_MOVE1 = 77,
	M_P1_MOVE2 = 78,
	M_P1_CLIMB = 79,
	M_P1_THROW = 80,
	M_P1_DEATH = 81
};

class SpriteSheet
{
public:
	~SpriteSheet(void);
	static void Init();
	static unsigned int Sprite();
	static unsigned int FontSprite();

	static void FillUV(float* uv_, SPRITE_TYPE st_);


private:
	static unsigned int sprite;
	static unsigned int fontSprite;
	static bool init;
	static UVTranslator translator;
	SpriteSheet(void);
//	static GLAHGraphics* gfx;
};

