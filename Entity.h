/*
 * Entitiy.h
 *
 *  Created on: 08/10/2012
 *      Author: tris
 */

#ifndef ENTITIY_H_
#define ENTITIY_H_

#include "main.h"
#include <deque>
#include <stack>
#include "Vector.h"

class stack;

class Entity {
	public:

	static std::deque<Entity*> ents;

	ALLEGRO_BITMAP   *sprite;

	Vector s;
	float width, height;

	Entity(ALLEGRO_BITMAP *image, Vector s, float width, float height);
	virtual ~Entity();

	virtual void step(void);
	virtual void post_step(void);

	static std::stack<Vector> convexHull(void);
};

/*
class stack {
private:
	int cap;
public:
	int size;
	Vector * array;
	stack(int max);
	~stack(void);
	void push(Vector v);
	Vector peek(void);
	Vector peek2(void);
	Vector pop (void);
	bool empty();
	};*/

#endif /* ENTITIY_H_ */
