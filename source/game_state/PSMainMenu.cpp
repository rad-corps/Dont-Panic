#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "PSLevelEditor.h"
#include "PSLevelSelect.h"
#include "PSLevelModifySelect.h"
#include "../GLAH/GLAHGraphics.h"
#include "../globals/consts.h"
#include <iostream>

using namespace std;

PSMainMenu::PSMainMenu(void) : newState(nullptr)
{
	cout << "PSMainMenu" << endl;
	menuStrings.push_back("----------Dont Panic Alpha----------");
	menuStrings.push_back("Play Game                          1");
	menuStrings.push_back("Create New Level                   2");
	menuStrings.push_back("Modify Existing Level              3");

	//create the GLText objects
	Vector2 textPos(SCREEN_W*0.5, 100);
	GLText txt;
	txt.SetAlignment(TEXT_ALIGNMENT::ALIGN_CENTRE);
	txt.SetHUD(true);
	for ( string str : menuStrings )
	{		
		txt.SetPos(textPos);
		txt.SetText(str);		
		textPos += Vector2(0, 30);
		menuText.push_back(txt);
	}

	AddInputListener(this);

	//testSprite = CreateSprite("./resources/images/simples_pimples2.png", 32, 32, 0, Vector3(0.f,0.f,1.f));
	selection = 1;
}


PSMainMenu::~PSMainMenu(void)
{
	//RemoveInputListener(this);
}

void PSMainMenu::KeyDown(SDL_Keycode key_)
{
	if ( key_ == SDLK_UP ) 
	{
		selection -= 1;
		if ( selection < 1 )  //check overflow
			selection = 3;
	}
	if ( key_ == SDLK_DOWN )
	{
		selection += 1;
		if ( selection > 3 ) //check overflow
			selection = 1;
	}
	if (key_ == SDLK_RETURN)
	{
		if ( selection == 1 )
		{
			newState = new PSLevelSelect();
		}
		if ( selection == 2 )
		{
			newState = new PSLevelEditor();
		}
		if ( selection == 3 )
		{
			newState = new PSLevelModifySelect();
		}
	}
}

void PSMainMenu::GamePadButtonDown(SDL_GameControllerButton button_) 
{
	if ( button_ == SDL_CONTROLLER_BUTTON_DPAD_UP ) 
		KeyDown(SDLK_UP);
	if ( button_ == SDL_CONTROLLER_BUTTON_DPAD_DOWN ) 
		KeyDown(SDLK_DOWN);
	if ( button_ == SDL_CONTROLLER_BUTTON_A || button_ == SDL_CONTROLLER_BUTTON_START ) 
		KeyDown(SDLK_RETURN);
}


ProgramState* PSMainMenu::Update(float delta_)
{
	return newState;
}

void PSMainMenu::Draw()
{
	int menuItem = 0;
	for ( auto txt : menuText )
	{
		if (menuItem == selection)
		{
			txt.SetText("--" + txt.GetText() + "--");
		}
		txt.Draw();
		menuItem++;
	}
	//DrawSprite(testSprite);
}