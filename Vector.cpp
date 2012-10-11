/*
 * Vector.cpp
 *
 *  Created on: 09/10/2012
 *      Author: tris
 */

#include "Vector.h"

Vector Vector::unitx(1, 0);
Vector Vector::unity(0, 1);
Vector Vector::zero(0, 0);

Vector::Vector(void):x(0), y(0){}

Vector::Vector(float x, float y)
	:x(x), y(y)
{}

Vector::~Vector()
{}

Vector Vector::operator-() {
	return Vector(-x, -y);
}

Vector Vector::operator+(const Vector &v) {
	return Vector(x + v.x, y + v.y);
}
Vector Vector::operator-(const Vector &v) {
	return Vector(x - v.x, y - v.y);
}

//Dot product
float operator*(const Vector &v1, const Vector &v2) {
	return (v1.x * v2.x + v1.y * v2.y);
}

/*
float Vector::operator*(const Vector &v) {
	return (x * v.x + y * v.y);
}*/

//Scale
Vector Vector::operator*(float f) {
	return Vector(f * x, f * y);
}
Vector operator*(float f, const Vector &v) {
	return Vector(f * v.x, f * v.y);
}

//Scale with 1/f
Vector Vector::operator/(float f) {
	return Vector(x/f, y/f);
}

bool Vector::operator==(const Vector &v) {
	return (x == v.x) && (y == v.y);
}

void Vector::operator+=(const Vector &v) {
	x += v.x;
	y += v.y;
}

void Vector::operator-=(const Vector &v) {
	x -= v.x;
	y += v.y;
}

//Scale
void Vector::operator*=(float f) {
	x *= f;
	y *= f;
}

