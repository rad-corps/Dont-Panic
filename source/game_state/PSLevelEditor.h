#pragma once
#include "ProgramState.h"
#include "GLAH/Vector.h"
#include "GLAH/InputHelper.h"
#include <vector>
#include "../game_objects/Environment.h"

class PSLevelEditor : public ProgramState
{
public:
	PSLevelEditor(void);
	~PSLevelEditor(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

	void KeyDown(int key_);

	static bool FindMatchingEnvironment(Environment& env_);

private:

	static int col;
	static int row;

	float uv[4];
	Vector2 pos;

	InputHelper inputHelper;
	std::vector<Environment> environment;
};

