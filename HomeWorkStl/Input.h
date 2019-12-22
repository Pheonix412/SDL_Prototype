#pragma once
#include"Vector2.h"
#include <SDL.h>
#include<iostream>

//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
//this is a enum that holds all of the types of the mouse inputs
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
	//this vector 2 holds the position of the mouse 
	Vector2 M_MousePosition;
	//this holds the button states 
	bool M_MouseButtonStates[7];
	//this holds the keyboard states 
	const Uint8* M_keyboardState;
	//these are functons to do with the mouse 
	void OnMouseButtonDown(SDL_Event &e);
	void OnMouseButtonUp(SDL_Event &e);
	void OnMouseButtonMove(SDL_Event &e);
public:
	//this holds te input constructor
	Input();
	//this holds teh update input function 
	void UpdateInput();
	//these are function that return an bollean value todo with mouses or keyboard 
	bool IsMouseButtonDown(MouseInputs button);
	bool IsMouseButtonUp(MouseInputs button);
	bool IsKeyDown(SDL_Scancode key);
	bool IsKeyUp(SDL_Scancode key);
	//is is a vector 2 that holds the mouse position
	Vector2 GetMousePos();
	//this is the destructor for the input class 
	~Input();
};

