#include "PSLevelModifySelect.h"
#include <iostream>
#include "../sqlite/DatabaseManager.h"
#include "PSLevelEditor.h"
#include "PSMainMenu.h"
#include "../globals/consts.h"
using namespace std;

//void MyModifyLevelSelectKeyEvent(int key_, void* caller_)
//{
//	PSLevelModifySelect* caller = (PSLevelModifySelect*)caller_;
//	caller->KeyDown(key_);
//}

void PSLevelModifySelect::KeyDown(SDL_Keycode key_)
{
	stringstream promptText;

	switch (key_)
	{
	case SDLK_UP : 
		if ( selection > 0 )
			--selection;
		break;
	case SDLK_DOWN : 
		if ( selection < levelText.size() - 1 )
			++selection;
		break;
	case SDLK_RETURN : 
		nextProgramState = new PSLevelEditor(levelMap[selection]);
		break;
	case SDLK_DELETE : 
		lvlToStart = levelMap[selection];
		deletePrompt = true;		
		promptText << "Are you sure you want to delete level " << GetLevelString(lvlToStart) << " Y/N";
		prompt.SetText(promptText.str());
		prompt.SetPos(Vector2(50, 300));
		break;	
	case SDLK_ESCAPE :
		nextProgramState = new PSMainMenu();
		break;
	}

	if  ( deletePrompt ) 
	{
		if ( key_ == SDLK_y )
		{
			cout << "deleting level " << GetLevelString(lvlToStart) << endl;
			DatabaseManager dm;
			char * error = "";
			{
				stringstream whereStatement;
				whereStatement << "id = " << lvlToStart;
				dm.Delete("./resources/db/dontpanic.db", "tbl_level", whereStatement.str(), error);			
			}
			{
				stringstream whereStatement;
				whereStatement << "level_id = " << lvlToStart;
				dm.Delete("./resources/db/dontpanic.db", "tbl_spawners", whereStatement.str(), error);			
				dm.Delete("./resources/db/dontpanic.db", "tbl_tile", whereStatement.str(), error);			
			}
			Init();
		}
		if ( key_ == SDLK_n )
		{
			cout << "not deleting level " << GetLevelString(lvlToStart) << endl;
			Init();
		}
	}
}

void PSLevelModifySelect::Init()
{
	selection = 0;
	levelMap.clear();
	levelText.clear();

	cout << endl << endl << "-------Select a Level---------" << endl;
	DatabaseManager dm;
	char * error = "";
	dm.Select("./resources/db/dontpanic.db", "tbl_level", "id, name", "", "", error);

	textPos = Vector2(SCREEN_W*0.5, 100);
	GLText txtTemp;
	txtTemp.SetAlignment(TEXT_ALIGNMENT::ALIGN_CENTRE);
	txtTemp.SetHUD(true);
	
	for ( int i = 0; i < dm.Rows(); ++i )
	{
		levelMap[i] = dm.GetValueInt(i, "id");
		txtTemp.SetText(dm.GetValueString(i, "name"));
		txtTemp.SetPos(textPos);
		
		levelText.push_back(txtTemp);
		textPos += Vector2(0, 30);
	}

	lvlToStart = -1;
	deletePrompt = false;
}

PSLevelModifySelect::PSLevelModifySelect(void) : nextProgramState(nullptr)
{
	Init();
	AddInputListener(this);
}


PSLevelModifySelect::~PSLevelModifySelect(void)
{
	//RemoveInputListener(this);
}

ProgramState* PSLevelModifySelect::Update(float delta_)
{
	return nextProgramState;
}

string PSLevelModifySelect::GetLevelString(int id_)
{
	int vectorSubscript = -1;
	//find the vector subscript based on the level id
	for ( auto & sub_id_pair : levelMap )
	{
		if ( sub_id_pair.second == id_ )
		{
			vectorSubscript = sub_id_pair.first;
		}
	}

	if ( vectorSubscript != -1 ) 
	{
		return levelText[vectorSubscript].GetText();
	}
	return "";
}

void PSLevelModifySelect::Draw()
{	
	if ( !deletePrompt ) 
	{
		for ( int i = 0; i < levelText.size(); ++i )
		{
			GLText txt = levelText[i];
			if ( i == selection )
			{
				txt.SetText("--" + txt.GetText() + "--");
			}
			txt.Draw();		
		}
	}
	if  (deletePrompt ) 
	{
		prompt.Draw();
	}
}