#include "SpriteSheet.h"



bool SpriteSheet::init;
unsigned int SpriteSheet::sprite;
unsigned int SpriteSheet::fontSprite;
UVTranslator SpriteSheet::translator;


SpriteSheet::SpriteSheet(void)
{	
}

SpriteSheet::~SpriteSheet(void)
{	
}

void SpriteSheet::FillUV(float* uv_, SPRITE_TYPE st_)
{
	//get row and column based on st_
	int row = static_cast<int>(st_) / 50;
	int col = static_cast<int>(st_) % 50;

	//translate to a float*
	translator.GetUV(uv_, row, col);
}

void SpriteSheet::Init()
{
	if ( !init ) 
	{
		translator = UVTranslator(800, 1280, 16, 16);
		//sprite = CreateSprite("./resources/images/simples_pimples2.png", 32, 32, 0, Vector3(16.f,16.f,1.f));
		sprite = CreateSprite("./resources/images/simples_pimples2.png", 32, 32, 0, Vector3(0.f,0.f,1.f));
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