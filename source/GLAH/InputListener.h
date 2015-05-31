#pragma once

#include <SDL2/SDL.h>

class InputListener
{
public: 
	virtual void KeyDown(SDL_Keycode key_) = 0;
	virtual void GamePadButtonDown(SDL_GameControllerButton button_) = 0;
};