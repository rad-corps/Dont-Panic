#pragma once

#include "GameObject.h"
#include "../spritesheet/SpriteSheet.h"
#include <string>
#include <vector>
#include <array>
#include "GLAH/Vector.h"

enum TEXT_ALIGNMENT
{
	ALIGN_LEFT,
	ALIGN_CENTRE,
	ALIGN_RIGHT
};

class GLText : public GameObject
{
public:
	GLText();
	~GLText(void);

	virtual void Update(float delta_);
	virtual void Draw();

	void SetAlignment(TEXT_ALIGNMENT alignment_);
	void SetText(std::string text_);
	void SetPos(Vector2 pos_);

private:
	std::vector<std::array<float, 4>> uvs;
	TEXT_ALIGNMENT alignment;
};
