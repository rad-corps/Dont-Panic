#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include <vector>
#include "../GLAH/Vector.h"

class EnemySpawner : public GameObject
{
public:
	EnemySpawner();
	EnemySpawner(Enemy toClone_);
	~EnemySpawner(void);

	void Update(float delta_, std::vector<Enemy>& enemyList_);
	void Draw();
private:
	Enemy enemyMaster;
	float timer;

	float uv[4];
};

