#include "SpriteSheet.h"


bool SpriteSheet::init;
unsigned int SpriteSheet::sprite;
unsigned int SpriteSheet::fontSprite;

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
		sprite = CreateSprite("./resources/images/simples_pimples2.png", 32, 32, 0, Vector3(16.f,16.f,1.f));
		fontSprite = CreateSprite("./resources/images/courier.png", 16, 16, 0, Vector3(8.f,8.f,1.f));
		init = true;
	}
}

unsigned int SpriteSheet::Sprite()
{
	if ( !init ) 
		return 0;
	return sprite;
}

unsigned int SpriteSheet::FontSprite()
{
	if ( !init ) 
		return 0;
	return fontSprite;
}