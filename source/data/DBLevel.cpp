#include "DBLevel.h"
#include <sstream>

using namespace std;

DBLevel::DBLevel(void)
{

}


DBLevel::~DBLevel(void)
{
}

void DBLevel::SaveData(std::vector<Environment>& environment_, Player& player_)
{
	//save the level table first. record the ID
	//tbl_level
	char * error = "";
	std::stringstream playerValues;
	playerValues << " " << player_.Pos().x << ", " << player_.Pos().y << " ";
	dm.Insert("./resources/db/dontpanic.db", "tbl_level", " player_tile_x, player_tile_y ", playerValues.str(), error);

	int id = dm.GetLastInsertedRowID();

	for ( auto& env : environment_ )
	{
		std::stringstream tileValues;
		tileValues << " " << id << ", " << env.Row() << ", " << env.Col() << ", " << (int)env.TileType() << " ";
		dm.Insert("./resources/db/dontpanic.db", "tbl_tile", " level_id, row, col, tile_type ", tileValues.str(), error);
	}

	
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