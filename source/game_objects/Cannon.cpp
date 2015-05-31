#include "Cannon.h"
#include "../GLAH/GLAHGraphics.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"
#include "../globals/consts.h"

Cannon::Cannon(void)
{
	active = true;

	UVTranslator translator(800,1280,16,16);
	//translator.GetUV(UVs,51,38);
	translator.GetUV(UVs,51,33);
	pos.x = 300;
	pos.y = 100;

	rotation = 0.0f;
	reloadTime = 0.0f;
	cannonListener = nullptr;
}


Cannon::~Cannon(void)
{
}

void Cannon::RegisterCannonListener(CannonListener *cannonListener_)
{
	//commented out as I'm not using a canon any more. 
	cannonListener = cannonListener_;
}

void
Cannon::Update(float delta_)
{
	reloadTime += delta_;
	////handle user input
	//if  (IsKeyDown(KEY_LEFT)) 
	//{
	//	rotation += delta_ * 10;
	//}
	//if  (IsKeyDown(KEY_RIGHT)) 
	//{
	//	rotation -= delta_ * 10;
	//}

	//mouse controlled
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);
	Vector2 mousePos(mouseX, mouseY);
	rotation = ((pos - mousePos).GetAngle()) - 3.14;
	//cout << pos.AngleBetweenVectors(mousePos) << endl;

	if  (GetMouseButtonDown(0)) 
	{
		if ( reloadTime > 0.3 ) 
		{
			reloadTime = 0.0f;
			Vector2 velocity;
			velocity.SetAngle(rotation);
			velocity.SetMagnitude(2000);
			cannonListener->ShotFired(pos, velocity);	
		}		
	}
}

void Cannon::Draw()
{
	SetSpriteUVCoordinates(SpriteSheet::Sprite(), UVs);
	MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
	RotateSprite(SpriteSheet::Sprite(), 3.14f/2 + 3.14);
	RotateSpriteRelative(SpriteSheet::Sprite(), -rotation);
	DrawSprite(SpriteSheet::Sprite());
	RotateSprite(SpriteSheet::Sprite(), 0.f);
}