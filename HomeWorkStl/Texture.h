#pragma once

#include <SDL.h>
class Texture
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
private:
	SDL_Texture *M_Texture;
	int M_Width;
	int M_Height;

public:
	Texture();
	bool LoadImgFromFile(const char* path, SDL_Renderer* renderer);

	void Draw(SDL_Renderer* renderer, int x, int y, SDL_Rect* sourceRect = NULL);
	int GetImageWidth() { return M_Width; }
	int GetImageHeight() { return M_Height; }
	void ResetTexture();

	~Texture();
};

