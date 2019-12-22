#pragma once
#include"GameObject.h"
class EnemyWave1:public GameObject
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
private:
	Vector2 M_Velocity;
	Vector2 M_Acceleration;
public:
	EnemyWave1();
	EnemyWave1(Texture * texture, Vector2 position);
	void AddPlayerForce(Vector2 force);
	void ReducePlayerForce(Vector2 force);
	void Draw(SDL_Renderer*renderer);
	void Update(float delraTime);
	void MoveToPlayer(float deltaTime, Vector2 position);
	~EnemyWave1();
};

