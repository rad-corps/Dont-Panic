#include "SpriteSheet.h"


bool SpriteSheet::init;
unsigned int SpriteSheet::sprite;
//GLAHGraphics* SpriteSheet::gfx;

SpriteSheet::SpriteSheet(void)
{	
}

SpriteSheet::~SpriteSheet(void)
{	
}

void SpriteSheet::Init()
{
	if ( !init ) 
	{
		//gfx = GLAHGraphics::Instance();
		sprite = CreateSprite("./resources/images/simples_pimples2.png", 32, 32, 0, Vector3(16.f,16.f,1.f));
		init = true;
	}
}

unsigned int SpriteSheet::Sprite()
{
	if ( !init ) 
		return 0;
	return sprite;
}