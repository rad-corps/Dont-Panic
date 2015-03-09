#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "PSLevelEditor.h"
#include "PSLevelSelect.h"
#include "PSLevelModifySelect.h"
#include "GLAH/GLAHGraphics.h"
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
	Vector2 textPos(1024/2, 700);
	GLText txt;
	txt.SetAlignment(TEXT_ALIGNMENT::ALIGN_CENTRE);
	for ( string str : menuStrings )
	{		
		txt.SetPos(textPos);
		txt.SetText(str);
		textPos -= Vector2(0, 30);
		menuText.push_back(txt);
	}

	AddInputListener(this);

	//testSprite = CreateSprite("./resources/images/simples_pimples2.png", 32, 32, 0, Vector3(0.f,0.f,1.f));
}


PSMainMenu::~PSMainMenu(void)
{
	//RemoveInputListener(this);
}

void PSMainMenu::KeyDown(SDL_Keycode key_)
{
	if ( key_ == SDLK_1 ) 
		newState = new PSLevelSelect();
	if ( key_ == SDLK_2 ) 
		newState = new PSLevelEditor();
	if ( key_ == SDLK_3 ) 
		newState = new PSLevelModifySelect();

	//if ( newState != nullptr ) 
	//	RemoveInputListener(this);
}


ProgramState* PSMainMenu::Update(float delta_)
{
	return newState;
}

void PSMainMenu::Draw()
{
	for ( auto &txt : menuText )
	{
		txt.Draw();
	}
	//DrawSprite(testSprite);
}