#include "Texture.h"
#include<iostream>


Texture::Texture()
{
	M_Texture = nullptr;
	M_Width = 0;
	M_Height = 0;

}



bool Texture::LoadImgFromFile(const char* path, SDL_Renderer* renderer) {

	if(M_Texture == nullptr) {
		SDL_Surface* loadsurface =SDL_LoadBMP(path);
		
		if (loadsurface != nullptr)
		{
			SDL_SetColorKey(loadsurface, SDL_TRUE, SDL_MapRGB(loadsurface->format, 205, 34, 0));
			std::cout << "texture loaded" << std::endl;
			M_Texture = SDL_CreateTextureFromSurface(renderer, loadsurface);



			if (M_Texture != nullptr) {

				std::cout << "created texture from surface" << std::endl;

				M_Width = loadsurface->w;
				M_Height = loadsurface->h;



			}
			else {
				std::cout << "cannot change texture to surface " << SDL_GetError()<<std::endl;
			}

			SDL_FreeSurface(loadsurface);
		
		
		
		
		}
}
	else
	{
		std::cout << "texture existing" << std::endl;
		return false;
	}
	return M_Texture != nullptr;
}

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





void Texture::ResetTexture() {

	if (M_Texture !=nullptr) {
		SDL_DestroyTexture(M_Texture);
		M_Texture = nullptr;
		M_Width = 0;
		M_Height = 0;

	}


	//im up to page 6 out of 7

 }



Texture::~Texture()
{
	ResetTexture();

}
