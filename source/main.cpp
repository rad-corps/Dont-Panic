
#include "game_state\GameLoop.h"

//The Original resolution of Space Invaders was 224 x 260 
//For comparison the Nintendo DS has a resolution of 292 x 192
//We're going to render this out at three times the original resolution (because we can)
const int iScreenWidth = 1024;
const int iScreenHeight = 768;

//update at 60-FPS
const float UPDATE_INTERVAL = 0.0166666666666666667f;

int main( int argc, char* argv[] )
{			

	{	
		GameLoop gameLoop(1024,768);
		gameLoop.Run();	
	} //scope ensures GameLoop destructor is called before returning from main

	return 0;
}
