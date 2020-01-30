#include "EnemyWave1.h"
#include <random>
//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019

EnemyWave1::EnemyWave1(){
	M_Texture = nullptr;
	m_Collider = nullptr;
}

EnemyWave1::EnemyWave1(Texture* texture, Vector2 position, int colWidth, int colHeight, int speed){
	//this initalizes the enemies texture and position 
	M_Texture = texture;
	M_Position = position;
	//initalize collider
	m_Collider = new AABB(position, colWidth, colHeight);
	M_Speed = speed;
}

void EnemyWave1::AddPlayerForce(Vector2 force){
	if (M_Acceleration.X<4 || M_Acceleration.Y<4)
	{
		M_Acceleration += force;
	}
}

void EnemyWave1::ReducePlayerForce(Vector2 force){
	if (M_Acceleration.X>-10 || M_Acceleration.Y>-10)
	{
		M_Acceleration -= force;
	}
}

void EnemyWave1::Draw(SDL_Renderer* renderer){
	//this draws the enemy 
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


void EnemyWave1::Update(float deltaTime){
	//this function increases the postion of the enemy when it updates 
	M_Position.X += (0 * deltaTime);
	M_Position.Y += (M_Speed * deltaTime);

	m_Collider->Update(M_Position);
}


AABB * EnemyWave1::GetCollider()
{
	return m_Collider;
}

EnemyWave1::~EnemyWave1(){
	if (M_Texture != nullptr) {
		delete  M_Texture;
		M_Texture = nullptr;
	}
}
