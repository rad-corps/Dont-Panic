#pragma once
#include "ProgramState.h"
#include "../game_objects/GLText.h"

class PSMainMenu : public ProgramState
{
public:
	PSMainMenu(void);
	~PSMainMenu(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

private:
	GLText text1;
	GLText text2;
	GLText text3;

};
