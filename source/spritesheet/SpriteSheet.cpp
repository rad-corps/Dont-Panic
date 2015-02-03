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
		sprite = CreateSprite("./resources/images/simples_pimples.png", 32, 32, 0, 0);
		init = true;
	}
}

unsigned int SpriteSheet::Sprite()
{
	if ( !init ) 
		return 0;
	return sprite;
}