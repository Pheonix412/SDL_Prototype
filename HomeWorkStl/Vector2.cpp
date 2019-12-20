#include "Vector2.h"





Vector2::Vector2()
{
}

Vector2::Vector2(int x, int y)
{
	this->X = x;
	this->Y = y;
}
//there was issues when i tried to overload these operators
Vector2 Vector2::operator+(const Vector2 &anotherV) {
	return Vector2(this->X + anotherV.X, this->Y + anotherV.Y);
}
Vector2 Vector2::operator+=(const Vector2 &anotherV) {
	this->X += anotherV.X;
	this->Y += anotherV.Y;
	return *this;
}
Vector2 Vector2::operator-(const Vector2 &anotherV) {
	return Vector2(this->X - anotherV.X, this->Y - anotherV.Y);
}
Vector2 Vector2::operator-=(const Vector2 &anotherV) {
	this->X -= anotherV.X;
	this->Y -= anotherV.Y;
	return *this;
}
Vector2 Vector2::operator*(const float & scalar)
{
	return Vector2(this->X * scalar, this->Y * scalar);
}

Vector2 Vector2::operator*=(const float & scalar)
{
	this->X *= scalar;
	this->Y *= scalar;
	return *this;
}

void Vector2::NormalizeVector()
{
	float mag = sqrtf(X*X + Y*Y);
	this->X /= mag;
	this->Y /= mag;
}

Vector2 Vector2::NormalizedVector()
{
	Vector2 result = Vector2(NULL,NULL);
	float mag = sqrtf(X*X + Y*Y);
	result.X = this->X / mag;
	result.Y = this->Y / mag;
	return result;
}



float Vector2::LengthOfVector()
{
	return sqrt(X*X + Y*Y);

}
Vector2::~Vector2()
{
}
