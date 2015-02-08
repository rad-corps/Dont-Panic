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

	text.SetPos(Vector2(200, 200));
	text.SetText("Hello World");
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
	text.Draw();
}