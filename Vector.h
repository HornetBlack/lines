/*
 * Vector.h
 *
 *  Created on: 09/10/2012
 *      Author: tris
 */

#ifndef VECTOR_H_
#define VECTOR_H_

class Vector
{
public:
	float x, y;
	Vector(void);
	Vector(float x, float y);
	virtual ~Vector();

	Vector operator-();
	Vector operator+(const Vector &v);
	Vector operator-(const Vector &v);
	friend float operator*(const Vector &v1, const Vector &v2);//Dot product

	Vector operator*(float f);  //Scalar product
	Vector operator/(float f);  //Scaler product with 1/f
	friend Vector operator*(float f, const Vector &v);

	bool operator==(const Vector &v);

	void operator+=(const Vector &v);
	void operator-=(const Vector &v);
	void operator*=(float f);

	static Vector unitx;
	static Vector unity;
	static Vector zero;
};

#endif /* VECTOR_H_ */
