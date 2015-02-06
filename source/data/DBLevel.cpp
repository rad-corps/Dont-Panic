#include "DBLevel.h"
#include <sstream>

using namespace std;

DBLevel::DBLevel(void)
{

}


DBLevel::~DBLevel(void)
{
}

void DBLevel::FillData(int level_, std::vector<Environment>& environment_, Player& player_)
{
	char * error = "";
	{
		std::stringstream ss;
		ss << "level_id=" << level_;		
		dm.Select("./resources/db/dontpanic.db", "tbl_tile", "*",ss.str(), "", error);
	
		for (int i = 0; i < dm.Rows(); ++i)
		{
			Environment env(dm.GetValueInt(i, "col"), dm.GetValueInt(i, "row"), (ENVIRO_TILE)dm.GetValueInt(i, "tile_type"));
			environment_.push_back(env);
		}
	}
	{
		std::stringstream ss;
		ss << "id=" << level_;

		dm.Select("./resources/db/dontpanic.db", "tbl_level", "*", ss.str(), "", error);

		player_.SetPos(dm.GetValueInt(0, "player_tile_x"), dm.GetValueInt(0, "player_tile_y"));
	}
}