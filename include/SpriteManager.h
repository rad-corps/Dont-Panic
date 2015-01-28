#pragma once

//static SpriteManager class 
//contains single sprite sheet in memory
//contains UV coordinates as float arrays for sprites

#include "AIE.h"
#include <map>
#include <vector>

enum UV_TYPE
{
	P_STAT,				//player stationary
	E_1,				//Environment block 1
};

class SpriteManager
{
public:
	static void Init();

	//UV coordinates
	float* UV();

private:
	SpriteManager();					//private CTOR (static class)
	static unsigned int spriteSheet;	//the spritesheet

	static std::map<UV_TYPE, float*> uvMap;
};