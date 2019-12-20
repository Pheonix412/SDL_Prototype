#pragma once
#include "GameObject.h"
class Enemy :public GameObject
{
public:
	Enemy();
	Enemy(Texture* texture, Vector2 position);
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void HandleUserInput(Input* input) override;
	void MoveToPlayer(float deltaTime, Vector2 position);
	~Enemy();
};

