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

	alive = true;

	////initialise colliders
	topCollider.width = 50;
	topCollider.height = 3;
	bottomCollider.width = 40;
	bottomCollider.height = 3;

	leftCollider.width = 3;
	leftCollider.height = 58;
	rightCollider.width = 3;
	rightCollider.height = 58;
	hitCollider.width = 58;
	hitCollider.height = 58;

	
	UpdateColliders();

	velocity = Vector2(0,0);
	status = PLAYER_STATUS::STATIONARY;

	//initialise animations
	UVTranslator translator(256, 32, 32, 32);
	translator.GetUV(animStationary, 0, 0);
	translator.GetUV(animMove1, 0, 1);
	translator.GetUV(animMove2, 0, 2);
	translator.GetUV(animMove3, 0, 3);
	translator.GetUV(animDead, 0, 4);
	
	currentAnimation = animStationary;

	animationTimer = 0.0f;
	faceLeft = false;
	onPlatform = false;

	playerSpeak.SetAlignment(TEXT_ALIGNMENT::ALIGN_RIGHT);

	//get the players attributes from DB (assume only 1 row)
	char * error = "";
	dm.Select("./resources/db/dontpanic.db", "player_attributes", "*", "", "", error);
	gravity = dm.GetValueFloat(0, "gravity");
	maxSpeed = dm.GetValueFloat(0, "top_speed");
	jumpForce = dm.GetValueFloat(0, "jump_force");
	accelleration = dm.GetValueFloat(0, "accelleration");	
}

Player::~Player(void)
{
}

void Player::InitListener(PlayerProjectileListener* playerProjectileListener_)
{
	playerProjectileListener = playerProjectileListener_;
}


//must be called whenever players position changes
void Player::UpdateColliders()
{
	//update colliders
	topCollider.centre = pos + Vector2(0, 30);
	bottomCollider.centre = pos + Vector2(0, -32);
	leftCollider.centre = pos + Vector2(-27.5, 0);
	rightCollider.centre = pos + Vector2(27.5, 0);

	hitCollider.centre = pos;
}

void Player::HandleCollision(vector<Platform>& platform_, std::vector<Enemy>& enemies_, Goal& goal_)
{
	onPlatform = false;
	//check collision	
	for ( auto &env : platform_ )
	{
		//if ( env.TileType() > ENVIRO_TILE::PLATFORMS_START && env.TileType() < ENVIRO_TILE::PLATFORMS_END )
		//{
		if ( env.Active() )
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
				MoveTo(Vector2(pos.x, env.Top() + (PLAYER_S * 0.5)));
				
				////if the env is a falling type, then make it fall!
				//if ( env.TileType() == ENVIRO_TILE::RED_BRICK_BASE || env.TileType() == ENVIRO_TILE::RED_BRICK_SURFACE ) 
				//{
				//	env.Fall();
				//}
			}
			if ( Collision::RectCollision(leftCollider, env))
			{
				UndoX();
				//PUSH HIM ONE PIXEL RIGHT
				pos.x += 1;
			}
			if ( Collision::RectCollision(rightCollider, env))
			{
				UndoX();
				pos.x -= 1;
			}
		}
		//}
	}
	if ( !onPlatform )
	{
		status = JUMPING;
	}

	//check player enemy collision
	for ( auto &enemy : enemies_ )
		if ( Collision::RectCollision(hitCollider, enemy.GetRect()))
			if ( enemy.IsActive() )
			{
				alive = false;
				playerSpeak.SetText("R TO RESTART");
			}

	//check player goal collision
	if ( Collision::RectCollision(hitCollider, goal_.GetRect()))
	{
		playerSpeak.SetText("WOO! ");
		
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
	Vector2 gravityVec(0, -(gravity)); 
	if ( status == JUMPING )
	{
		velocity += gravityVec;	
	}
}

void Player::HandleInput(float delta_)
{
	if ( IsKeyDown(SDLK_a ) || IsGamePadButtonDown( SDL_CONTROLLER_BUTTON_DPAD_LEFT ) )
	{
		faceLeft = true;
		pos.x -= maxSpeed * delta_;
		if ( onPlatform ) 
			status = RUNNING;
	}
	else if ( IsKeyDown(SDLK_d ) || IsGamePadButtonDown( SDL_CONTROLLER_BUTTON_DPAD_RIGHT ) )
	{
		faceLeft = false;
		pos.x += maxSpeed * delta_;
		
		if ( onPlatform ) 
			status = RUNNING;
	}
	else if ( onPlatform ) 
	{
		status = STATIONARY;
	}

	//only jump if not already jumping
	if ( (IsKeyDown(SDLK_w ) || IsGamePadButtonDown( SDL_CONTROLLER_BUTTON_A )) && status != PLAYER_STATUS::JUMPING && !jumpHeld)
	{
		jumpHeld = true;
		status = JUMPING;	
		
		//will only happen for one frame
		velocity.y += jumpForce;
	}

	if ( !IsKeyDown(SDLK_w) )
	{
		jumpHeld = false;
	}

	if ( (IsKeyDown(SDLK_SPACE) || IsGamePadButtonDown( SDL_CONTROLLER_BUTTON_X ))&& shootHeld == false )
	{
		shootHeld = true;
		cout << "SPACE PRESSED" << endl;
		
		if ( faceLeft )
			playerProjectileListener->PlayerProjectileFired(pos, Vector2(-1, 0));
		else
			playerProjectileListener->PlayerProjectileFired(pos, Vector2(1, 0));

	}
	else if (!IsKeyDown(SDLK_SPACE) && !IsGamePadButtonDown( SDL_CONTROLLER_BUTTON_X ))
	{
		shootHeld = false;
	}
}

void Player::UpdateAnimation(float delta_)
{
	if ( !alive ) 
	{
		currentAnimation = animDead;
		return;
	}
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

void Player::Update(float delta_, vector<Platform>& platform_, std::vector<Enemy>& enemies_, Goal& goal_ )
{

	prevX = pos.x;
	prevY = pos.y;
	
	if (alive )	
		HandleInput(delta_);	

	
	ApplyGravity();	
	ApplyVelocity(velocity);	
	playerSpeak.SetPos(pos);
	HandleCollision(platform_, enemies_, goal_);
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
	SetSpriteUVCoordinates	( SpriteSheet::PlayerSprite(), currentAnimation);
	MoveSprite(SpriteSheet::PlayerSprite(), pos.x, pos.y);
	DrawSprite(SpriteSheet::PlayerSprite(), faceLeft);
	//DrawString(to_string(FPS).c_str(), 50, 500);

	playerSpeak.Draw();
}