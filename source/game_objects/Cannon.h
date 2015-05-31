#pragma once

#include "GameObject.h"

//#include "GLAH\GLAHInput.h"
#include "../GLAH/GLAHGraphics.h"
#include "../listeners/CannonListener.h"

class Cannon : public GameObject
{
public:
	Cannon(void);
	~Cannon(void);

	virtual void Update(float delta_);
	virtual void Draw();

	void RegisterCannonListener(CannonListener *cannonListener_);


private:
	float UVs[4];
	float rotation;
	float reloadTime;
	CannonListener* cannonListener;
};

