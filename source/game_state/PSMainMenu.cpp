#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "PSLevelEditor.h"
#include "GLAH/GLAHGraphics.h"
#include <iostream>

using namespace std;

PSMainMenu::PSMainMenu(void)
{
	cout << endl << endl << "--------Main Menu---------" << endl;
	cout << "Play Game:            1" << endl;
	cout << "Level Designer:       2" << endl;
	//cout << "Quit:                 Escape" << endl;
}


PSMainMenu::~PSMainMenu(void)
{
}


ProgramState* PSMainMenu::Update(float delta_)
{
	if ( IsKeyDown(KEY_1) )
		return new PSGameLoop();
	if ( IsKeyDown(KEY_2) )
		return new PSLevelEditor();
	//if ( IsKeyDown(KEY_ESCAPE) )
	//{}
	return nullptr;
}

void PSMainMenu::Draw()
{}