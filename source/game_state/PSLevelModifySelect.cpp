#include "PSLevelModifySelect.h"
#include <iostream>
#include "../sqlite/DatabaseManager.h"
#include "PSLevelEditor.h"
#include "PSMainMenu.h"
using namespace std;

void MyModifyLevelSelectKeyEvent(int key_, void* caller_)
{
	PSLevelModifySelect* caller = (PSLevelModifySelect*)caller_;
	caller->KeyDown(key_);
}

void PSLevelModifySelect::KeyDown(int key_)
{
	switch (key_)
	{
	case KEY_UP : 
		if ( selection > 0 )
			--selection;
		break;
	case KEY_DOWN : 
		if ( selection < levelText.size() - 1 )
			++selection;
		break;
	case KEY_ENTER : 
		lvlToStart = levelMap[selection];
		break;
	case KEY_DELETE : 
		lvlToStart = levelMap[selection];
		deletePrompt = true;
		stringstream promptText;
		promptText << "Are you sure you want to delete level " << GetLevelString(lvlToStart) << " Y/N";
		prompt.SetText(promptText.str());
		prompt.SetPos(Vector2(50, 300));
		break;	
	}

	if  ( deletePrompt ) 
	{
		if ( key_ == KEY_Y )
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
		if ( key_ == KEY_N )
		{
			cout << "not deleting level " << GetLevelString(lvlToStart) << endl;
			Init();
		}
	}
}

void PSLevelModifySelect::Init()
{
	levelMap.clear();
	levelText.clear();

	cout << endl << endl << "-------Select a Level---------" << endl;
	DatabaseManager dm;
	char * error = "";
	dm.Select("./resources/db/dontpanic.db", "tbl_level", "id, name", "", "", error);

	textPos = Vector2(1024/2, 700);
	GLText txtTemp;
	txtTemp.SetAlignment(TEXT_ALIGNMENT::ALIGN_CENTRE);
	
	
	for ( int i = 0; i < dm.Rows(); ++i )
	{
		levelMap[i] = dm.GetValueInt(i, "id");
		txtTemp.SetText(dm.GetValueString(i, "name"));
		txtTemp.SetPos(textPos);
		levelText.push_back(txtTemp);
		textPos -= Vector2(0, 30);
	}

	lvlToStart = -1;
	deletePrompt = false;
}

PSLevelModifySelect::PSLevelModifySelect(void)
{
	Init();

	selection = 0;

	inputHelper.RegisterCallback(&MyModifyLevelSelectKeyEvent, this);
	inputHelper.AddKey(KEY_UP);
	inputHelper.AddKey(KEY_DOWN);
	inputHelper.AddKey(KEY_ENTER);
	inputHelper.AddKey(KEY_DELETE);
	inputHelper.AddKey(KEY_N);
	inputHelper.AddKey(KEY_Y);
	inputHelper.AddKey(KEY_ESCAPE);


}


PSLevelModifySelect::~PSLevelModifySelect(void)
{
}

ProgramState* PSLevelModifySelect::Update(float delta_)
{
	inputHelper.Update();

	if ( lvlToStart != -1 && !deletePrompt)
		return new PSLevelEditor(lvlToStart);
	
	if ( IsKeyDown( KEY_ESCAPE ) )
		return new PSMainMenu();	

	return nullptr;
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