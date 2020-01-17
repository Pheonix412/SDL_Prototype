#pragma once
#include"GameObject.h"
class EnemyWave1:public GameObject
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
private:
	//this is the varoables for velocity and accleration for the first wave of enemies 
	Vector2 M_Velocity;
	Vector2 M_Acceleration;
public:
	//this is the first wave of enemies constructor and overloaded constructor
	EnemyWave1();
	EnemyWave1(Texture* texture, Vector2 position);
	//this function adds force to the enemy 
	void AddPlayerForce(Vector2 force);
	//this function removes force from the enemy
	void ReducePlayerForce(Vector2 force);
	//this funcation draws the enemy
	void Draw(SDL_Renderer* renderer);
	//this function updates the enemy
	void Update(float deltaTime);
	//this function moves the player towards the player
	void MoveToPlayer(float deltaTime, Vector2 position);
	//this function destructs the enemy 
	~EnemyWave1();
};

