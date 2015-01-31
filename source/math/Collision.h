//////////////////////////////////////////////////////////////////////////
// Game Code By Adam Hulbert
// 22/12/2014
// Collision.h
/////////////////////////////////////////////////////////////////////////

#pragma once

//#include "GameObject.h"
#include "Rect.h"

enum COLLISION_TYPE
{
	NO_COL = 0x0,
	TOP_COLL = 0x1,
	BOT_COLL = 0x2,
	LEFT_COL = 0x4,
	RIGHT_COL = 0x8,	
};

class Collision
{
public:
	~Collision(void);

	//static bool CheckCollision(GameObject* obj1_, GameObject* obj2_);
	static int RectCollision(Rect r1_, Rect r2_);

private:
	Collision(void);
	
};