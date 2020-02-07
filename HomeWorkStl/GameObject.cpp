#include "GameObject.h"
#include<iostream>

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
GameObject::GameObject()
{
	//this initalizes the texture and also the position of the game obejct 
	//std::cout << "gameobject constructor" << std::endl;
	M_Position = Vector2(0, 0);
	M_Texture = nullptr;


}


GameObject::~GameObject()
{
	
}

void GameObject::Draw(SDL_Renderer* renderer)
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::HandleUserInput(Input* input)
{
	
}