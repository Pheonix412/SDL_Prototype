#pragma once

#include"Texture.h"
#include"Vector2.h"
#include"Input.h"
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
	//this is the user input function for the game object 
	virtual void UserInput1();
	//these are functions that handles the user input 
	virtual void HandleUserInput(Input* input);
	virtual void HandleUserInput1(Input* input, Texture* playerBullets);
	//this holds the postion of the game object 
	Vector2 GetPosition();
protected:
	//this holds the position and the texture for the game object 
	Vector2 M_Position;
	Texture* M_Texture;
};

