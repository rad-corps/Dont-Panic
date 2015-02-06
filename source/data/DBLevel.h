#pragma once

#include "../sqlite/DatabaseManager.h"
#include "../game_objects/Environment.h"
#include "../game_objects/Player.h"
#include <vector>


class DBLevel
{
public:
	DBLevel(void);
	~DBLevel(void);

	void FillData(int level_, std::vector<Environment>& environment_, Player& player_);
	void SaveData(std::vector<Environment>& environment_, Player& player_);

private:
	DatabaseManager dm;
};

