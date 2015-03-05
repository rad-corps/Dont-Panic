#include "Enemy.h"
#include "GLAH/GLAHGraphics.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"
#include "../math/Collision.h"

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

	//initialise colliders
	topCollider.width = 10;
	topCollider.height = 3;
	bottomCollider.width = 16;
	bottomCollider.height = 3;

	leftCollider.width = 3;
	leftCollider.height = 18;
	rightCollider.width = 3;
	rightCollider.height = 18;
	

	width = 32;
	height = 32;

	UpdateColliders();
	velocity = Vector2(0,0);

	active = enemy_.active;
	onPlatform = false;
}

Enemy::Enemy(ENEMY_TYPE type_, DIRECTION initialDirection_, int col_, int row_)
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

	width = 32;
	height = 32;


	currentAnimation = walk1;
	dir = initialDirection_;
	timer = 0.0f;
	active = true;
	SetPos(col_, row_);
	velocity = Vector2(0,0);
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

	width = 32;
	height = 32;


	velocity = Vector2(0,0);
}



Enemy::~Enemy(void)
{
}

void Enemy::UpdateColliders()
{
	//update colliders
	topCollider.centre = pos + Vector2(0, 14);
	bottomCollider.centre = pos + Vector2(0, -16);
	leftCollider.centre = pos + Vector2(-12, 0);
	rightCollider.centre = pos + Vector2(12, 0);
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

void Enemy::MoveTo(Vector2 pos_)
{
	pos = pos_;
	UpdateColliders();
}

void Enemy::UndoX()
{
	MoveTo(Vector2(prevX, pos.y));
}

void Enemy::UndoY()
{
	MoveTo(Vector2(pos.x, prevY));
}

void Enemy::HandleCollision(vector<Platform>& platform_, std::vector<Shell>& shells_)
{
	onPlatform = false;
	//check collision	
	for ( auto &env : platform_ )
	{
		//only check collision with platforms
		if ( env.TileType() > ENVIRO_TILE::PLATFORMS_START && env.TileType() < ENVIRO_TILE::PLATFORMS_END )
		{
			if ( env.Active() ) 
			{
				if ( Collision::RectCollision(topCollider, env))
				{
					if  (velocity.y > 0)
						velocity.y = 0;
						//velocity.y = -velocity.y;
				}
				if ( Collision::RectCollision(bottomCollider, env))
				{
					onPlatform = true;
					velocity.y = 0;
					//push him back up to the top of the platform
					MoveTo(Vector2(pos.x, env.Top() + 16));
				}
				if ( Collision::RectCollision(leftCollider, env))
				{
					UndoX();
					dir = DIRECTION::DIR_RIGHT;
				}
				if ( Collision::RectCollision(rightCollider, env))
				{
					UndoX();
					dir = DIRECTION::DIR_LEFT;
				}
			}
		}
	}
	if ( !onPlatform )
	{
		status = ENEMY_STATUS::WALKING;
	}

	//check if shot
	for ( auto &shell : shells_ )
		if ( shell.IsActive() )
			if ( Collision::RectCollision(shell.GetRect(), GetRect()) )		
			{
				active = false;
				shell.SetActive(false);
			}

		
	
}

void Enemy::ApplyGravity()
{
	//gravity only if jumping
	Vector2 gravity(0, -1); 
	if ( !onPlatform )
	{
		velocity += gravity;	
	}
}

void Enemy::ApplyVelocity(Vector2 velocity_)
{
	pos += velocity;
	UpdateColliders();
}

void Enemy::Update(float delta_, vector<Platform>& platform_, std::vector<Shell>& shells_)
{
	if ( !active )
		return;

	timer += delta_;

	prevX = pos.x;
	prevY = pos.y;

	if (timer > 0.2f )
	{
		timer = 0.0f;
		GetNextAnimation();
	}

	
	HandleCollision(platform_, shells_);
	ApplyGravity();
	ApplyVelocity(velocity);

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
	if ( !active )
		return;

	SetSpriteUVCoordinates(SpriteSheet::Sprite(),currentAnimation);
	//SetSpriteUVCoordinates(SpriteSheet::Sprite(),walk1);
	
	MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
	if ( dir == DIRECTION::DIR_LEFT)
		DrawSprite(SpriteSheet::Sprite(), true);
	else
		DrawSprite(SpriteSheet::Sprite());
}