#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "PSLevelEditor.h"
#include "PSLevelSelect.h"
#include "GLAH/GLAHGraphics.h"
#include <iostream>

using namespace std;

PSMainMenu::PSMainMenu(void)
{
	menuStrings.push_back("----------Dont Panic Alpha----------");
	menuStrings.push_back("Play Game                          1");
	menuStrings.push_back("Level Designer                     2");

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
}


PSMainMenu::~PSMainMenu(void)
{
}


ProgramState* PSMainMenu::Update(float delta_)
{
	if ( IsKeyDown(KEY_1) )
		return new PSLevelSelect();
	if ( IsKeyDown(KEY_2) )
		return new PSLevelEditor();
	//if ( IsKeyDown(KEY_ESCAPE) )
	//{}
	return nullptr;
}

void PSMainMenu::Draw()
{
	for ( auto &txt : menuText )
	{
		txt.Draw();
	}
}