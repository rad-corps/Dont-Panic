#pragma once
#include "ProgramState.h"
#include "GLAH/Vector.h"
#include "GLAH/InputHelper.h"
#include <vector>
#include "../game_objects/Platform.h"
#include "../game_objects/Cannon.h"
#include "../game_objects/Player.h"
#include "../game_objects/GLText.h"
#include "../game_objects/EnemySpawner.h"
#include "../game_objects/Goal.h"

enum TILE_CATEGORY
{
	PLATFORM,
	ENVIRONMENT,
	PLAYER,
	CANNON, 
	GOAL
};

class PSLevelEditor : public ProgramState
{
public:
	PSLevelEditor(void);
	~PSLevelEditor(void);

	virtual ProgramState* Update(float delta_);
	virtual void Draw();

	void KeyDown(int key_);

	static bool FindMatchingEnvironment(Platform& env_);
	static bool FindMatchingEnemySpawner(EnemySpawner& env_);

private:

	void ChangePlatformTile();
	void RemovePlatformTile();
	void UpdateRowCol();
	void HandleMouseDown();
	bool lmbDown;
	bool rmbDown;

	static int col;
	static int row;
	static int lastRow;
	static int lastCol;

	float uv[4];
	Vector2 pos;

	InputHelper inputHelper;
	std::vector<Platform> environment;
	std::vector<EnemySpawner> enemySpawners;
	Cannon cannon;
	Player player;
	Goal goal;
	

	bool inputName;
	bool saving;

	std::string levelName;
	GLText promptText;
	Vector2 mousePos;

	TILE_CATEGORY currentCategory;
};

