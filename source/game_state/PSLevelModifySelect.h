#pragma once
#include "ProgramState.h"
#include "../game_objects/GLText.h"
#include <vector>
#include <map>
//#include "GLAH/InputHelper.h"
#include "../GLAH/InputListener.h"

class PSLevelModifySelect : public ProgramState, public InputListener
{
public:
	PSLevelModifySelect(void);
	~PSLevelModifySelect(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();
	//void KeyDown(int key_);
	virtual void KeyDown(SDL_Keycode key_);
	virtual void GamePadButtonDown(SDL_GameControllerButton button_){}
	

private:
	void Init();
	string GetLevelString(int id_);
	std::vector<GLText> levelText;
	GLText prompt;
	Vector2 textPos;
	int selection; //the vector subscript index (not the database level id)
	std::map<int, int> levelMap; //vector subcript, level ID
	//InputHelper inputHelper;
	int lvlToStart;
	bool deletePrompt;
	ProgramState* nextProgramState;
};

