#include "DBLevel.h"
#include <sstream>

using namespace std;

DBLevel::DBLevel(void)
{

}


DBLevel::~DBLevel(void)
{
}

void DBLevel::SaveData(std::vector<Platform>& platform_, Player& player_, Cannon& cannon_, std::string levelName_, std::vector<EnemySpawner>& spawners_, Goal& goal_)
{
	//save the level table first. record the ID
	char * error = "";
	std::stringstream levelValues;
	levelValues << " " << player_.Col() 
		<< ", " << player_.Row() 
		<< ", " << cannon_.Col() 
		<< ", " << cannon_.Row() 
		<< ", '" << levelName_ 
		<< "', " << goal_.Col() 
		<< ", " << goal_.Row() << " ";

	dm.Insert("./resources/db/dontpanic.db", "tbl_level", " player_tile_x, player_tile_y, cannon_tile_x, cannon_tile_y, name, goal_tile_x, goal_tile_y ", levelValues.str(), error);

	int id = dm.GetLastInsertedRowID();

	//save each table tile
	for ( auto& env : platform_ )
	{
		std::stringstream tileValues;
		tileValues << " " << id << ", " << env.Row() << ", " << env.Col() << ", " << (int)env.TileType() << " ";
		dm.Insert("./resources/db/dontpanic.db", "tbl_tile", " level_id, row, col, tile_type ", tileValues.str(), error);
	}

	//save each spawner tile
	for ( auto& spawner : spawners_ )
	{
		std::stringstream spawnerValues;	
		spawnerValues << " " << id << ", " << spawner.Row() << ", " << spawner.Col() << ", 0, 3.0 ";
		dm.Insert("./resources/db/dontpanic.db", "tbl_spawners", " level_id, row, col, type, freq ", spawnerValues.str(), error);
	}

	
}

void DBLevel::FillData(int level_, std::vector<Platform>& platform_, Player& player_, Cannon& cannon_, std::vector<EnemySpawner>& spawners_, Goal& goal_)
{
	char * error = "";
	
	//get platform_ tiles
	{
		std::stringstream ss;
		ss << "level_id=" << level_;		
		dm.Select("./resources/db/dontpanic.db", "tbl_tile", "*",ss.str(), "", error);
	
		for (int i = 0; i < dm.Rows(); ++i)
		{
			Platform env(dm.GetValueInt(i, "col"), dm.GetValueInt(i, "row"), dm.GetValueInt(i, "tile_type"));
			platform_.push_back(env);
		}
	}

	//get enemy spawners
	{
		std::stringstream ss;
		ss << "level_id=" << level_;		
		dm.Select("./resources/db/dontpanic.db", "tbl_spawners", "*",ss.str(), "", error);
	
		for (int i = 0; i < dm.Rows(); ++i)
		{
			ENEMY_TYPE et = (ENEMY_TYPE)dm.GetValueInt(i, "type");
			Enemy enemy(et, DIRECTION::DIR_LEFT, dm.GetValueInt(i,"col"), dm.GetValueInt(i,"row"));
			EnemySpawner spawner(enemy);			
			spawners_.push_back(spawner);
		}
	}

	//get level specific (player, cannon)
	{
		std::stringstream ss;
		ss << "id=" << level_;

		dm.Select("./resources/db/dontpanic.db", "tbl_level", "*", ss.str(), "", error);

		player_.SetPos(dm.GetValueInt(0, "player_tile_x"), dm.GetValueInt(0, "player_tile_y"));
		cannon_.SetPos(dm.GetValueInt(0, "cannon_tile_x"), dm.GetValueInt(0, "cannon_tile_y"));
		goal_.SetPos(dm.GetValueInt(0, "goal_tile_x"), dm.GetValueInt(0, "goal_tile_y"));
	}
}