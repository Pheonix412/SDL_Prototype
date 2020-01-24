#include "EnemyWave1.h"
#include <random>
//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019

EnemyWave1::EnemyWave1(){
	
}

EnemyWave1::EnemyWave1(Texture* texture, Vector2 position){
	//this initalizes the enemies texture and position 
	M_Texture = texture;
	M_Position = position;
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
}


void EnemyWave1::Update(float deltaTime){
	//this function increases the postion of the enemy when it updates 
	M_Position.X += (0 * deltaTime);
	M_Position.Y += (120 * deltaTime);
}

void EnemyWave1::MoveToPlayer(float deltaTime, Vector2 position){
	//this function moves the enemy towards the player 
	M_Position.X = position.X - M_Position.X;
	M_Position.Y = position.Y - M_Position.Y;

	int xVel = (2 * M_Position.X / M_Position.LengthOfVector());
	int yVel = (2 * M_Position.Y / M_Position.LengthOfVector());


	M_Position.X += xVel;
	M_Position.Y += yVel;
}

EnemyWave1::~EnemyWave1(){
	if (M_Texture != nullptr) {
		delete  M_Texture;
		M_Texture = nullptr;
	}
}
