//PlayerProjectile

#include "../spritesheet/UVTranslator.h"
#include "../spritesheet/SpriteSheet.h"
#include "PlayerProjectile.h"
#include <iostream>
#include "../globals/consts.h"
#include "../math/Collision.h"

float PlayerProjectile::uv[4];
bool PlayerProjectile::init = false;

using namespace std;

PlayerProjectile::PlayerProjectile()
{
	active = false;

	if ( !init ) 
	{
		UVTranslator translator(800,1280,16,16);
		translator.GetUV(uv, 0, 0);
		init = true;
	}

	width = TILE_S;
	height = TILE_S;
}

PlayerProjectile::~PlayerProjectile()
{
	cout << "Projectile Created" << endl; 
}

void PlayerProjectile::Shoot(Vector2 pos_, Vector2 direction_)
{
//	timer = 0.0f;
	active = true;
	pos = pos_;
	
	velocity = direction_ * 2000;
}

void
PlayerProjectile::Draw()
{
	if ( active )
	{
		SetSpriteUVCoordinates(SpriteSheet::Sprite(), uv);
		MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
		DrawSprite(SpriteSheet::Sprite());
	}
}

void
PlayerProjectile::Update(float delta_)
{
	if ( active ) 
	{
		pos += velocity * delta_;
	
		//if it no longer collides with the screen, deactivate
		if ( !Collision::RectCollision(GetScreenRect(), GetRect() ) )
		{
			cout << "PlayerProjectile left screen" << endl;
			active = false;
		}
	}
}