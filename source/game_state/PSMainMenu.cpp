#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "PSLevelEditor.h"
#include "PSLevelSelect.h"
#include "GLAH/GLAHGraphics.h"
#include <iostream>

using namespace std;

PSMainMenu::PSMainMenu(void)
{
	cout << endl << endl << "--------Main Menu---------" << endl;
	cout << "Play Game:            1" << endl;
	cout << "Level Designer:       2" << endl;
	//cout << "Quit:                 Escape" << endl;

	text1.SetPos(Vector2(1024/2, 200));
	text1.SetText("Hello World - High Score - 1234567890");
	text2.SetAlignment(TEXT_ALIGNMENT::ALIGN_CENTRE);
	text2.SetPos(Vector2(1024/2, 150));
	text2.SetText("Hello World - High Score - 2345678901");
	text3.SetAlignment(TEXT_ALIGNMENT::ALIGN_RIGHT);
	text3.SetPos(Vector2(1024/2, 100));
	text3.SetText("Hello World - High Score - 3456789012");
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
	text1.Draw();
	text2.Draw();
	text3.Draw();
}