#include "GameObject.h"
#include<iostream>


GameObject::GameObject()
{
	std::cout << "gameobject constructor" << std::endl;
	M_Position = Vector2(0, 0);
	M_Texture = nullptr;


}


GameObject::~GameObject()
{
	
}

void GameObject::Draw(SDL_Renderer * renderer)
{
}

void GameObject::Update(float delraTime)
{
}

void GameObject::UserInput1()
{
}

void GameObject::HandleUserInput(Input * input)
{
	
}

void GameObject::HandleUserInput1(Input*input, Texture* playerBullets)
{
}

Vector2 GameObject::GetPosition()
{
	return Vector2(M_Position.X, M_Position.Y);
}
