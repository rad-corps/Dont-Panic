#include "Player.h"
#include "aie.h"
#include "spritesheet\SpriteSheet.h"
#include "spritesheet\UVTranslator.h"

Player::Player(void)
{
	pos = Vector2(50,50);
	velocity = Vector2(0,0);
	status = PLAYER_STATUS::STATIONARY;

	//initialise animations
	UVTranslator translator(800, 1280, 16, 16);
	translator.GetUV(animStationary, 78, 26);
	translator.GetUV(animMove1, 78, 27);
	translator.GetUV(animMove2, 78, 28);
	translator.GetUV(animMove3, 78, 27);
	currentAnimation = animStationary;

	animationTimer = 0.0f;
}


Player::~Player(void)
{
}

void Player::Update(float delta_)
{
	//check bounds
	if ( pos.y <= 20 )
	{
		status = PLAYER_STATUS::STATIONARY;
		pos.y = 20;
	}


	if ( IsKeyDown(KEY_LEFT ) )
	{
		pos.x -= 300 * delta_;

		if ( status != JUMPING ) 
			status = RUNNING;
	}
	else if ( IsKeyDown(KEY_RIGHT ) )
	{
		pos.x += 300 * delta_;
		
		if ( status != JUMPING ) 
			status = RUNNING;
	}
	else if ( status != JUMPING ) 
	{
		status = STATIONARY;
	}
	//only jump if not already jumping
	if ( IsKeyDown(KEY_UP ) && status != PLAYER_STATUS::JUMPING)
	{
		status = JUMPING;	
		
		//will only happen for one frame
		velocity.y += 10;
	}

	pos += velocity;
	Vector2 gravity(0, -1); 
	velocity += gravity;
	if ( velocity.y < 0.0f && status != PLAYER_STATUS::JUMPING) velocity.y = 0.0f;
	


	//pick the animation
	animationTimer += delta_;
	if ( animationTimer > 0.1f )
	{
		animationTimer = 0.0f;

		if  ( status == STATIONARY ) 
			currentAnimation = animStationary;
		else if ( status == RUNNING ) 
		{
			if ( currentAnimation == animStationary ) 
				currentAnimation = animMove1;
			else if ( currentAnimation == animMove1 ) 
				currentAnimation = animMove2;
			else if ( currentAnimation == animMove2 ) 
				currentAnimation = animMove3;
			else if ( currentAnimation == animMove3 ) 
				currentAnimation = animStationary;
		}
		else if ( status == JUMPING )
		{
			currentAnimation = animMove1;
		}

		FPS = 1 / delta_;
		

		//switch ( status ) 

		//{
		//case STATIONARY :
		//	cout << "STATIONARY" << endl;
		//	break;
		//case JUMPING :
		//	cout << "JUMPING" << endl;
		//	break;
		//case RUNNING :
		//	cout << "RUNNING" << endl;
		//	break;
		//}
	}
}

void Player::Draw()
{
	//set the UV
	SetSpriteUVCoordinates	( SpriteSheet::Sprite(), currentAnimation);
	MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
	DrawSprite(SpriteSheet::Sprite());

	DrawString(to_string(FPS).c_str(), 50, 500);
}