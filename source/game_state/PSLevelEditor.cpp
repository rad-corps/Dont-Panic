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
	cout << "Place Cannon                C Key" << endl;
	cout << "Quit To Main Menu           Escape key" << endl;

	UVTranslator trans(800,1280,16,16);
	trans.GetUV(uv, 16, 0);

	inputHelper.RegisterCallback(&MyKeyEvent, this);
	inputHelper.AddKey(KEY_LEFT);
	inputHelper.AddKey(KEY_RIGHT);
	inputHelper.AddKey(KEY_UP);
	inputHelper.AddKey(KEY_DOWN);
	inputHelper.AddKey(KEY_SPACE);
	inputHelper.AddKey(KEY_ENTER);
	

	vector<int> keys;
	//A to Z
	for (int i = 65; i <= 90; ++i)
	{
		keys.push_back(i);
	}

	inputHelper.AddKeys(keys);

	saving = false;
	inputName = false;

	promptText.SetAlignment(TEXT_ALIGNMENT::ALIGN_CENTRE);
	promptText.SetPos(Vector2(1024/2, 700));
	promptText.SetText("");
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

bool PSLevelEditor::FindMatchingEnemySpawner(EnemySpawner& spawner_)
{
	if ( spawner_.Col() == col && spawner_.Row() == row )
		return true;
	return false;
}

void PSLevelEditor::KeyDown(int key_)
{
	if ( inputName )
	{
		if (key_ == KEY_ENTER)
		{
			//submit
			cout << "...Saving Level..." << endl;
			saving = false;
			DBLevel db;
			db.SaveData(environment, player, cannon, levelName, enemySpawners);
			inputName = false;
			promptText.SetText(levelName + " Saved");
		}
		else
		{			
			//turn key into a char
			char x = (char)key_;
			levelName += x;
			cout << "Level Name: " << levelName;
		}
	}
	if ( !inputName )
	{
		if (key_ == KEY_UP)
			++row;
		if (key_ == KEY_DOWN)	
			--row;
		if( key_ == KEY_LEFT)
			--col;
		if( key_ == KEY_RIGHT)
			++col;
		if ( key_ == KEY_SPACE )
		{
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
		if ( key_ == KEY_E )
		{
			//find enemySpawner tile at this space.
			auto it = find_if(enemySpawners.begin(), enemySpawners.end(), FindMatchingEnemySpawner);
		
			//if found, we want to set this environment to the next tile
			if ( it != enemySpawners.end() )
			{
				it = enemySpawners.erase(it);
			}
			else //if no tiles found, add a new one. 
			{
				enemySpawners.push_back(EnemySpawner(Enemy(ENEMY_TYPE::SKELETON, DIRECTION::DIR_LEFT, col, row)));
			}
		}
		if ( key_ == KEY_C )
		{
			cannon.SetPos(col, row);
		}
		if ( key_ == KEY_P )
		{
			player.SetPos(col, row);
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
		inputName = true;
		levelName = "";
	}

	if ( inputName )
	{
		promptText.SetText("Enter Level Name - " + levelName);
	}

	if (  !IsKeyDown(KEY_LEFT_CONTROL) || !IsKeyDown(KEY_S) ) 
	{
		saving = false;
	}

	return nullptr;
}
void PSLevelEditor::Draw()
{
	for ( auto &env : environment ) env.Draw();
	for ( auto &spawner : enemySpawners ) spawner.Draw();
	cannon.Draw();
	player.Draw();
	

	SetSpriteUVCoordinates(SpriteSheet::Sprite(), uv);
	MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
	DrawSprite(SpriteSheet::Sprite());

	promptText.Draw();
}