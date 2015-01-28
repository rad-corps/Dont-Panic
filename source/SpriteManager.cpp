#include "SpriteManager.h"

using namespace std;

//initialise static variables
unsigned int SpriteManager::spriteSheet;
std::map<UV_TYPE, float*> SpriteManager::uvMap;

//How to declare and initialize a static const array as a class member?
//http://stackoverflow.com/questions/11367141/how-to-declare-and-initialize-a-static-const-array-as-a-class-member



//float SpriteManager::PLAYER_STATIONARY_UV[4] = { 0.52 , 0.975, 0.54, 0.9875 };

void SpriteManager::Init()
{
	spriteSheet = CreateSprite("./images/simples_pimples.png", 64, 64, true);

	//vector<int> test = { 1, 2, 3 };
	//vector<float> test = { 0.52f , 0.975f, 0.54f, 0.9875f };

	float uv1[4] = {  0.52f, 0.975f, 0.54f, 0.9875f };
	uvMap[UV_TYPE::E_1] = uv1;
	//uvMap.
}

SpriteManager::SpriteManager()
{
	
}