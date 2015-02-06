#include "PSMainMenu.h"
#include "PSGameLoop.h"
#include "GLAH/GLAHGraphics.h"
#include <iostream>

using namespace std;

PSMainMenu::PSMainMenu(void)
{
	cout << endl << endl << "--------Main Menu---------" << endl;
	cout << "Play Game:            1" << endl;
	cout << "Level Designer:       2" << endl;
}


PSMainMenu::~PSMainMenu(void)
{
}


ProgramState* PSMainMenu::Update(float delta_)
{
	if ( IsKeyDown(KEY_1) )
		return new PSGameLoop();
	return nullptr;
}

void PSMainMenu::Draw()
{}