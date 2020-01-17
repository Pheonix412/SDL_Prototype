#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
class Texture
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
private:
	//this is a pointer for the texture 
	SDL_Texture* M_Texture;
	//this holds the width and the height for the texture 
	int M_Width;
	int M_Height;
public:
	//this is the constructor for the texture
	Texture();
	//this ia function that loads a image from the file 
	bool LoadImgFromFile(const char* path, SDL_Renderer* renderer);
	//this is the draw function for the texture 
	void Draw(SDL_Renderer* renderer, int x, int y, SDL_Rect* sourceRect = NULL);
	//this gets the iamge width
	int GetImageWidth() { return M_Width; }
	//this gets the image height 
	int GetImageHeight() { return M_Height; }
	//this resets the texture 
	void ResetTexture();
	//renders text
	bool RenderText(const char* text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color colour);
	//this is a destructor for the texture 
	~Texture();
};

