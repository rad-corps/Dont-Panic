#include "GLAH/InputHelper.h"


InputHelper::InputHelper(void)
{
}


InputHelper::~InputHelper(void)
{
}


void InputHelper::AddKeys(std::vector<int> keys_)
{
	for (int i = 0; i < keys_.size(); ++i )
	{
		keyList[keys_[i]] = IsKeyDown(keys_[i]);
	}	
}

void InputHelper::AddKey(int key_)
{
	keyList[key_] = IsKeyDown(key_);
}

void InputHelper::RegisterCallback(KeyDownEvent callBack_, void* caller_)
{
	callBack = callBack_;
	caller = caller_;
}

void InputHelper::Update()
{
	for(auto iterator = keyList.begin(); iterator != keyList.end(); iterator++) 
	{
		//If key was not down last frame, but is now, then we want to trigger the event. 
		if ( keyList[iterator->first] == false && IsKeyDown(iterator->first))
		{
			keyList[iterator->first] = true;
			callBack(iterator->first, caller);
		}

		//if key was down last frame, but not this frame, set its bool back to false
		if ( keyList[iterator->first] == true && !IsKeyDown(iterator->first) )
		{
			keyList[iterator->first] = false;
		}
	}
}