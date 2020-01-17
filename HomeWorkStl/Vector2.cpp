#include "Vector2.h"
//by Rhys Thomas Baker 7772 and By Jayme Schmid 6290 2019
Vector2::Vector2()
{
}

Vector2::Vector2(int x, int y)
{
	//this initalized the x and y variables for vector 2 
	this->X = x;
	this->Y = y;
}
//this is the addition operator ,pretty much the other variables 
Vector2 Vector2::operator+(const Vector2& anotherV) {
	//this  returns vectors 2 once it has added both the current and the objects x and y vairiables together
	return Vector2(this->X + anotherV.X, this->Y + anotherV.Y);
}
//this is the addition and equals operator
Vector2 Vector2::operator+=(const Vector2& anotherV) {
	//this adds the current x operator to the current objects x operator
	this->X += anotherV.X;
	//this adds the current y operator to the current objects y operator
	this->Y += anotherV.Y;
	//this returns a pointer to the current objects 
	return *this;
}
//its pretty much the same thing for the rest of the operators just with their coresponding operators instead of +
Vector2 Vector2::operator-(const Vector2& anotherV) {
	return Vector2(this->X - anotherV.X, this->Y - anotherV.Y);
}
Vector2 Vector2::operator-=(const Vector2& anotherV) {
	this->X -= anotherV.X;
	this->Y -= anotherV.Y;
	return *this;
}
Vector2 Vector2::operator*(const float& scalar)
{
	return Vector2(this->X * scalar, this->Y * scalar);
}

Vector2 Vector2::operator*=(const float& scalar)
{
	this->X *= scalar;
	this->Y *= scalar;
	return *this;
}
//this is a function that normalizes the vector 
void Vector2::NormalizeVector()
{
	//works out the magnitude of both the x and y values 
	float mag = sqrtf(X*X + Y*Y);
	//this sets the normalized vectors for both the x and y values
	this->X /= mag;
	this->Y /= mag;
}
//this function normalizes the vector
Vector2 Vector2::NormalizedVector()
{
	//sets the result to null
	Vector2 result = Vector2(NULL,NULL);
	//this works out the magnitude 
	float mag = sqrtf(X*X + Y*Y);
	//this works out the normalized x and y values
	result.X = this->X / mag;
	result.Y = this->Y / mag;
	return result;
}
//this function works out the magnitude however it is incorrect. 
float Vector2::magnitude()
{
	return sqrt(X*X + Y*Y);
}
//this fucntion works out the length of vector
float Vector2::LengthOfVector()
{
	//this returns  the legnth of the vector it does this my multiplying both x and y values and then it adds them to themselves and square roots it.
	return sqrt(X*X + Y*Y);
}
//this  destruct the current vector 
Vector2::~Vector2()
{
}
