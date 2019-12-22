#include "Texture.h"
#include<iostream>
//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
//this constructs the texture class
Texture::Texture()
{
	//intalizes all of the variables 
	M_Texture = nullptr;
	M_Width = 0;
	M_Height = 0;

}
//this function loads the image from the file
bool Texture::LoadImgFromFile(const char* path, SDL_Renderer* renderer) {
	//this checks ifthe texture is a null pointer
	if(M_Texture == nullptr) {
		//this creates a object of the surface  that contains the select texture 
		SDL_Surface* loadsurface =SDL_LoadBMP(path);
		//if the surfeace is not null
		if (loadsurface != nullptr)
		{
			//this sets the colour key
			SDL_SetColorKey(loadsurface, SDL_TRUE, SDL_MapRGB(loadsurface->format, 205, 34, 0));
		//this outputs to the console that the texture loaded 
			std::cout << "texture loaded" << std::endl;
			//this changes the surface to a texture and saves it 
			M_Texture = SDL_CreateTextureFromSurface(renderer, loadsurface);
			//if the texture is not null
			if (M_Texture != nullptr) {

				std::cout << "created texture from surface" << std::endl;
				//this sets the width and height of the texture 
				M_Width = loadsurface->w;
				M_Height = loadsurface->h;

			}
			else {
				//this outputs this if there is no texture 
				std::cout << "cannot change texture to surface " << SDL_GetError()<<std::endl;
			}
			//this frees the surface 
			SDL_FreeSurface(loadsurface);
	
		}
}
	else
	{
		//if the texture still exists then output this 
		std::cout << "texture existing" << std::endl;
		return false;
	}
	//this returns if the texture is not null
	return M_Texture != nullptr;
}
//this function draws the texture 
void Texture::Draw(SDL_Renderer* renderer, int x, int y, SDL_Rect * sourceRect) {

	//first x and y is the postion of the rectangle on the scren and also the width and height of it
	SDL_Rect destRect = { x,y,M_Width,M_Height };
	if (sourceRect != nullptr) {
		destRect.w = sourceRect->w;
		destRect.h = sourceRect -> h;
	}
	//put the source rectangle here , the source rectangle is in charge of what is rendered from the sprite sheet
	SDL_RenderCopyEx(renderer, M_Texture, sourceRect, &destRect,0.0,NULL,SDL_FLIP_HORIZONTAL);


}
//this function resets the texture 
void Texture::ResetTexture() {
	//if the texture is not a null pointer 
	if (M_Texture !=nullptr) {
		//if it is a nullpter then destroy the texture 
		SDL_DestroyTexture(M_Texture);
		//set it to a nullpointer 
		M_Texture = nullptr;
		//make its width and height 0
		M_Width = 0;
		M_Height = 0;
	}
 }
//this function destructs the texture
Texture::~Texture()
{
	//this function resets the texture
	ResetTexture();
}
