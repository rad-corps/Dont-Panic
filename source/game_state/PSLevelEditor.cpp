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
int PSLevelEditor::lastCol = 0;
int PSLevelEditor::lastRow = 0;
Platform* PSLevelEditor::currentPlatform = nullptr;

//void PSLevelEditor::ScrollCallback(GLFWwindow* window_, double x_, double y_)
//{
//	//change the current platform tile
//	if ( y_ > 0 )
//	{
//		currentPlatform->DecrementTileType();
//	}
//	else if ( y_ < 0 )
//	{
//		currentPlatform->IncrementTileType();		
//	}		 
//}

void MyKeyEvent(int key_, void* caller_)
{
	PSLevelEditor* caller = (PSLevelEditor*)caller_;
	caller->KeyDown(key_);
}

void PSLevelEditor::Init()
{
	newProgramState=nullptr;
	UVTranslator trans(800,1280,16,16);
	trans.GetUV(uv, 16, 0);

	AddInputListener(this);

	saving = false;
	inputName = false;

	promptText.SetAlignment(TEXT_ALIGNMENT::ALIGN_CENTRE);
	promptText.SetPos(Vector2(1024/2, 700));
	promptText.SetText("");

	//glfwSetScrollCallback(GetWindow(), ScrollCallback); 

	lmbDown = false;
	rmbDown = false;
	currentCategory = TILE_CATEGORY::PLATFORM;
	
	if ( currentPlatform == nullptr )
	{
		currentPlatform = new Platform(col, row, ENVIRO_TILE::RED_BRICK_SURFACE);
	}

	//instructions
	showInstructions = true;
	std::vector<string> instructionsStr;
	instructionsStr.push_back("1: PLATFORMS");
	instructionsStr.push_back("2: DECORATIONS");
	//instructionsStr.push_back("3: ENEMIES");
	instructionsStr.push_back("SCROLL MOUSE WHEEL TO SWAP OBJECT");
	instructionsStr.push_back("LEFT MOUSE BUTTON TO PLACE");
	instructionsStr.push_back("RIGHT MOUSE BUTTON TO DELETE");
	instructionsStr.push_back("I: SHOW/HIDE INSTRUCTIONS");
	instructionsStr.push_back("P: SET PLAYER POSITION");
	instructionsStr.push_back("O: SET CANON POSITION");
	instructionsStr.push_back("G: SET GOAL POSITION");
	instructionsStr.push_back("E: SET ENEMY SPAWN POSITION");
	//instructionsStr.push_back("C: COPY TILE");
	//instructionsStr.push_back("V: PASTE TILE");
	instructionsStr.push_back("CTRL + S: SAVE LEVEL");

	GLText tempText;
	Vector2 instPos(30, 700);
	for (auto &text : instructionsStr)
	{
		tempText.SetText(text);
		tempText.SetPos(instPos);
		instructions.push_back(tempText);
		instPos.y -= 30;
	}
}

PSLevelEditor::PSLevelEditor(int levelID_) 
{
	
	DBLevel dbLevel;
	dbLevel.FillData(levelID_, platforms, player, cannon, enemySpawners, goal);
	Init();
	
}

PSLevelEditor::PSLevelEditor(void)
{
	Init();	
}


PSLevelEditor::~PSLevelEditor(void)
{
	if ( currentPlatform != nullptr ) 
	{
		delete currentPlatform;
		currentPlatform = nullptr;
	}
//	glfwSetScrollCallback(GetWindow(), NULL); 
}

bool PSLevelEditor::FindMatchingPlatform(Platform& env_)
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

void PSLevelEditor::RemovePlatformTile()
{
	auto it = find_if(platforms.begin(), platforms.end(), FindMatchingPlatform );

	//if found remove
	if ( it != platforms.end() )
	{		
		it = platforms.erase(it);
	}
}

void PSLevelEditor::ChangePlatformTile()
{
	//find platform tile at this space.
	auto it = find_if(platforms.begin(), platforms.end(), FindMatchingPlatform );
		
	//if not found, add one
	if ( it == platforms.end() )
	{
		platforms.push_back(Platform(col, row, currentPlatform->TileType()));
	}
}

