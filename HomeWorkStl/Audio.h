#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
class Audio
{
public:
	Audio();
	void PlayBGMusic(const char* path);
	void PlaySFX(const char* path);

	~Audio();
private:
	Mix_Music* M_BGMusic;
	Mix_Chunk* M_SFXMusic;	
};

