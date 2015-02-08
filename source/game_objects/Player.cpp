#include "Player.h"
//#include "aie.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"
#include "../math/Collision.h"
#include "../globals/consts.h"


Player::Player(void)
{
//	gfx = GLAHGraphics::Instance();
//	inpt = GLAHInput::Instance();

	pos = Vector2(200,200);

	//initialise colliders
	topCollider.width = 10;
	topCollider.height = 1;
	bottomCollider.width = 16;
	bottomCollider.height = 1;

	leftCollider.width = 1;
	leftCollider.height = 18;
	rightCollider.width = 1;
	rightCollider.height = 18;
	
	UpdateColliders();

	velocity = Vector2(0,0);
	status = PLAYER_STATUS::STATIONARY;

	//initialise animations
	UVTranslator translator(800, 1280, 16, 16);
	translator.GetUV(animStationary, 1, 26);
	translator.GetUV(animMove1, 1, 27);
	translator.GetUV(animMove2, 1, 28);
	translator.GetUV(animMove3, 1, 27);
	currentAnimation = animStationary;

	animationTimer = 0.0f;
	faceLeft = false;
	onPlatform = false;
}


Player::~Player(void)
{
}

//must be called whenever players position changes
void Player::UpdateColliders()
{
	//update colliders
	topCollider.centre = pos + Vector2(0, 14);
	bottomCollider.centre = pos + Vector2(0, -16);
	leftCollider.centre = pos + Vector2(-12, 0);
	rightCollider.centre = pos + Vector2(12, 0);
}

void Player::HandleCollision(vector<Environment>& environment_)
{
	onPlatform = false;
	//check collision	
	for ( auto &env : environment_ )
	{
		if ( Collision::RectCollision(topCollider, env))
		{
			if  (velocity.y > 0)
				velocity.y = 0;
				//velocity.y = -velocity.y;
		}
		if ( Collision::RectCollision(bottomCollider, env))
		{
			onPlatform = true;
			velocity.y = 0;
			//push him back up to the top of the platform
			MoveTo(Vector2(pos.x, env.Top() + 16));
		}
		if ( Collision::RectCollision(leftCollider, env))
		{
			UndoX();
		}
		if ( Collision::RectCollision(rightCollider, env))
		{
			UndoX();
		}
	}
	if ( !onPlatform )
	{
		status = JUMPING;
	}
}

void Player::UndoX()
{
	MoveTo(Vector2(prevX, pos.y));
}

void Player::UndoY()
{
	MoveTo(Vector2(pos.x, prevY));
}

void Player::ApplyGravity()
{
	//gravity only if jumping
	Vector2 gravity(0, -1); 
	if ( status == JUMPING )
	{
		velocity += gravity;	
	}
}

void Player::HandleInput(float delta_)
{
	if ( IsKeyDown(KEY_A ) )
	{
		faceLeft = true;
		pos.x -= 300 * delta_;
		if ( onPlatform ) 
			status = RUNNING;
	}
	else if ( IsKeyDown(KEY_D ) )
	{
		faceLeft = false;
		pos.x += 300 * delta_;
		
		if ( onPlatform ) 
			status = RUNNING;
	}
	else if ( onPlatform ) 
	{
		status = STATIONARY;
	}

	//only jump if not already jumping
	if ( IsKeyDown(KEY_W ) && status != PLAYER_STATUS::JUMPING)
	{
		status = JUMPING;	
		
		//will only happen for one frame
		velocity.y += 15;
	}
}

void Player::UpdateAnimation(float delta_)
{
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

void Player::Update(float delta_, vector<Environment>& environment_)
{
	prevX = pos.x;
	prevY = pos.y;
	
	HandleInput(delta_);
	
	ApplyGravity();
	
	ApplyVelocity(velocity);	
	HandleCollision(environment_);
	UpdateAnimation(delta_);

}

void Player::MoveTo(Vector2 pos_)
{
	pos = pos_;
	UpdateColliders();
}



void Player::ApplyVelocity(Vector2 velocity_)
{
	pos += velocity;
	UpdateColliders();
}

void Player::Draw()
{
	//set the UV
	SetSpriteUVCoordinates	( SpriteSheet::Sprite(), currentAnimation);
	MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
	DrawSprite(SpriteSheet::Sprite(), faceLeft);
	//DrawString(to_string(FPS).c_str(), 50, 500);
}