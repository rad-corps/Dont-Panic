#pragma once
#include "ProgramState.h"

class PSMainMenu : public ProgramState
{
public:
	PSMainMenu(void);
	~PSMainMenu(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();
};

