#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
class Audio
{
public:
	Audio();
	//plays background music
	void PlayBGMusic(const char* path);
	//plays a sound effects
	void PlaySFX(const char* path);

	~Audio();
private:
	Mix_Music* M_BGMusic;
	Mix_Chunk* M_SFXMusic;	
};

