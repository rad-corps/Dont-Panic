#include "SpriteSheet.h"

bool SpriteSheet::init;
unsigned int SpriteSheet::sprite;

SpriteSheet::SpriteSheet(void)
{	
}

SpriteSheet::~SpriteSheet(void)
{	
}

void SpriteSheet::Init()
{
	if ( !init ) 
		sprite = CreateSprite("./images/simples_pimples.png", 32, 32, true);
}

unsigned int SpriteSheet::Sprite()
{
	if ( !init ) 
		return 0;
	return sprite;
}