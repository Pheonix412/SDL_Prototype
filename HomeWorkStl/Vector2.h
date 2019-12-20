#pragma once
#include<math.h>

class Vector2
{
public:
	int X;
	int Y;
public:
	Vector2();
	Vector2(int x,int y);


	Vector2 Vector2::operator+(const Vector2 &anotherV);
	Vector2 Vector2::operator+=(const Vector2 &anotherV);
	 Vector2 operator-(const Vector2 &anotherV);
	 Vector2 operator-=(const Vector2 &anotherV);
	Vector2 operator*(const float &scalar);
	Vector2 operator*=(const float &scalar);



	void NormalizeVector();
	Vector2 NormalizedVector();
	float LengthOfVector();
	~Vector2();
};

