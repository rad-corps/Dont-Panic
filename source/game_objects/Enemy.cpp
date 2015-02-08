#include "Enemy.h"
#include "GLAH/GLAHGraphics.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"

using namespace std;

Enemy::Enemy(const Enemy& enemy_)
{
	for ( int i = 0; i < 4; ++i )
	{
		walk1[i] = enemy_.walk1[i];
		walk2[i] = enemy_.walk2[i];
		walk3[i] = enemy_.walk3[i];
	}

	currentAnimation = walk1;
	dir = enemy_.dir;
	xFlip = enemy_.xFlip;
	timer = 0.0f;
	pos = enemy_.pos;
	active = true;
}

Enemy::Enemy(ENEMY_TYPE type_, DIRECTION initialDirection_, Vector2 pos_)
{
	UVTranslator trans(800,1280,16,16);

	switch (type_)
	{
	case ZOMBIE: 
		trans.GetUV(walk1, 5, 26);
		//trans.GetUV(walk1, 1, 26);
		trans.GetUV(walk2, 5, 27);
		trans.GetUV(walk3, 5, 28);
		break;
	case SKELETON:
		trans.GetUV(walk1, 6, 26);
		//trans.GetUV(walk1, 1, 26);
		trans.GetUV(walk2, 6, 27);
		trans.GetUV(walk3, 6, 28);
		break;
	}

	currentAnimation = walk1;
	dir = initialDirection_;
	timer = 0.0f;
	active = true;
	pos = pos_;
}


Enemy::~Enemy(void)
{
}

void Enemy::GetNextAnimation()
{
	if ( currentAnimation == walk1 )
		currentAnimation = walk2;
	else if ( currentAnimation == walk2 ) 
		currentAnimation = walk3;
	else if ( currentAnimation == walk3 ) 
		currentAnimation = walk1;
}

void Enemy::Update(float delta_, vector<Environment>& environment_)
{
	timer += delta_;

	if (timer > 0.2f )
	{
		timer = 0.0f;
		GetNextAnimation();
	}

	if ( dir == DIRECTION::DIR_LEFT)
	{
		pos -= Vector2(100, 0) * delta_;
	}
	else
	{
		pos += Vector2(100, 0) * delta_;
	}

}

void Enemy::Draw()
{
	SetSpriteUVCoordinates(SpriteSheet::Sprite(),currentAnimation);
	//SetSpriteUVCoordinates(SpriteSheet::Sprite(),walk1);
	
	MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
	if ( dir == DIRECTION::DIR_LEFT)
		DrawSprite(SpriteSheet::Sprite(), true);
	else
		DrawSprite(SpriteSheet::Sprite());
}