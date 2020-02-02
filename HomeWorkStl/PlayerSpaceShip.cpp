#include "PlayerSpaceShip.h"

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019

PlayerSpaceShip::PlayerSpaceShip()
{
	//on construction of the player it sets their texture to a nullptr
	M_Texture = nullptr;
	std::cout << "playerconstructor" << std::endl;
	LastUpadateTimer = SDL_GetTicks();
	M_Velocity = Vector2(0, 0);
	M_Acceleration = Vector2(0, 0);
	m_MaxVelocity = 0.0f;
	playerdecleration = 0.0f;

	m_playerDir = 0;


	maxVelocity = 0.0f;
	m_Collider = new AABB();
	
	m_isTouchingGround = false;
}

PlayerSpaceShip::PlayerSpaceShip(SDL_Renderer* renderer, Vector2 position, int colWidth, int colHeight)
{
	//this part initalizes the players position,texture,velocity and also acceleration.
	M_Position = position;
	//m_colPOS = M_Position;
	//m_colPOS.X = m_colPOS.X + 20;
	M_Velocity = Vector2(0, 0);
	M_Acceleration = Vector2(0, 0);
	maxVelocity = 1000.0f;
	playerdecleration = 2000.0f;
	//maxVelocity = 500.0f;
	m_colWidth = colWidth;
	m_colHeight = colHeight;
	// setting the inital player texture
	M_Texture = new Texture();
	M_Texture->LoadImgFromFile("../assets/SP1Idle.png", renderer);
	m_animation = new Animation(M_Texture, 6, 0.25f);
	//setup collider
	m_isTouchingGround = false;
	m_Collider = new AABB(M_Position, m_colWidth, m_colHeight);
	m_playerDir = 0;
	m_sdlRenderer = renderer;
}

void PlayerSpaceShip::AnimationLogic(Input * input){
	// Pressed d key
	if (input->wasKeyPressed(SDLK_d)) {
		RunAnimation(true);
		// clear the d key state
		input->SetKeyboardStateFalse(SDLK_d);
	}

	if (input->wasKeyPressed(SDLK_a)) {
		RunAnimation();
		// clear the a key state
		input->SetKeyboardStateFalse(SDLK_a);
	}

	if (input->wasKeyReleased(SDLK_d) && m_playerDir == 2) {
		IdleAnimation();
		// clear the d key state
		input->SetKeyboardStateFalse(SDLK_d);
	}

	if (input->wasKeyReleased(SDLK_a) && m_playerDir == 1) {
		IdleAnimation();
		// clear the a key state
		input->SetKeyboardStateFalse(SDLK_a);
	}

	if (input->wasKeyReleased(SDLK_d) && m_playerDir == 0) {
		IdleAnimation();
		input->SetKeyboardStateFalse(SDLK_a);
		input->SetKeyboardStateFalse(SDLK_d);
	}

	if (input->wasKeyReleased(SDLK_a) && m_playerDir == 0) {
		IdleAnimation();
		input->SetKeyboardStateFalse(SDLK_d);
		input->SetKeyboardStateFalse(SDLK_a);
	}
}

void PlayerSpaceShip::IdleAnimation(){
	// Reset the texture
	M_Texture->ResetTexture();
	// Load the animation
	M_Texture->LoadImgFromFile("../assets/SP1Idle.png", m_sdlRenderer);
	// play the animation
	m_animation = new Animation(M_Texture, 6, 0.25f);
}

void PlayerSpaceShip::RunAnimation(bool flip){
	// Reset the texture
	M_Texture->ResetTexture();
	// Load the animation
	M_Texture->LoadImgFromFile("../assets/SP1Move.png", m_sdlRenderer);
	// play the animation
	m_animation = new Animation(M_Texture, 6, 0.125f, flip);
}

void PlayerSpaceShip::AddPlayerForce(Vector2 force)
{
	//this part increases the players acceleration in a direction by adding the players force to their acceleration 
		M_Acceleration += force;
}

void PlayerSpaceShip::ReducePlayerForce(Vector2 force)
{
		M_Acceleration -= force;
}

float PlayerSpaceShip::GetPlayerY()
{
	return M_Position.Y;
}

float PlayerSpaceShip::GetPlayerX()
{
	return M_Position.X;
}

AABB * PlayerSpaceShip::GetCollider()
{
	return m_Collider;
}

Vector2 PlayerSpaceShip::GetPlayerPos()
{
	return M_Position;
}

void PlayerSpaceShip::ToggleGorund(bool toggle){
	//toggle isTouchingGround
	m_isTouchingGround = toggle;

}

void PlayerSpaceShip::Draw(SDL_Renderer* renderer)
{
	//this part points to the draw function in the texture class and draws te player on the screen 
	m_animation->Draw(renderer, M_Position.X, M_Position.Y);

	//draw a box to visualise the collider
	SDL_Rect rect = {
		m_Collider->GetPosition().X,
		m_Collider->GetPosition().Y,
		m_Collider->GetWidth(),
		m_Collider->GetHeight()
	};

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
	SDL_RenderDrawRect(renderer, &rect);

	
}

void PlayerSpaceShip::Update(float deltaTime)
{
	//this part updates the players posution and also their velocity
	
	//M_Acceleration = M_Acceleration + Vector2(M_Velocity *-0.5f);
		M_Velocity += M_Acceleration * deltaTime;
		float length = M_Velocity.magnitude();
		if (length >= maxVelocity) {
			M_Velocity.NormalizeVector();
			M_Velocity = M_Velocity*maxVelocity;
		}

		M_Position += M_Velocity * deltaTime;
		if (!m_isTouchingGround) {
			M_Position.Y += 500.0f*deltaTime;
		}
		M_Acceleration = Vector2(0, 0);
		m_Collider->Update(M_Position);
		
		m_animation->Update(deltaTime);
		//SDL_Log("velocty %f, %f", M_Velocity.X, M_Velocity.Y);
		
		//M_Acceleration = Vector2(0, 0);
	
}

void PlayerSpaceShip::UserInput1()
{
}


void PlayerSpaceShip::HandleUserInput1(Input* input)
{
	//this part handles the users input when they press a key down the keyboard, when they press a button down it will add to the players force in the coresponding direction

	if (input->IsKeyDown(SDL_SCANCODE_A))
	{
		m_playerDir = 2;
		AddPlayerForce(Vector2(-1,0) * 2000.0f);
	}

	if (input->IsKeyUp(SDL_SCANCODE_A))
	{
		if (M_Velocity.X < 0) {
			ReducePlayerForce(Vector2(-2, 0) *playerdecleration);
		}
	}

	if (input->IsKeyDown(SDL_SCANCODE_D))
	{
		m_playerDir = 1;
		AddPlayerForce(Vector2(1, 0) * 2000.0f);
	}
	if (input->IsKeyUp(SDL_SCANCODE_D))
	{
		if (M_Velocity.X > 0) {
			ReducePlayerForce(Vector2(1, 0) * playerdecleration);
		}
	}
	// if we are not moving the player in a direction
	if (input->IsKeyUp(SDL_SCANCODE_A) && input->IsKeyUp(SDL_SCANCODE_D)) {
		// set player direction to idle
		m_playerDir = 0;
	}
	AnimationLogic(input);

}


PlayerSpaceShip::~PlayerSpaceShip()
{
	M_Texture->ResetTexture();

	std::cout << "player destructor" << std::endl;

}
