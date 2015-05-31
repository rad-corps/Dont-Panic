#pragma once
#include "ProgramState.h"
#include "../game_objects/GLText.h"
#include <vector>
#include <map>
#include "../GLAH/InputListener.h"

class PSLevelSelect : public ProgramState, public InputListener
{
public:
	PSLevelSelect(void);
	~PSLevelSelect(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

	virtual void KeyDown(SDL_Keycode key_);
	virtual void GamePadButtonDown(SDL_GameControllerButton button_);

private:

	std::vector<GLText> levelText;
	Vector2 textPos;
	int selection; //the vector subscript index (not the database level id)
	std::map<int, int> levelMap; //vector subcript, level ID
	ProgramState* nextProgramState;
};

