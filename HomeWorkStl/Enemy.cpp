#include "Enemy.h"

Enemy::Enemy() {
	M_Texture = nullptr;
	std::cout << "Enemy constructor" << std::endl;
}

Enemy::Enemy(Texture * texture, Vector2 position) {
	M_Texture = texture;
	M_Position = position;
}

void Enemy::Update(float deltaTime) {
	M_Position.X += (0 *deltaTime);
	M_Position.Y += (5 * deltaTime);
	M_Position.Y += M_Position.Y*deltaTime;
}

void Enemy::Draw(SDL_Renderer * renderer) {
	M_Texture->Draw(renderer, M_Position.X, M_Position.Y);
}

void Enemy::HandleUserInput(Input* input) {

}

void Enemy::MoveToPlayer(float deltaTime, Vector2 position) {
	M_Position.X = position.X - M_Position.X;
	M_Position.Y = position.Y - M_Position.Y;

	int xVel = (2 * M_Position.X / M_Position.LengthOfVector());
	int yVel = (2 * M_Position.Y / M_Position.LengthOfVector());


	M_Position.X += xVel;
	M_Position.Y += yVel;
	
}

Enemy::~Enemy() {
	std::cout << "Enemy destructor" << std::endl;
}
