#pragma once

#include "GameObject.h"

//#include "GLAH\GLAHInput.h"
#include "../GLAH/GLAHGraphics.h"


class Goal : public GameObject
{
public:

	//must call SetPos after constructor to validate Goal State
	Goal(void);
	~Goal(void);

	virtual void Update(float delta_);
	virtual void Draw();


private:
	float UVs[4];
};

