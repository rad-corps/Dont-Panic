#include "GLAH/GLAHSound.h"
#include "GLAH/bass.h"

GLAHSound* GLAHSound::instance = nullptr;

GLAHSound*
GLAHSound::Instance()
{
	if ( instance == nullptr )
	{
		instance = new GLAHSound();    
		BASS_Init(-1,44100,0,0,0);
	}
	return instance;
}

GLAHSound::GLAHSound(void)
{
}


GLAHSound::~GLAHSound(void)
{
}

unsigned int GLAHSound::CreateSound(std::string path_, bool loop_, bool play_, float vol_, float pan_ )
{

	DWORD sound;
	if ( loop_ )
		sound = BASS_StreamCreateFile(false,path_.c_str(),0,0,BASS_SAMPLE_LOOP);
	else
		sound = BASS_StreamCreateFile(false,path_.c_str(),0,0,0);

	BASS_ChannelSetAttribute(sound, BASS_ATTRIB_VOL, vol_);
	BASS_ChannelSetAttribute(sound, BASS_ATTRIB_PAN, pan_);

	if ( play_ ) 
		Play(sound);

	return sound;
}

void GLAHSound::Play(unsigned int sound_)
{
	BASS_ChannelPlay(sound_,true);
}

void GLAHSound::Stop(unsigned int sound_)
{
	BASS_ChannelStop(sound_);
}

void GLAHSound::Pause(unsigned int sound_)
{
	BASS_ChannelPause(sound_);
}

void GLAHSound::SetPitch(unsigned int sound_, float freq_)
{
	BASS_ChannelSetAttribute(sound_, BASS_ATTRIB_FREQ, freq_);
}

void GLAHSound::SetVolume(unsigned int sound_, float vol_)
{
	BASS_ChannelSetAttribute(sound_, BASS_ATTRIB_VOL, vol_);
}

void GLAHSound::SetPan(unsigned int sound_, float pan_)
{
	BASS_ChannelSetAttribute(sound_, BASS_ATTRIB_PAN, pan_);
}