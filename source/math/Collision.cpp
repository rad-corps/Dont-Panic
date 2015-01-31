//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// Collision.cpp
/////////////////////////////////////////////////////////////////////////

#include "Collision.h"
#include <iostream>

using namespace std;

Collision::Collision(void)
{
}


Collision::~Collision(void)
{
}
/*
//circle collision between two gameobjects
bool Collision::CheckCollision(GameObject* obj1_, GameObject* obj2_)
{
	if ( !obj1_->IsActive() || !obj2_->IsActive() )
		return false;

	//calculate a slight reduction in radius to account for some collision overlap
	float obj1_radius = obj1_->Width() / 2;
	float obj2_radius = obj2_->Width() / 2;
	obj1_radius *= 0.7f;
	obj2_radius *= 0.7f;

	float distance = sqrt(pow(obj1_->Pos().x - obj2_->Pos().x, 2) + pow(obj1_->Pos().y - obj2_->Pos().y, 2));
	if ( distance < obj1_radius + obj2_radius )
		return true;
	return false;
}
*/

//check rectangle collision between two rectangles
int Collision::RectCollision(Rect r1_, Rect r2_)
{
	//r1_.Scale(0.95f);
	//r2_.Scale(0.95f);

	int ret = (int)COLLISION_TYPE::NO_COL;

	if (r1_.Right() < r2_.Left() 
		|| r2_.Right() < r1_.Left() 
		|| r1_.Bottom() > r2_.Top() 
		|| r1_.Top() < r2_.Bottom())
		
		return ret;

	//http://stackoverflow.com/questions/5062833/detecting-the-direction-of-a-collision

	float b_collision = r2_.Bottom() - r1_.Top();
	float t_collision = r1_.Bottom() - r2_.Top();
	float l_collision = r1_.Right() - r2_.Left();
	float r_collision = r2_.Right() - r1_.Left();

	if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision )
	{                           
		ret |= COLLISION_TYPE::TOP_COLL;
	}
	if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)                        
	{
		ret |= COLLISION_TYPE::BOT_COLL;
	}
	if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
	{
		ret |= COLLISION_TYPE::LEFT_COL;
	}
	if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision )
	{
		ret != COLLISION_TYPE::RIGHT_COL;
	}

	return ret;
}