#pragma once
#include"GameObject.h"
class Bullet1 : public GameObject
{
private:
	Vector2 M_Velocity;
	Vector2 M_Acceleration;
public:
	Bullet1();
	Bullet1(Texture * texture, Vector2 position);
	void AddPlayerForce(Vector2 force);
	void ReducePlayerForce(Vector2 force);
	void Draw(SDL_Renderer*renderer);
	void Update(float delraTime);
	~Bullet1();
};

