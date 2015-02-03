#pragma once

#include <map>
#include <string>
#include "GLAHSoundInfo.h"


class GLAHSound
{
public:	
	~GLAHSound(void);
	static GLAHSound* Instance();

	
	unsigned int CreateSound(std::string path_, 
						bool loop_ = false, //true to loop
						bool play_ = false, //true to start playing immediately
						float vol_ = 0.2f, //0 to 1
						float pan = 0.0f //-1 (full left) to +1 (full right)
						);

	void Play(unsigned int sound_);
	void Stop(unsigned int sound_);
	void Pause(unsigned int sound_);

	//set frequency sample rate in HZ
	void SetPitch(unsigned int sound_, float freq_ = 44100.f);

	//vol_ 0 min, 1 max
	void SetVolume(unsigned int sound_, float vol_ = 0.2f);
	
	//pan -1 LEFT, +1 RIGHT
	void SetPan(unsigned int sound_, float pan_ = 0.0f);

private:
	GLAHSound(void);
	static GLAHSound* instance;

	//std::map<unsigned int, GLAHSoundInfo>
};

