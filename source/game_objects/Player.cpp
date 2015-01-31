#include "Player.h"
#include "aie.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"
#include "../math/Collision.h"

Player::Player(void)
{
	pos = Vector2(50,100);
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

void Player::Update(float delta_, const vector<Environment>& environment_)
{
	prevPos = pos;
	
	//gravity only if jumping
	Vector2 gravity(0, -1); 
	if ( status == JUMPING )
	{
		velocity += gravity;	
	}

	//check collision
	Rect playerRect(Vector2(pos.x, pos.y), 16,16);
	int collidedWith = 0;
	for ( auto &env : environment_ )
	{
		collidedWith |= Collision::RectCollision(playerRect, env);
		if ( collidedWith > 0)
		{
			if ( collidedWith & COLLISION_TYPE::BOT_COLL ) 
			{
				//cout << "BOT_COLL" << endl;
				status = STATIONARY; //will be overwritten to running if user input
				//pos = prevPos; //undo effects of gravity
				velocity.y = 0;
			}
			if ( collidedWith & COLLISION_TYPE::LEFT_COL ) {}
				//cout << "LEFT_COLL" << endl;
			if ( collidedWith & COLLISION_TYPE::RIGHT_COL) {}
				//cout << "RIGHT_COLL" << endl;
			if ( collidedWith & COLLISION_TYPE::TOP_COLL) {}
				//cout << "TOP_COLL" << endl;
		}		
	}
	if ( collidedWith == 0 )
	{
		status = JUMPING;
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
		velocity.y += 15;
	}

	pos += velocity;


	//if ( velocity.y < 0.0f && status != PLAYER_STATUS::JUMPING) velocity.y = 0.0f;
	
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