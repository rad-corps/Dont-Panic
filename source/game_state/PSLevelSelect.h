#pragma once
#include "ProgramState.h"

class PSLevelSelect : public ProgramState
{
public:
	PSLevelSelect(void);
	~PSLevelSelect(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

private:

};

