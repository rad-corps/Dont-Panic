//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// GameObject.cpp
/////////////////////////////////////////////////////////////////////////

#include "GameObject.h"
#include <iostream>
#include "../globals/consts.h"

using namespace std;

GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
}

void GameObject::SetPos(int col_, int row_)
{
	pos = Vector2(col_ * TILE_S, row_ * TILE_S);
}

int GameObject::Row()
{
	return pos.y / TILE_S;
}

int GameObject::Col()
{
	return pos.x / TILE_S;
}

bool GameObject::IsActive()
{
	return active;
}

Vector2 GameObject::Pos()
{
	return pos;
}

float GameObject::Width()
{
	return width;
}
float GameObject::Height()
{
	return height;
}

Rect GameObject::GetRect()
{
	return Rect(pos, width, height);
}

void GameObject::SetActive(bool active_)
{
	active = active_;
}