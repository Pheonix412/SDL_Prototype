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
	if (TTF_Init() == -1) {
		std::cerr << "Failed to initialied SDL_ttf.h\n";
	}

}
//this function loads the image from the file
bool Texture::LoadImgFromFile(const char* path, SDL_Renderer* renderer) {
	//this checks ifthe texture is a null pointer
	if(M_Texture == nullptr) {
		//this creates a object of the surface  that contains the select texture 
		SDL_Surface* loadsurface = IMG_Load(path);
		//if the surfeace is not null
		if (loadsurface != nullptr)
		{
			//this sets the colour key
			//SDL_SetColorKey(loadsurface, SDL_TRUE, SDL_MapRGB(loadsurface->format, 205, 34, 0));
		//this outputs to the console that the texture loaded 
	//		std::cout << "texture loaded" << std::endl;
			//this changes the surface to a texture and saves it 
			M_Texture = SDL_CreateTextureFromSurface(renderer, loadsurface);
			//if the texture is not null
			if (M_Texture != nullptr) {

			//	std::cout << "created texture from surface" << std::endl;
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
void Texture::Draw(SDL_Renderer* renderer, int x, int y, SDL_Rect * sourceRect,bool flip) {

	//first x and y is the postion of the rectangle on the scren and also the width and height of it
	SDL_Rect destRect = { x,y,M_Width,M_Height };
	SDL_Point center;
	if (sourceRect != nullptr) {
		destRect.w = sourceRect->w;
		destRect.h = sourceRect->h;
	}
	//put the source rectangle here , the source rectangle is in charge of what is rendered from the sprite sheet

	if (!flip) {
		SDL_RenderCopy(renderer, M_Texture, sourceRect, &destRect);
	}
	else {
		center.x = destRect.w / 2;
		center.y = destRect.h / 2;
		SDL_RenderCopyEx(renderer, M_Texture, sourceRect, &destRect, 0, &center, SDL_FLIP_HORIZONTAL);
	}

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
bool Texture::RenderText(const char* text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color colour)
{
	//remmove pre-existing texture
	ResetTexture();

	//check if texture is nullptr

	if (M_Texture == nullptr) {
		//render text to surface
		SDL_Surface*  textSurface = TTF_RenderText_Blended_Wrapped(font,text,colour,500);

		if (textSurface != nullptr) {
		//	SDL_Log("Loaded text to surface-success");

			//converts the rendered tet surface to the texture
			M_Texture = SDL_CreateTextureFromSurface(renderer, textSurface);

			if (M_Texture != nullptr) {
			//	SDL_Log("Convert surface to texture- Success");
				//get width and height of rendered text
				M_Width = textSurface->w;
				M_Height = textSurface->h;
			}
			else {
				SDL_Log("Convert surface to texture- Failed %s", SDL_GetError());
				return false;
			}
			//remove the text surface from the memory
			SDL_FreeSurface(textSurface);
		}
		else {
			SDL_Log("Loaded text to surface- Failed %s", TTF_GetError());
			return false;
		}
	}
	return M_Texture != nullptr;
}

//this function destructs the texture
Texture::~Texture()
{
	//this function resets the texture
	ResetTexture();
}