void PSLevelEditor::KeyDown(SDL_Keycode key_)
{
	if ( inputName )
	{
		if (key_ == SDLK_RETURN)
		{
			//submit
			cout << "...Saving Level..." << endl;
			saving = false;
			DBLevel db;
			db.SaveData(platforms, player, cannon, levelName, enemySpawners, goal);
			inputName = false;
			promptText.SetText(levelName + " Saved");
		}
		else if ( key_ == SDLK_BACKSPACE )
		{
			if ( levelName.size() > 0 )
			{
				levelName = levelName.substr(0, levelName.size()-1);
			}
		}
		else
		{			
			//turn key into a char
			char x = (char)key_;
			levelName += x;
		}
	}
	if ( !inputName )
	{
		if (key_ == SDLK_UP)
			++row;
		if (key_ == SDLK_DOWN)	
			--row;
		if( key_ == SDLK_LEFT)
			--col;
		if( key_ == SDLK_RIGHT)
			++col;
		if ( key_ == SDLK_SPACE )
		{
			ChangePlatformTile();
		}
		if ( key_ == SDLK_e )
		{
			//find enemySpawner tile at this space.
			auto it = find_if(enemySpawners.begin(), enemySpawners.end(), FindMatchingEnemySpawner);
		
			//if found, we want to set this platform to the next tile
			if ( it != enemySpawners.end() )
			{
				it = enemySpawners.erase(it);
			}
			else //if no tiles found, add a new one. 
			{
				enemySpawners.push_back(EnemySpawner(Enemy(ENEMY_TYPE::SKELETON, DIRECTION::DIR_LEFT, col, row)));
			}
		}
		if ( key_ == SDLK_o )
		{
			cannon.SetPos(col, row);
		}
		if ( key_ == SDLK_p)
		{
			player.SetPos(col, row);
		}
		if ( key_ == SDLK_g )
		{
			goal.SetPos(col, row);
		}
		if ( key_ == SDLK_1 )
		{
			currentPlatform->SetTileset(ENVIRO_TILE::PLATFORMS_START);
		}
		if ( key_ == SDLK_2 )
		{
			currentPlatform->SetTileset(ENVIRO_TILE::DECORATION_BEGIN);
		}
		if ( key_ == SDLK_i )
		{
			showInstructions = !showInstructions;
		}
		if ( key_ == SDLK_ESCAPE )
		{
			RemoveInputListener();
			newProgramState = new PSMainMenu();
		}
	}
}

void PSLevelEditor::UpdateRowCol()
{
	//get mouse location
	int mouseX, mouseY;
	GetMouseLocation(mouseX, mouseY);
	mousePos.x = (float)mouseX;//offset x due to drawing from centre
	mousePos.y = (float)mouseY;
	//get row and column based on mousePos
	col = mousePos.x / 32;
	row = mousePos.y / 32;
}

void PSLevelEditor::HandleMouseDown()
{
	//if left mouse button is down
	if ( GetMouseButtonDown(0) )
	{
		if (!lmbDown || (lastCol != col || lastRow != row))
		{
			ChangePlatformTile();
			lmbDown = true;
		}
	}
	else if ( !GetMouseButtonDown(0) )
	{
		lmbDown = false;
	}

	if ( GetMouseButtonDown(1) )
	{
		if (!rmbDown || (lastCol != col || lastRow != row))
		{
			RemovePlatformTile();
			rmbDown = true;
		}
	}
	else if ( !GetMouseButtonDown(1) )
	{
		rmbDown = false;
	}
}

ProgramState* PSLevelEditor::Update(float delta_)
{
	pos = Vector2(col * 32, row * 32);
	
	UpdateRowCol();
	HandleMouseDown();

	//inputHelper.Update();

//	if ( IsKeyDown(KEY_ESCAPE) ) 
//		return new PSMainMenu();

	//if ( IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_S) && !saving)
	//{
	//	inputName = true;
	//	levelName = "";
	//}

	if ( inputName )
	{
		promptText.SetText("Enter Level Name - " + levelName);
	}

	//if (  !IsKeyDown(KEY_LEFT_CONTROL) || !IsKeyDown(KEY_S) ) 
	//{
	//	saving = false;
	//}

	lastCol = col;
	lastRow = row;

	return newProgramState;
}
void PSLevelEditor::Draw()
{
	for ( auto &env : platforms ) env.Draw();
	for ( auto &spawner : enemySpawners ) spawner.Draw();
	cannon.Draw();
	player.Draw();
	goal.Draw();
	

	currentPlatform->SetX(pos.x);
	currentPlatform->SetY(pos.y);
	currentPlatform->Draw(0.3f);
	//SetSpriteUVCoordinates(SpriteSheet::Sprite(), uv);
	//MoveSprite(SpriteSheet::Sprite(), pos.x, pos.y);
	//DrawSprite(SpriteSheet::Sprite());

	promptText.Draw();

	if ( showInstructions )
		for ( auto& text : instructions )
			text.Draw();
	
}