#pragma once

#include "GLAH\GLAHGraphics.h"

//#include "AIE.h"

class SpriteSheet
{
public:
	~SpriteSheet(void);
	static void Init();
	static unsigned int Sprite();
	static unsigned int FontSprite();


private:
	static unsigned int sprite;
	static unsigned int fontSprite;
	static bool init;
	SpriteSheet(void);
//	static GLAHGraphics* gfx;
};

