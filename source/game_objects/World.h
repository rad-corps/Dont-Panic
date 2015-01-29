#pragma once

#include "Player.h"
#include "Environment.h"
#include <vector>

struct World
{
	Player player;
	std::vector<Environment> environment;
};