#pragma once
#include "ProgramState.h"
#include "GLAH/Vector.h"
#include "GLAH/InputHelper.h"

class PSLevelEditor : public ProgramState
{
public:
	PSLevelEditor(void);
	~PSLevelEditor(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

	void KeyDown(int key_);

private:

	int col;
	int row;

	float uv[4];
	Vector2 pos;

	InputHelper inputHelper;
};

