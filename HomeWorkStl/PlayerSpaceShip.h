#pragma once
#include <vector>
#include "GameObject.h"
#include"Bullet1.h"
class PlayerSpaceShip : public GameObject
{
private:
	Vector2 M_Velocity;
	Vector2 M_Acceleration;
	std::vector <Bullet1*> m_bullets;
	Vector2 M_Position1;
	Vector2 M_Position2;
	//std::vector<GameObject*>M_GameObjects;
public:
	PlayerSpaceShip();
	Bullet1 * m_bullet;

	PlayerSpaceShip(Texture * texture, Vector2 position);
	void AddPlayerForce(Vector2 force);
	void ReducePlayerForce(Vector2 force);
	void Draw(SDL_Renderer*renderer);
	void Update(float delraTime);
	void UserInput1();
	//void UserInput1(Texture* playerBullets);
	void HandleUserInput(Input*input);
	void HandleUserInput1(Input*input, Texture* playerBullets);
	~PlayerSpaceShip();
};

