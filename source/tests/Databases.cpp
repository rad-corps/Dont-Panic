#include "Databases.h"
#include "../sqlite/DatabaseManager.h"
#include <iostream>
#include <map>

using namespace std;

void CreateDatabase()
{
	cout << "CreateDatabase" << endl;
	DatabaseManager dm;

	map<string, DB_SQLITE_DATATYPE> dbFields;

	dbFields["id"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
	dbFields["name"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_TEXT;
	dbFields["cols"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
	dbFields["rows"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
	dbFields["end_tile_x"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
	dbFields["end_tile_y"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
	dbFields["player_tile_x"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
	dbFields["player_tile_y"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;

	char* error = NULL;

	dm.Create("dontpanic.db", "tbl_level", dbFields, error);
	if ( error != NULL )
		cout << "error creating dontpanic.db: " << error << endl;
}