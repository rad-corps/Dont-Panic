#include "DBLevel.h"
#include <sstream>

using namespace std;

DBLevel::DBLevel(void)
{

}


DBLevel::~DBLevel(void)
{
}

void DBLevel::SaveData(std::vector<Environment>& environment_, Player& player_, Cannon& cannon_, std::string levelName_)
{
	//save the level table first. record the ID
	char * error = "";
	std::stringstream levelValues;
	levelValues << " " << player_.Col() << ", " << player_.Row() << ", " << cannon_.Col() << ", " << cannon_.Row() << ", '" << levelName_ << "' ";
	dm.Insert("./resources/db/dontpanic.db", "tbl_level", " player_tile_x, player_tile_y, cannon_tile_x, cannon_tile_y, name ", levelValues.str(), error);

	int id = dm.GetLastInsertedRowID();

	//save each table tile
	for ( auto& env : environment_ )
	{
		std::stringstream tileValues;
		tileValues << " " << id << ", " << env.Row() << ", " << env.Col() << ", " << (int)env.TileType() << " ";
		dm.Insert("./resources/db/dontpanic.db", "tbl_tile", " level_id, row, col, tile_type ", tileValues.str(), error);
	}

	
}

void DBLevel::FillData(int level_, std::vector<Environment>& environment_, Player& player_, Cannon& cannon_)
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
		cannon_.SetPos(dm.GetValueInt(0, "cannon_tile_x"), dm.GetValueInt(0, "cannon_tile_y"));
	}
}