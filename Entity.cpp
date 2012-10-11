/*
 * Entitiy.cpp
 *
 *  Created on: 08/10/2012
 *      Author: tris
 */

#include "Entity.h"
#include <algorithm>
#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;

deque<Entity*> Entity::ents;

Entity::Entity(ALLEGRO_BITMAP *image, Vector s, float width, float height) :
		sprite(image), s(s), width(width), height(height)
{
}

Entity::~Entity()
{
	printf("Entity destructor invoked\n");
}

void Entity::step(void)
{
}
void Entity::post_step(void)
{
}

// Convex hull stuff

static bool compByY(Entity *a, Entity *b)
{
	return (a->s.y < b->s.y);
}

static float getPolarCoord(Vector a)
{
	if (a.x == 0 && a.y == 0) {
		return -INFINITY;
	}

	float out = atan2(a.y, a.x);
	if (out < 0) {
		out = 2 * M_PI - out;
	}
	return out;
}

class CompPolar {
public:
	Vector ref;
	CompPolar(Vector ref): ref(ref) {}
	bool operator()(Entity *a, Entity *b) {
		float ap = getPolarCoord(a->s - ref);
		float bp = getPolarCoord(b->s - ref);
		return ap < bp;
	}
};

/*
stack::stack(int max): cap(max+1), size(0) {array = new Vector[cap];}
stack::~stack(void) {}//{delete array;}
void stack::push(Vector v) {size++; array[size] = v;}
Vector stack::peek(void) {return array[size];}
Vector stack::peek2(void){return array[size-1];}
Vector stack::pop (void) {return array[size--];}
bool stack::empty(void) {return (size <= 0);}
*/

static float ccw (Vector p1, Vector p2, Vector p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

std::stack<Vector> Entity::convexHull(void)
{
	deque <Entity*>::iterator it;
	Vector ref;
	std::stack<Vector> s;

	sort(ents.begin(), ents.end(), compByY);
	ref = ents.front()->s;
	CompPolar origin(ref);
	sort(ents.begin() + 1, ents.end(), origin);

	s->push(reference);
	it = ents.begin() + 1;
	s->push((*it)->s);
	it++;
	while (it != ents.end() - 1) {
		if (*it == ents[0]) {
			break;
		}
		Vector v = (*it)->s;
		while (ccw(v, s->peek(), s->peek2()) > 0) {
			cout << "Removed " << s->peek().x << s->peek().y << endl;
			s->pop();
		}

		cout << "Added: " << v.x << " "<< v.y << endl;

		s->push(v);
		it++;
	}

	return s;
}

