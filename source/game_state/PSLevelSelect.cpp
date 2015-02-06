#include "PSLevelSelect.h"
#include <iostream>
#include "../sqlite/DatabaseManager.h"
#include "PSGameLoop.h"
using namespace std;

PSLevelSelect::PSLevelSelect(void)
{
	cout << endl << endl << "-------Select a Level---------" << endl;
	DatabaseManager dm;
	char * error = "";
	dm.Select("./resources/db/dontpanic.db", "tbl_level", "id", "", "", error);
	
	for ( int i = 0; i < dm.Rows(); ++i )
	{
		cout << dm.GetValueInt(i, "id") << endl;
	}
}


PSLevelSelect::~PSLevelSelect(void)
{
}

ProgramState* PSLevelSelect::Update(float delta_)
{
	cout << endl;
	int level = -1;
	cout << "enter the level to play: ";
	cin >> level;

	return new PSGameLoop(level);
}

void PSLevelSelect::Draw()
{}