#pragma once

#include "GameObject.h"
#include "../spritesheet/SpriteSheet.h"
#include <string>
#include <vector>
#include <array>
#include "GLAH/Vector.h"

class GLText : public GameObject
{
public:
	GLText();
	~GLText(void);

	virtual void Update(float delta_);
	virtual void Draw();

	void SetText(std::string text_);
	void SetPos(Vector2 pos_);

private:
	std::vector<std::array<float, 4>> uvs;
};

