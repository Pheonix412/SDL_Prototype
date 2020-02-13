#include "Bullet1.h"

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019

Bullet1::Bullet1()
{
	//this intalizes the texture
	M_Texture = nullptr;
	std::cout << "bullet constructor" << std::endl;
	m_Collider = nullptr;
	M_Position = Vector2(0,0);
}

Bullet1::Bullet1(SDL_Renderer *renderer, Vector2 position , int colWidth, int colHeight, int speed)
{
	//sets the bullers postion and texture 
	M_Position = position;
	M_Texture = new Texture();
	M_Texture->LoadImgFromFile("../assets/B2.bmp", renderer);
	//only velocity no
	//this sets the bullets velocty and also acceleration 
	m_Collider = new AABB(position, colWidth, colHeight);
	M_Velocity = Vector2(0, -70);
	M_Acceleration = Vector2(0,speed);
	
}

void Bullet1::Draw(SDL_Renderer* renderer)
{
	//this draws the texture 
	M_Texture->Draw(renderer, M_Position.X, M_Position.Y);
	SDL_Rect rect = {
		m_Collider->GetPosition().X,
		m_Collider->GetPosition().Y,
		m_Collider->GetWidth(),
		m_Collider->GetHeight()
	};

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
	SDL_RenderDrawRect(renderer, &rect);

}

void Bullet1::Update(float deltaTime)
{
	//this part increases the velocity and also the postiion of the bullet 
	M_Velocity += M_Acceleration *deltaTime;
	M_Position += M_Velocity*deltaTime;
	m_Collider->Update(M_Position);
}

AABB * Bullet1::GetCollider()
{
	return m_Collider;
}


Bullet1::~Bullet1()
{
	if (M_Texture != nullptr) {
		delete  M_Texture;
		M_Texture = nullptr;
	}
}
