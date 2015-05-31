#pragma once

#include "../GLAH/Vector.h"

class CannonListener
{
public:
	virtual void ShotFired(Vector2 pos_, Vector2 velocity_) = 0;

	//CannonListener();
	//virtual ~CannonListener(); 

private:
	

};