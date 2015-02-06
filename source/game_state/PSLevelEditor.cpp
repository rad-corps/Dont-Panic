#include "PSLevelEditor.h"
#include "GLAH/GLAHGraphics.h"
#include "PSMainMenu.h"
#include "../spritesheet/SpriteSheet.h"
#include "../spritesheet/UVTranslator.h"
#include "../data/DBLevel.h"
#include <iostream>
#include <algorithm>

using namespace std;

int PSLevelEditor::col = 0;
int PSLevelEditor::row = 0;

void MyKeyEvent(int key_, void* caller_)
{
	PSLevelEditor* caller = (PSLevelEditor*)caller_;
	caller->KeyDown(key_);
}

PSLevelEditor::PSLevelEditor(void)
{
	cout << endl << "--------Don't Panic : Level Editor----------" << endl;
	cout << "Move Active Tile            Arrow Keys" << endl;
	cout << "Change Active Tile          Space Bar" << endl;
	cout << "Save Level                  CTRL + S" << endl;
	cout << "Quit To Main Menu           Escape key" << endl;

	UVTranslator trans(800,1280,16,16);
	trans.GetUV(uv, 16, 0);

	inputHelper.RegisterCallback(&MyKeyEvent, this);
	inputHelper.AddKey(KEY_LEFT);
	inputHelper.AddKey(KEY_RIGHT);
	inputHelper.AddKey(KEY_UP);
	inputHelper.AddKey(KEY_DOWN);
	inputHelper.AddKey(KEY_SPACE);

	saving = false;
}


PSLevelEditor::~PSLevelEditor(void)
{
}

bool PSLevelEditor::FindMatchingEnvironment(Environment& env_)
{
	if ( env_.Col() == col && env_.Row() == row )
		return true;
	return false;
}

void PSLevelEditor::KeyDown(int key_)
{
	switch (key_)
	{
	case KEY_UP : 
		++row;
		break;
	case KEY_DOWN : 
		--row;
		break;
	case KEY_LEFT : 
		--col;
		break;
	case KEY_RIGHT : 
		++col;
		break;
	case KEY_SPACE : 
		//find environment tile at this space.
		auto it = find_if(environment.begin(), environment.end(), FindMatchingEnvironment );
		
		//if found, we want to set this environment to the next tile
		if ( it != environment.end() )
		{
			//change to the next tile
			it->IncrementTileType();
			
			//if we are at the end, remove the tile
			if ( it->TileType() == ENVIRO_TILE::ENVIRO_TILE_END )
			{
				it = environment.erase(it);
			}
		}
		else //if no tiles found, add a new one. 
		{
			environment.push_back(Environment(col, row, ENVIRO_TILE::RED_BRICK_SURFACE));
		}
	}
}



ProgramState* PSLevelEditor::Update(float delta_)
{
	pos = Vector2(col * 32, row * 32);

	inputHelper.Update();

	if ( IsKeyDown(KEY_ESCAPE) ) 
		return new PSMainMenu();

	if ( IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_S) && !saving)
	{
		cout << "...Saving Level..." << endl;
		saving = true;
		DBLevel db;
		Player temp;
		db.SaveData(environment, temp);
	}

	if (  !IsKeyDown(KEY_LEFT_CONTROL) || !IsKeyDown(KEY_S) ) 
	{
		saving = false;
	}

	return nullptr;
}
void PSLevelEditor::Draw()
{
	for ( auto &env : environment ) 
	{
		env.Draw();
	}

	SetSpriteUVCoordinates(SpriteSheet::Sprite(), uv);
	MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
	DrawSprite(SpriteSheet::Sprite());
}