//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// OuterLoop.cpp
/////////////////////////////////////////////////////////////////////////

#include "OuterLoop.h"
#include "../GLAH/GLAHGraphics.h"
#include "ProgramState.h"
#include "PSGameLoop.h"
#include "PSMainMenu.h"
//#include "PSMainMenu.h"
//#include "AIE.h"
//#include "windows.h"
//#include "FrameworkHelpers.h"
//#include "wtypes.h"
#include "../data/FileSettings.h"
#include "../spritesheet/SpriteSheet.h"
#include <iostream>
#include "../globals/consts.h"

using namespace std;

// Get the horizontal and vertical screen sizes in pixel
//void GetDesktopResolution(int& horizontal, int& vertical)
//{
//   RECT desktop;
//   // Get a handle to the desktop window
//   const HWND hDesktop = GetDesktopWindow();
//   // Get the size of screen to the variable desktop
//   GetWindowRect(hDesktop, &desktop);
//   // The top left corner will have coordinates (0,0)
//   // and the bottom right corner will have coordinates
//   // (horizontal, vertical)
//   horizontal = desktop.right;
//   vertical = desktop.bottom;
//}

OuterLoop::OuterLoop(void)
	: updateInterval(0.0166666666666666667f)
{
	//set the screen resolution variables in the filesettings map
	//int hor, ver;
	//GetDesktopResolution(hor, ver);
	//cout << "Screen Res: " << hor << "x" << ver << endl;
	FileSettings::AddIntValue("SCREEN_W", SCREEN_W);
	FileSettings::AddIntValue("SCREEN_H", SCREEN_H);

	//Initialise( FileSettings::GetInt("SCREEN_W"), FileSettings::GetInt("SCREEN_H"),  FileSettings::GetBool("FULL_SCREEN"), "Dont Panic" );
	Initialise( SCREEN_W, SCREEN_H, false, "Dont Panic" );
	SpriteSheet::Init();
	
	//AddFont("./resources/fonts/arial.fnt");

	cout << "OuterLoop()" << endl;

	mouseX = 0.0;
	mouseY = 0.0;
	gameTimer = 0.0f;

	shuttingDown = false;

	currentProgramState = new PSMainMenu();	
}


OuterLoop::~OuterLoop(void)
{
	cout << "~OuterLoop()" << endl;
}

void OuterLoop::Go()
{
	
	do 
	{
		//if this is set to something other than null, we switch states. 
		ProgramState* newState = nullptr;

		//update only if we have reached an updateInterval
		gameTimer += GetDeltaTime();
		if ( gameTimer > updateInterval ) 
		{
			gameTimer -= updateInterval;
			newState = currentProgramState->Update(updateInterval);
		}

		//change state if required
		if ( newState != nullptr )
		{
			delete currentProgramState;
			currentProgramState = newState;
		}

		currentProgramState->Draw();
			
	}while ( FrameworkUpdate() == false );
}
