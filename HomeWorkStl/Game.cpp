#include "Game.h"
#include <iostream>
#include <string>
#include "resource1.h"
#include <windows.h>
#include <chrono>

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
//credit to https://patrickdearteaga.com for the music
Game::Game()
{
	//please follow he guides in class for a more detailed description of this class 
	//initalizes the window and the renderer
	SdlWindow = nullptr;
	SdlRenderer = nullptr;
	isPlayerAlive = nullptr;
	Difiiculty = 0;
	Lives = 0;
	lastClear = 0;
	finalTime = 0;
    shootSpeed = -70;
    PowerUpActive = false;
    isGameFinnished = false;
	LastUpadateTimer = SDL_GetTicks();
	//checks if sdl is initalized if it isnt  then end the game , else if it has then run the game 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0|| TTF_Init() == -1|| Mix_OpenAudio(192000,MIX_DEFAULT_FORMAT,2,4096)==-1) {
		IsTheGameOver = true;

		std::cout << "error initalizing " << std::endl;
	}
	else
	{
		IsTheGameOver = false;
		std::cout << "inialized " << std::endl;
	}
	audio = nullptr;
}
bool Game::start() {
	Difiiculty = 1;
	Lives = SetIntLives(Difiiculty);
	isPlayerAlive = true;
	
	//create the renderer
	SdlRenderer = SDL_CreateRenderer(SdlWindow, 0, -1);
	//if its not null
	if (SdlRenderer != nullptr) {
		//make an object of the input  class 
		UserInput = new Input();
		//std::cout << "render created " << std::endl;
		//make an object of the texture class
		playerBullets = new Texture();
		//loads the player bullets texture
		
		playerBullets->LoadImgFromFile("../assets/B1.bmp", SdlRenderer);
		
		audio = new Audio();

		audio->PlayBGMusic("../assets/IntergalacticOdyssey.ogg");
		//intalizing text texture
		m_textTexture = new Texture();
		//initalizing the font
		m_font = TTF_OpenFont("../assets/RobotoBold.ttf", 24);

		//its then sets the postion of the bullet class 
		M_Position1.X = 710;
		M_Position1.Y = 700;
		//it then creates a new obejct of that class 
		playerSpaceS = new PlayerSpaceShip(SdlRenderer, M_Position1,75, 80);
		//then adds the objeect to the game objects list
		
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
	//checks the type of window to be shown
	if (!fullscreen)
	{
		//sets the type of window to be shown
		creationFlag = SDL_WINDOW_SHOWN;
	}
	else
	{
		//sets the type of window to be shown
		creationFlag = SDL_WINDOW_FULLSCREEN;
	}
	//creates the window
	SdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, creationFlag);

	//if there is a window and start is being run then
	if (SdlWindow !=nullptr && start())
	{

		//this part finds the name of the current window and converts to to lpcwstr 
		std::string test;
		test = title;
		int len;
		int slength = (int)test.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, test.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, test.c_str(), slength, buf, len);
		std::wstring r(buf);
		// TEST SDL is the name of the window that the program will try to find. 
		std::wstring test1;
		test1 = r;
		LPCWSTR t1;
		t1 = test1.c_str();
		//this part finds the current window and loads and sets the menu 
		HWND happ = FindWindow(NULL, t1);
		HMENU hmenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU2));
		//this sets the menu to the window.
		SetMenu(happ, hmenu);

		std::cout << "created window" << std::endl;
		//checks if the game is not over 
		while (!IsTheGameOver)
		{
			//calculate delta time. 
			unsigned int ticks = SDL_GetTicks() - LastUpadateTimer;
			float deltaTime = ticks / 1000.0f;
			LastUpadateTimer = SDL_GetTicks();

			//process the users input 
			processinput();
			//update the screen 
			update(deltaTime);
			//draw on the screen the obbejcts 
			draw();
		}
	}
	else
	{
		std::cout << "not created window" << std::endl;
		//if not then shutdown the game and destory the objects (including window and etc)
		shutdown();
		destroy();
	}
}
void Game::draw() {
	//this part sets the render colour and cleanrs the background
	SDL_SetRenderDrawColor(SdlRenderer, 47, 155, 228, 255);
	SDL_RenderClear(SdlRenderer);

	playerSpaceS->Draw(SdlRenderer);
	for (int i = 0; i < m_bullets.size(); ++i)
	{

		m_bullets[i]->Draw(SdlRenderer);
	}
	for (int i = 0; i < M_EnemyObjects.size(); ++i)
	{
		M_EnemyObjects[i]->Draw(SdlRenderer);
	}
    for (int i = 0; i < M_PowerUpObjects.size(); ++i)
    {
        M_PowerUpObjects[i]->Draw(SdlRenderer);
    }
    for (int i = 0; i < M_PowerUpObjects2.size(); ++i)
    {
        M_PowerUpObjects2[i]->Draw(SdlRenderer);
    }
	if (m_font != nullptr) {
		SDL_Color colour = { 255,255,255,255 };
		
		std::string livenum1;
		livenum1 = std::to_string((int)Lives);
		std::string Time;
		Time = std::to_string((int)GameTime);
        std::string PowerUpStatus;
        if (PowerUpActive == false) {


            //GameTime
            if (!m_textTexture->RenderText((" Lives: " + livenum1 + " Time:" + Time).c_str(), m_font, SdlRenderer, colour)) {
                //SDL_Log("Text rendered - Success");
            }
        }
        else if(PowerUpActive==true)
        {
            PowerUpStatus = " Active";
            if (!m_textTexture->RenderText((" Lives: " + livenum1 + " Time:" + Time+" PowerUp: "+PowerUpStatus).c_str(), m_font, SdlRenderer, colour)) {
                //SDL_Log("Text rendered - Success");
            }
        }

		if (isPlayerAlive == false)
		{
			M_EnemyObjects.clear();
			finalTime = GameTime;
			std::string endTime;
			endTime = std::to_string((int)finalTime);
			if (!m_textTexture->RenderText(("Game over! You lasted: "+endTime+" Seconds").c_str(), m_font, SdlRenderer, colour)) {
				//SDL_Log("Text rendered - Success");
			}

		}
        if (isGameFinnished == true)
        {
            M_EnemyObjects.clear();
            
            std::string killnumber;
            int kn = numberofkills;
            killnumber = std::to_string(kn);
            
            if (!m_textTexture->RenderText(("Congratulations you have finished the game, you have killed "+killnumber+" enemies").c_str(), m_font, SdlRenderer, colour)) {
                //SDL_Log("Text rendered - Success");
            }

        }
		m_textTexture->Draw(SdlRenderer, 10, 10);
	}
	SDL_RenderPresent(SdlRenderer);
}
void Game::destroy() {
//this destroys the window,renderer and also quits the game
	SDL_DestroyWindow(SdlWindow);
	SDL_DestroyRenderer(SdlRenderer);
	SDL_Quit();
}
void Game::PE_CollisionCheck(){

	if (playerSpaceS->GetCollider()) {
		//check that we have collided with the individual enemy collisions
		for (auto itr = M_EnemyObjects.end(); itr != M_EnemyObjects.begin();) {
			--itr;
			//if the enemes collision is within the players collsion bounds then delete the enemy
			if ((*itr) != nullptr && playerSpaceS->GetCollider()->RectCollision(*(*itr)->GetCollider())) {
				delete* itr;
				*itr = nullptr;
				itr = M_EnemyObjects.erase(itr);

			if (Lives > 0) {

				playerSpaceS->~PlayerSpaceShip();
				playerSpacetexture = new Texture();
				playerSpacetexture->LoadImgFromFile("../assets/SP1.bmp", SdlRenderer);
				M_Position1.X = 710;
				M_Position1.Y = 690;
				playerSpaceS = new PlayerSpaceShip(SdlRenderer, M_Position1,75, 80);
				Lives--;
				audio->PlaySFX("../assets/PlayerDeath.wav");
				}
				else if (Lives == 0)
				{
					playerSpaceS->~PlayerSpaceShip();
					SDL_Log("game over");

					isPlayerAlive = false;
					
				}

				SDL_Log("Enemy Deleted");
			}
		}
        for (auto itr2 = M_PowerUpObjects.end(); itr2 != M_PowerUpObjects.begin();) {
            --itr2;
            //if the enemes collision is within the players collsion bounds then delete the enemy
            if ((*itr2) != nullptr && playerSpaceS->GetCollider()->RectCollision(*(*itr2)->GetCollider())) {
                delete* itr2;
                *itr2 = nullptr;
                itr2 = M_PowerUpObjects.erase(itr2);
               
                unsigned int gameTicks = SDL_GetTicks();

                GameTime = gameTicks / 1000.0f;
                GameTime = GameTime - lastClear;
                PowerUpTime = GameTime;
                    shootSpeed = -200;
                    SDL_Log("Power Up gained");
                    PowerUpActive = true;
                    audio->PlaySFX("../assets/P1.wav");
                
               
            }
        }
        for (auto itr2 = M_PowerUpObjects2.end(); itr2 != M_PowerUpObjects2.begin();) {
            --itr2;
            //if the enemes collision is within the players collsion bounds then delete the enemy
            if ((*itr2) != nullptr && playerSpaceS->GetCollider()->RectCollision(*(*itr2)->GetCollider())) {
                delete* itr2;
                *itr2 = nullptr;
                itr2 = M_PowerUpObjects2.erase(itr2);

                unsigned int gameTicks = SDL_GetTicks();

                GameTime = gameTicks / 1000.0f;
                GameTime = GameTime - lastClear;
                PowerUpTime = GameTime;
                shootSpeed = -300;
                SDL_Log("Power Up gained");
                PowerUpActive = true;
                audio->PlaySFX("../assets/P2.wav");


            }
        }
        for (auto itr3 = M_PowerUpObjects3.end(); itr3 != M_PowerUpObjects3.begin();) {
            --itr3;
            //if the enemes collision is within the players collsion bounds then delete the enemy
            if ((*itr3) != nullptr && playerSpaceS->GetCollider()->RectCollision(*(*itr3)->GetCollider())) {
                delete* itr3;
                *itr3 = nullptr;
                itr3 = M_PowerUpObjects3.erase(itr3);

                unsigned int gameTicks = SDL_GetTicks();

                GameTime = gameTicks / 1000.0f;
                GameTime = GameTime - lastClear;
                PowerUpTime = GameTime;
                shootSpeed = -400;
                SDL_Log("Power Up gained");
                PowerUpActive = true;
                audio->PlaySFX("../assets/P3.wav");


            }
        }
        for (auto itr4 = M_PowerUpObjects4.end(); itr4 != M_PowerUpObjects4.begin();) {
            --itr4;
            //if the enemes collision is within the players collsion bounds then delete the enemy
            if ((*itr4) != nullptr && playerSpaceS->GetCollider()->RectCollision(*(*itr4)->GetCollider())) {
                delete* itr4;
                *itr4 = nullptr;
                itr4 = M_PowerUpObjects4.erase(itr4);

                unsigned int gameTicks = SDL_GetTicks();

                GameTime = gameTicks / 1000.0f;
                GameTime = GameTime - lastClear;
                PowerUpTime = GameTime;
                shootSpeed = -500;
                SDL_Log("Power Up gained");
                PowerUpActive = true;
                audio->PlaySFX("../assets/P4.wav");


            }
        }
	}
	
	try {
		//the issue is to do with the .end and .begin statements..

		for (auto itr2 = M_EnemyObjects.end(); itr2 != M_EnemyObjects.begin();) {
			
			itr2--;
		//	if ((*itr2)->GetCollider())
		//	{
				for (auto itr1 = m_bullets.end(); itr1 != m_bullets.begin();) {
					itr1--;
					//if ((*itr1)->GetCollider()) {

						//I NEED TO FIX THIS
						if ((*itr2) != nullptr && (*itr1) != nullptr && (*itr1)->GetCollider()->RectCollision(*(*itr2)->GetCollider())) {

							SDL_Log("BULLET COILDED");
							//for some reason this causes issues 
							//delete* itr;
							//*itr = nullptr;
							//itr = M_EnemyObjects.erase(itr);

							delete* itr1;
							*itr1 = nullptr;
							itr1 = m_bullets.erase(itr1);
							
							
							delete* itr2;
							*itr2 = nullptr;
							itr2 = M_EnemyObjects.erase(itr2);
							audio->PlaySFX("../assets/EnemyDeath.wav");

							//this fixes the differencible bug however i dont think it is correct
                            numberofkills = numberofkills + 1;
							break;
                            

						}
				//	}
					

				}


		//	}
		}



	}
	catch(std::string e) {
		std::string e1 = "error" + e;
		//SDL_Log(e1);
		//SDL_Log(("error " + e + "sdlerror " + SDL_Error).c_str());
	}
    try {
		//the issue is to do with the .end and .begin statements..

		for (auto itr2 = M_EnemyObjects.end(); itr2 != M_EnemyObjects.begin();) {
			
			itr2--;
		//	if ((*itr2)->GetCollider())
		//	{
				for (auto itr1 = m_bullets.end(); itr1 != m_bullets.begin();) {
					itr1--;
					//if ((*itr1)->GetCollider()) {

						//I NEED TO FIX THIS
						if ((*itr2) != nullptr && (*itr1) != nullptr && (*itr1)->GetCollider()->RectCollision(*(*itr2)->GetCollider())) {

							SDL_Log("BULLET COILDED");
							//for some reason this causes issues 
							//delete* itr;
							//*itr = nullptr;
							//itr = M_EnemyObjects.erase(itr);

							delete* itr1;
							*itr1 = nullptr;
							itr1 = m_bullets.erase(itr1);
							
							
							delete* itr2;
							*itr2 = nullptr;
							itr2 = M_EnemyObjects.erase(itr2);
							audio->PlaySFX("../assets/EnemyDeath.wav");

							//this fixes the differencible bug however i dont think it is correct

							break;

						}
				//	}
					

				}


		//	}
		}



	}
	catch(std::string e) {
		std::string e1 = "error" + e;
		//SDL_Log(e1);
		//SDL_Log(("error " + e + "sdlerror " + SDL_Error).c_str());
	}


}
void Game::ResetGame()
{
	//resets the player 
	playerSpaceS->~PlayerSpaceShip();
	playerSpacetexture = new Texture();
	playerSpacetexture->LoadImgFromFile("../assets/SP1.bmp", SdlRenderer);
	M_Position1.X = 710;
	M_Position1.Y = 690;
	playerSpaceS = new PlayerSpaceShip(SdlRenderer, M_Position1, 75, 80);
	SetLives(Difiiculty);
	//resets the enemy spawns
	lastSpawnL = 0;
	lastSpawnM = 0;
	lastSpawnS = 0;
	isPlayerAlive = true;
    PowerUpActive = false;
	//erases all enemies
	M_EnemyObjects.clear();
	//erases all bullets
	m_bullets.clear();
	//reset the game timer so that the spawns starts fresh
	lastClear = GameTime+lastClear;
    shootSpeed = -70;
    PowerUpTime = 0;
    isGameFinnished = false;
    numberofkills = 0;

}
void Game::ChangeDifficulty(int diff)
{
	//set the difficulty and also the game itself 
	Difiiculty = diff;
	ResetGame();
}
void Game::SetLives(int diff)
{
	SDL_Log("lives set");
	//sets the lives to the player 
	//easy 
	if (diff==1)
	{
		Lives = 3;
	}
	//medium
	else if( diff==2)
	{
		Lives = 2;
	}
	//hard
	else if (diff == 3)
	{
		Lives = 1;
	}
	else {
		SDL_Log("no lives set");
	}
}
int Game::SetIntLives(int diff)
{
	int liv = 0;
	if (diff == 1)
	{
		liv = 3;
	}
	//medium
	else if (diff == 2)
	{
		liv = 2;
	}
	//hard
	else if (diff == 3)
	{
		liv = 1;
	}
	else {
		SDL_Log("no lives set");
	}
	return liv;
}
void Game::processinput() {
	//this calls the update input function
	UserInput->UpdateInput(this);
	PE_CollisionCheck();
	playerSpaceS->HandleUserInput(UserInput);
	//if the user has  presses down the left mouse button
	if (UserInput->IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		SDL_Log("ifring");

	}
	//if the user has  let go of the left mouse button
	if (UserInput->IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
		//SDL_Log("did not press te left buttton");

	}
	//if the user has  presses down the right mouse button
	if (UserInput->IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		SDL_Log("ALT ifring");
	}

	if (UserInput->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		SDL_Log("SpacePressed");
		unsigned int BulletTicks = SDL_GetTicks() - LastBullet;
		float bulletTime = BulletTicks / 1000.0f;
		//only allows a bullet to spawn after 0.2 seconds
		if (bulletTime >= 0.3f) {

			int X1 = (playerSpaceS->GetPlayerX() + 37);
			int Y1 = (playerSpaceS->GetPlayerY() - 20);
			LastBullet = SDL_GetTicks();
			M_Position2.X = X1;
			M_Position2.Y = Y1;
			Bullet1*playerC = new Bullet1(SdlRenderer, M_Position2, 12, 15, shootSpeed);
			m_bullets.push_back(playerC);
			audio = new Audio();
			audio->PlaySFX("../assets/Shoot.wav");
		}
	}

	//this part checks what type of event the user has done if they have done a quit event then end the game
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type==SDL_QUIT)
		{
			IsTheGameOver = true;
		}

	}

}
void Game::update(float deltaTime) {
	
	playerSpaceS->Update(deltaTime);
	
	if (isPlayerAlive && isGameFinnished !=true) { 
	//calculate game timer
	unsigned int gameTicks = SDL_GetTicks();
	
	GameTime = gameTicks / 1000.0f;
	GameTime = GameTime - lastClear;
	//calculates the spawn timer
	unsigned int spawnTicksL = SDL_GetTicks() - lastSpawnL;
	float spawnTimerL = spawnTicksL / 1000.0f;
	 
	unsigned int spawnTicksM = SDL_GetTicks() - lastSpawnM;
	float spawnTimerM = spawnTicksM / 1000.0f;

	unsigned int spawnTicksS = SDL_GetTicks() - lastSpawnS;
	float spawnTimerS = spawnTicksS / 1000.0f;
	
		if (spawnTimerL > 0.8) {
			enemycount++;
			M_EnemyTexture = new Texture();
			M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipL.bmp", SdlRenderer);
			int rand_x = rand() % 1400 + 10;
			int rand_y = rand() % 1 + 10;
			Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y), 60, 41, 200);
			M_EnemyObjects.push_back(Enemies);
			lastSpawnL = SDL_GetTicks();
          

		}
        //1 minute
        //60
		if (spawnTimerM > 2 && GameTime > 60) {
			enemycount++;
			M_EnemyTexture = new Texture();
			M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipM.bmp", SdlRenderer);
			int rand_x = rand() % 1400 + 10;
			int rand_y = rand() % 1 + 10;
			Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y), 41, 41, 120);
			M_EnemyObjects.push_back(Enemies);
			lastSpawnM = SDL_GetTicks();

            float t1 = (PowerUpTime - GameTime)*-1;

            if (PowerUpTime == 0.0F)
            {


                M_PowerUpTexture = new Texture();
                M_PowerUpTexture->LoadImgFromFile("../assets/p2.png", SdlRenderer);
                rand_x = rand() % 1400 + 10;
                rand_y = rand() % 1 + 10;
                PowerU = new PowerUp(M_PowerUpTexture, Vector2(rand_x, rand_y), 16, 16, 200);
                M_PowerUpObjects.push_back(PowerU);
            }

            if (t1 >= 10 && PowerUpTime != 0.0F)
            {
                PowerUpActive = false;
                shootSpeed = -70;
                PowerUpTime = 0;
                // M_PowerUpObjects.clear();

            }
           

		}
        //2 miutes 
        //120
		if (spawnTimerS > 1 && GameTime > 120) {
			enemycount++;
			M_EnemyTexture = new Texture();
			M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipS.bmp", SdlRenderer);
			int rand_x = rand() % 1400 + 10;
			int rand_y = rand() % 1 + 10;
			Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y), 40, 35, 200);
			M_EnemyObjects.push_back(Enemies);
			lastSpawnS = SDL_GetTicks();

            float t1 = (PowerUpTime - GameTime)*-1;

            if (PowerUpTime == 0.0F)
            {


                M_PowerUpTexture2 = new Texture();
                M_PowerUpTexture2->LoadImgFromFile("../assets/p3.png", SdlRenderer);
                rand_x = rand() % 1400 + 10;
                rand_y = rand() % 1 + 10;
                PowerU2 = new PowerUp(M_PowerUpTexture2, Vector2(rand_x, rand_y), 16, 16, 200);
                M_PowerUpObjects2.push_back(PowerU2);
            }

            if (t1 >= 10 && PowerUpTime != 0.0F)
            {
                PowerUpActive = false;
                shootSpeed = -70;
                PowerUpTime = 0;
                // M_PowerUpObjects.clear();

            }


		}
        //3 minutes
        //180
        if (spawnTimerS > 1 && GameTime > 180) {
            enemycount++;
            M_EnemyTexture = new Texture();
            M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipXl.png", SdlRenderer);
            int rand_x = rand() % 1400 + 10;
            int rand_y = rand() % 1 + 10;
            Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y), 32, 32, 200);
            M_EnemyObjects.push_back(Enemies);
            lastSpawnS = SDL_GetTicks();

            float t1 = (PowerUpTime - GameTime)*-1;

            if (PowerUpTime == 0.0F)
            {


                M_PowerUpTexture3 = new Texture();
                M_PowerUpTexture3->LoadImgFromFile("../assets/p4.png", SdlRenderer);
                rand_x = rand() % 1400 + 10;
                rand_y = rand() % 1 + 10;
                PowerU3 = new PowerUp(M_PowerUpTexture3, Vector2(rand_x, rand_y), 16, 16, 200);
                M_PowerUpObjects3.push_back(PowerU3);
            }

            if (t1 >= 10 && PowerUpTime != 0.0F)
            {
                PowerUpActive = false;
                shootSpeed = -70;
                PowerUpTime = 0;
                // M_PowerUpObjects.clear();

            }


        }
        //4minues
        //240
        if (spawnTimerS > 1 && GameTime > 240) {
            enemycount++;
            M_EnemyTexture = new Texture();
            M_EnemyTexture->LoadImgFromFile("../assets/EnemyShipxs.png", SdlRenderer);
            int rand_x = rand() % 1400 + 10;
            int rand_y = rand() % 1 + 10;
            Enemies = new EnemyWave1(M_EnemyTexture, Vector2(rand_x, rand_y),16, 16, 200);
            M_EnemyObjects.push_back(Enemies);
            lastSpawnS = SDL_GetTicks();

            float t1 = (PowerUpTime - GameTime)*-1;

            if (PowerUpTime == 0.0F)
            {


                M_PowerUpTexture4 = new Texture();
                M_PowerUpTexture4->LoadImgFromFile("../assets/p5.png", SdlRenderer);
                rand_x = rand() % 1400 + 10;
                rand_y = rand() % 1 + 10;
                PowerU4 = new PowerUp(M_PowerUpTexture4, Vector2(rand_x, rand_y), 16, 16, 200);
                M_PowerUpObjects4.push_back(PowerU4);
            }

            if (t1 >= 10 && PowerUpTime != 0.0F)
            {
                PowerUpActive = false;
                shootSpeed = -70;
                PowerUpTime = 0;
                // M_PowerUpObjects.clear();

            }


        }
        //5 minues end game..
        //300
        if (spawnTimerS > 1 && GameTime > 300) {
            playerSpaceS->~PlayerSpaceShip();
            isGameFinnished = true;
            audio->PlaySFX("../assets/win.wav");

        }
	
	}
	//this goes through all of the enimies and game obejcts and updates them 
	
	for (int i = 0; i < M_EnemyObjects.size(); ++i)
	{
		M_EnemyObjects[i]->Update(deltaTime);
	}
	for (int i = 0; i < m_bullets.size(); ++i)
	{
		m_bullets[i]->Update(deltaTime);
	}
    for (int i = 0; i < M_PowerUpObjects.size(); ++i)
    {
        M_PowerUpObjects[i]->Update(deltaTime);
    }
    for (int i = 0; i < M_PowerUpObjects2.size(); ++i)
    {
        M_PowerUpObjects2[i]->Update(deltaTime);
    }
}
void Game::shutdown() {
	Mix_Quit();
}
Game::~Game()
{
}
void Game::SetGameState(bool status)
{
	IsTheGameOver = status;
}
