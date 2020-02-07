#pragma once

#include"Texture.h"
#include"Vector2.h"
#include"Input.h"
#include "AABB.h"
#include "Animation.h"
class GameObject
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
public:
	//this is the constructor and the destructor for the game object
	GameObject();
	~GameObject();
	//this is the draw function for the game object
	virtual void Draw(SDL_Renderer* renderer);
	//this is the update function for the game object
	virtual void Update(float deltaTime);
	//these are functions that handles the user input 
	virtual void HandleUserInput(Input* input);


protected:
	//this holds the position and the texture for the game object 
	Vector2 M_Position;
	Texture* M_Texture;
};

