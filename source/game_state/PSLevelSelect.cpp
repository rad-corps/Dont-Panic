#include "PSLevelSelect.h"
#include <iostream>
#include "../sqlite/DatabaseManager.h"
#include "PSGameLoop.h"
#include "PSMainMenu.h"
using namespace std;

void MyLevelSelectKeyEvent(int key_, void* caller_)
{
	PSLevelSelect* caller = (PSLevelSelect*)caller_;
	caller->KeyDown(key_);
}

void PSLevelSelect::KeyDown(int key_)
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
	}
}

PSLevelSelect::PSLevelSelect(void)
{
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

	selection = 0;

	inputHelper.RegisterCallback(&MyLevelSelectKeyEvent, this);
	inputHelper.AddKey(KEY_UP);
	inputHelper.AddKey(KEY_DOWN);
	inputHelper.AddKey(KEY_ENTER);

	lvlToStart = -1;
}


PSLevelSelect::~PSLevelSelect(void)
{
}

ProgramState* PSLevelSelect::Update(float delta_)
{
	inputHelper.Update();

	if ( lvlToStart != -1)
		return new PSGameLoop(lvlToStart);

	if ( IsKeyDown( KEY_ESCAPE ) )
		return new PSMainMenu();
	
	return nullptr;
}

void PSLevelSelect::Draw()
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