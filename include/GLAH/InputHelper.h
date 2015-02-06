#pragma once

#include "GLAHGraphics.h"
#include <vector>
#include <map>

typedef void (*KeyDownEvent)(int, void*);

class InputHelper
{

public:	
	InputHelper(void);
	~InputHelper(void);

	void AddKeys(std::vector<int> keys_);
	void AddKey(int key_);
	void RegisterCallback(KeyDownEvent callBack_, void* caller_);
	void Update();

private:
	
	KeyDownEvent callBack;
	void* caller;

	//ascii key code, key is currently down
	std::map<int, bool> keyList;
};

