#include "PSLevelSelect.h"
#include <iostream>
#include "../sqlite/DatabaseManager.h"
#include "PSGameLoop.h"
#include "PSMainMenu.h"
#include "../globals/consts.h"
using namespace std;

void MyLevelSelectKeyEvent(int key_, void* caller_)
{
	PSLevelSelect* caller = (PSLevelSelect*)caller_;
	caller->KeyDown(key_);
}

void PSLevelSelect::KeyDown(SDL_Keycode key_)
{
	switch (key_)
	{
	case SDLK_UP : 
		if ( selection > 0 )
			--selection;
		break;
	case SDLK_DOWN : 
		if ( selection < levelText.size() - 1 )
			++selection;
		break;
	case SDLK_RETURN : 
		nextProgramState = new PSGameLoop(levelMap[selection]); 
		break;
	case SDLK_ESCAPE : 
		nextProgramState = new PSMainMenu(); 
		break;
	}
}

void PSLevelSelect::GamePadButtonDown(SDL_GameControllerButton button_)
{
	if ( button_ == SDL_CONTROLLER_BUTTON_DPAD_DOWN ) 
		KeyDown ( SDLK_DOWN );
	if ( button_ == SDL_CONTROLLER_BUTTON_DPAD_UP ) 
		KeyDown ( SDLK_UP );
	if ( button_ == SDL_CONTROLLER_BUTTON_A || button_ == SDL_CONTROLLER_BUTTON_START ) 
		KeyDown ( SDLK_RETURN );
	if ( button_ == SDL_CONTROLLER_BUTTON_BACK || button_ == SDL_CONTROLLER_BUTTON_B ) 
		KeyDown ( SDLK_ESCAPE );
}

PSLevelSelect::PSLevelSelect(void) : nextProgramState(nullptr)
{
	AddInputListener(this);

	cout << endl << endl << "-------Select a Level---------" << endl;
	DatabaseManager dm;
	char * error = "";
	dm.Select("./resources/db/dontpanic.db", "tbl_level", "id, name", "", "", error);

	textPos = Vector2(SCREEN_W * 0.5, 50);
	GLText txtTemp;
	txtTemp.SetAlignment(TEXT_ALIGNMENT::ALIGN_CENTRE);
	txtTemp.SetHUD(true);
	
	for ( int i = 0; i < dm.Rows(); ++i )
	{
		levelMap[i] = dm.GetValueInt(i, "id");
		txtTemp.SetText(dm.GetValueString(i, "name"));
		txtTemp.SetPos(textPos);
		levelText.push_back(txtTemp);
		textPos += Vector2(0, 30);
	}

	selection = 0;
}


PSLevelSelect::~PSLevelSelect(void)
{
}

ProgramState* PSLevelSelect::Update(float delta_)
{
	return nextProgramState;
}

void PSLevelSelect::Draw()
{	
	for ( int i = 0; i < levelText.size(); ++i )
	{		
		GLText txt = levelText[i];
		if ( i == selection )
		{
			txt.SetText("--" + txt.GetText() + "--");
		}
		txt.Draw();		
	}
}