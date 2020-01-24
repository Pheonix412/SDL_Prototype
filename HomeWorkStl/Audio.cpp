#include "Audio.h"



Audio::Audio(){
	M_BGMusic = nullptr;
	M_SFXMusic = nullptr;
}

void Audio::PlayBGMusic(const char * path){
	M_BGMusic = Mix_LoadMUS(path);
	if (M_BGMusic != nullptr) {
		if (!Mix_PlayingMusic()) {
			if (Mix_PlayMusic(M_BGMusic, 0) == -1) {
				std::cout << "load background music -failed: " << SDL_GetError() << std::endl;
			}
			else {
				Mix_VolumeMusic(2);
			}
		}
	}
}

void Audio::PlaySFX(const char * path){
	M_SFXMusic = Mix_LoadWAV(path);
	if (Mix_Playing(2) == 0) {
		Mix_VolumeChunk(M_SFXMusic, 2);
		Mix_PlayChannel(2, M_SFXMusic, 0);
	}
}


Audio::~Audio()
{
}
