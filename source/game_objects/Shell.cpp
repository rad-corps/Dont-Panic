#include "Shell.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"
#include "../globals/consts.h"

float Shell::uv[4];
bool Shell::init = false;

Shell::Shell(Vector2 pos_, Vector2 velocity_)
{	
	if ( !init ) 
	{
		UVTranslator translator(800,1280,16,16);
		translator.GetUV(uv, 0, 0);
		init = true;
	}

	width = TILE_S;
	height = TILE_S;

	Shoot(pos_,velocity_);
}


Shell::~Shell(void)
{
}

void Shell::Shoot(Vector2 pos_, Vector2 velocity_)
{
	timer = 0.0f;
	active = true;
	pos = pos_;
	
	velocity = velocity_;
	//cout << "Shoot(Vector2 " << pos_ << ", Vector2 " << velocity_ << ")" << endl;
}

void Shell::Update(float delta_)
{
	if ( timer > 3.0f )
	{
		active = false;
	}

	if ( active ) 
	{
		//apply gravity
		//Vector2 gravity(0, -50); 
		//velocity += gravity;	

		pos += velocity * delta_;
		timer += delta_;
	}
}

void Shell::Draw()
{
	if ( active ) 
	{
		SetSpriteUVCoordinates(SpriteSheet::Sprite(), uv);
		MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
		DrawSprite(SpriteSheet::Sprite());
	}
}