#pragma once
#include"Vector2.h"
#include <SDL.h>
#include<iostream>

enum MouseInputs
{
	MOUSE_BUTTON_LEFT = 0,
	MOUSE_BUTTON_RIGHT = 1,
	MOUSE_BUTTON_MIDDLE = 2,
	MOUSE_BUTTON_4 = 3,
	MOUSE_BUTTON_5 = 4,
	MOUSE_BUTTON_6 = 5,
	MOUSE_BUTTON_7 = 6,

};


class Input
{
private:
	Vector2 M_MousePosition;
	bool M_MouseButtonStates[7];
	const Uint8* M_keyboardState;
	void OnMouseButtonDown(SDL_Event &e);
	void OnMouseButtonUp(SDL_Event &e);
	void OnMouseButtonMove(SDL_Event &e);
	
public:
	Input();
	
	void UpdateInput();

	bool IsMouseButtonDown(MouseInputs button);
	bool IsMouseButtonUp(MouseInputs button);

	bool IsKeyDown(SDL_Scancode key);
	bool IsKeyUp(SDL_Scancode key);

	Vector2 GetMousePos();




	~Input();
};

