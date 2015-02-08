#pragma once
#include "ProgramState.h"
#include "../game_objects/GLText.h"
#include <vector>
#include <map>
#include "GLAH/InputHelper.h"

class PSLevelSelect : public ProgramState
{
public:
	PSLevelSelect(void);
	~PSLevelSelect(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

	void KeyDown(int key_);

private:

	std::vector<GLText> levelText;
	Vector2 textPos;
	int selection; //the vector subscript index (not the database level id)
	std::map<int, int> levelMap; //vector subcript, level ID
	InputHelper inputHelper;
	int lvlToStart;
};

