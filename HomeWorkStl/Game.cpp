#include "Game.h"
#include<iostream>


//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019

Game::Game()
{
	SdlWindow = nullptr;
	SdlRenderer = nullptr;
	LastUpadateTimer = SDL_GetTicks();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		IsTheGameOver = true;

		std::cout << "error initalizing " << std::endl;

	}
	else
	{
		IsTheGameOver = false;

		std::cout << "inialized " << std::endl;

	}

	

}
bool Game::start() {
	SdlRenderer = SDL_CreateRenderer(SdlWindow, 0, -1);
	if (SdlRenderer != nullptr) {
		UserInput = new Input();
		std::cout << "render created " << std::endl;

		playerBullets = new Texture();
		playerBullets->LoadImgFromFile("../assets/B1.bmp", SdlRenderer);
		


		Texture* playerSpacetexture = new Texture();
		playerSpacetexture->LoadImgFromFile("../assets/SP1.bmp", SdlRenderer);

		M_Position1.X = 380;
		M_Position1.Y = 400;
		playerSpaceS = new PlayerSpaceShip(playerSpacetexture, M_Position1);
		M_GameObjects.push_back(playerSpaceS);
	
		
		lastSpawn = SDL_GetTicks();

		LastUpadateTimer = SDL_GetTicks();

		return true;
	}
	else
	{
		std::cout << "render failed " << std::endl;
		return false;
	}
	


}
void Game::run(char* title, int width, int height, bool fullscreen) {
	int creationFlag = 0;

	if (!fullscreen)
	{
		creationFlag = SDL_WINDOW_SHOWN;
	}
	else
	{
		creationFlag = SDL_WINDOW_FULLSCREEN;
	}
	SdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, creationFlag);


	if (SdlWindow !=nullptr && start())
	{
		std::cout << "created window" << std::endl;
		while (!IsTheGameOver)
		{
			processinput();

			update();
			draw();
		}



	}
	else
	{
		std::cout << "not created window" << std::endl;
		shutdown();
		destroy();
	
	}


}

void Game::draw() {

	SDL_SetRenderDrawColor(SdlRenderer, 47, 155, 228, 255);
	SDL_RenderClear(SdlRenderer);
	
	
	
	//ani->draw(sdlRenderer, 0, 0);
	
	//m_player->Draw(sdlRenderer);

	for (int i = 0; i < M_GameObjects.size(); ++i)
	{
		M_GameObjects[i]->Draw(SdlRenderer);
	}
	for (int i = 0; i < M_EnemyObjects.size(); ++i)
	{
		M_EnemyObjects[i]->Draw(SdlRenderer);
	}
	SDL_RenderPresent(SdlRenderer);
}
void Game::destroy() {
	SDL_DestroyWindow(SdlWindow);
	SDL_DestroyRenderer(SdlRenderer);
	SDL_Quit();
}
void Game::processinput() {
	//m_player->Input();

	UserInput->UpdateInput();
	
	if (UserInput->IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		SDL_Log("ifring");

	}

	if (UserInput->IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
		SDL_Log("did not press te left buttton");

	}

	if (UserInput->IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		SDL_Log("ALT ifring");

	}
	//move this to the player class and when you press space in the player class it should spawn a bullet and be able to retrive the current position of the player as it is apart of the game object class
	/*if (UserInput->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		SDL_Log("SpacePressed");

	//M_GameObjects[0].
		int X1 = (*M_GameObjects[0]).M_Position.X;
		int Y1 = (*M_GameObjects[0]).M_Position.Y;
		M_Position1.X = (X1+10);
		M_Position1.Y = (Y1-40);
		GameObject*playerC = new Bullet1(playerBullets, M_Position1);
		M_GameObjects.push_back(playerC);
		

	}*/

	for (int i = 0; i < M_GameObjects.size(); ++i)
	{
		M_GameObjects[i]->UserInput1();
		//M_GameObjects[i]->HandleUserInput(UserInput);
		M_GameObjects[i]->HandleUserInput1(UserInput, playerBullets);
	}
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type==SDL_QUIT)
		{
			IsTheGameOver = true;
		}

	
	}

	



}
void Game::update() {
	//calculate delta time. 
	unsigned int ticks = SDL_GetTicks() - LastUpadateTimer;
	float deltaTime = ticks / 1000.0f;
	LastUpadateTimer = SDL_GetTicks();
	
	//this displays the delta time 
	//std::cout << "time" << deltaTime<< std::endl;


	unsigned int spawnTicks = SDL_GetTicks() - lastSpawn;
	float spawnTimer = spawnTicks / 1000.0f;

	//this displays the spawn timer 
	//std::cout << "Spawn Timer: " << spawnTimer<< std::endl;

	if (spawnTimer>0.5 && enemycount<10) {
		enemycount++;
		M_EnemyTexture = new Texture();
		M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipS.bmp", SdlRenderer);
		int rand_x = rand() % 700 + 10;
		int rand_y = rand() % 1 + 10;
		Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y));
		M_EnemyObjects.push_back(Enemies);
		lastSpawn = SDL_GetTicks();
	}

//	ani->Update(deltaTime);
	//m_player->Update(deltaTime);
	
	for (int i = 0; i < M_GameObjects.size(); ++i)
	{
		M_GameObjects[i]->Update(deltaTime);
	}
	for (int i = 0; i < M_EnemyObjects.size(); ++i)
	{
		M_EnemyObjects[i]->Update(deltaTime);
		//M_EnemyObjects[i]->MoveToPlayer(deltaTime, playerSpaceS->GetPosition());

	}
}
void Game::shutdown() {

}

Game::~Game()
{
}
