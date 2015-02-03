#pragma once

#include "GLAH\GLAHGraphics.h"

//#include "AIE.h"

class SpriteSheet
{
public:
	~SpriteSheet(void);
	static void Init();
	static unsigned int Sprite();


private:
	static unsigned int sprite;
	static bool init;
	SpriteSheet(void);
//	static GLAHGraphics* gfx;
};

