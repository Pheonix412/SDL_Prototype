#include "Bullet1.h"

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019

Bullet1::Bullet1()
{
	//this intalizes the texture
	M_Texture = nullptr;
	std::cout << "bullet constructor" << std::endl;
}

Bullet1::Bullet1(Texture* texture, Vector2 position)
{
	//sets the bullers postion and texture 
	M_Position = position;
	M_Texture = texture;
	//only velocity no
	//this sets the bullets velocty and also acceleration 
	M_Velocity = Vector2(0, -70);
	M_Acceleration = Vector2(0,-70);
	
}

void Bullet1::AddPlayerForce(Vector2 force)
{
	//dont think we need these 
}

void Bullet1::ReducePlayerForce(Vector2 force)
{
	//dont think we need these 
}

void Bullet1::Draw(SDL_Renderer* renderer)
{
	//this draws the texture 
	M_Texture->Draw(renderer, M_Position.X, M_Position.Y);

}

void Bullet1::Update(float deltaTime)
{
	//this part increases the velocity and also the postiion of the bullet 
	M_Velocity += M_Acceleration *deltaTime;
	M_Position += M_Velocity*deltaTime;
}


Bullet1::~Bullet1()
{
}
