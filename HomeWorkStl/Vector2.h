#pragma once
#include<math.h>

class Vector2
{
	//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
public:
	//this holds te x and y values 
	int X;
	int Y;
public:
	//this is a constructor for the vector 2 classs 
	Vector2();
	//this is a overloadd constructor for the vector 2 class 
	Vector2(int x,int y);
	// this overloads operators todo with the vector 2 class 
	Vector2 Vector2::operator+(const Vector2& anotherV);
	Vector2 Vector2::operator+=(const Vector2& anotherV);
	 Vector2 operator-(const Vector2& anotherV);
	 Vector2 operator-=(const Vector2& anotherV);
	Vector2 operator*(const float& scalar);
	Vector2 operator*=(const float& scalar);
	//this functions normalize the object
	void NormalizeVector();
	Vector2 NormalizedVector();
	//this function gets the magnitude of a object 
	float magnitude();
	//this function gets the length of a vector 
	float LengthOfVector();
	//this is a destructor for the vector 2 class 
	~Vector2();
};

