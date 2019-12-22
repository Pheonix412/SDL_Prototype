#pragma once

#include"Texture.h"
#include"Vector2.h"
#include"Input.h"
class GameObject
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
public:
	GameObject();
	~GameObject();
	//put getters and and setters
	virtual void Draw(SDL_Renderer*renderer);
	virtual void Update(float delraTime);
	virtual void UserInput1();
	virtual void HandleUserInput(Input*input);
	virtual void HandleUserInput1(Input*input, Texture* playerBullets);
	Vector2 GetPosition();
protected:
	Vector2 M_Position;
	Texture* M_Texture;
};

