#include "EnemyWave1.h"



EnemyWave1::EnemyWave1(){
}

EnemyWave1::EnemyWave1(Texture * texture, Vector2 position){
	M_Texture = texture;
	M_Position = position;
}

void EnemyWave1::AddPlayerForce(Vector2 force)
{
}

void EnemyWave1::ReducePlayerForce(Vector2 force)
{
}

void EnemyWave1::Draw(SDL_Renderer * renderer){
	M_Texture->Draw(renderer, M_Position.X, M_Position.Y);
}


void EnemyWave1::Update(float delraTime){
	M_Position.X += (0 * delraTime);
	M_Position.Y += (5 * delraTime);
	M_Position.Y += M_Position.Y*delraTime;
}

void EnemyWave1::MoveToPlayer(float deltaTime, Vector2 position){
	M_Position.X = position.X - M_Position.X;
	M_Position.Y = position.Y - M_Position.Y;

	int xVel = (2 * M_Position.X / M_Position.LengthOfVector());
	int yVel = (2 * M_Position.Y / M_Position.LengthOfVector());


	M_Position.X += xVel;
	M_Position.Y += yVel;
}

EnemyWave1::~EnemyWave1()
{
}
