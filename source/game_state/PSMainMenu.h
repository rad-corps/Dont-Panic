#pragma once
#include "ProgramState.h"
#include "../GLAH/InputListener.h"
#include "../game_objects/GLText.h"

class PSMainMenu : public ProgramState, public InputListener
{
public:
	PSMainMenu(void);
	~PSMainMenu(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

	virtual void KeyDown(SDL_Keycode key_);

private:
	
	std::vector<string> menuStrings;
	std::vector<GLText> menuText;
	

	ProgramState* newState;
};

