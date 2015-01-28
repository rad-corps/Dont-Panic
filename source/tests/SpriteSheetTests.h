#pragma once

#include "..\spritesheet\UVTranslator.h"

class SpriteSheetTests
{
public:
	SpriteSheetTests(void);
	~SpriteSheetTests(void);

	void RunTest1();
	void RunTest2();

private:
	UVTranslator sheet;
	float myUV[4];
	float expected[4];
};

