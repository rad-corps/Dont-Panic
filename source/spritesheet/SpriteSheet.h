#pragma once

#include "AIE.h"

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
};

