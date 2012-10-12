/*
 * Entitiy.cpp
 *
 *  Created on: 08/10/2012
 *      Author: tris
 */

#define _USE_MATH_DEFINES

#include "Entity.h"
#include <limits>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <sstream>

#include "what.h"

extern ALLEGRO_FONT* font;

using namespace std;

deque<Entity*> Entity::ents;
Vector Entity::ref;

Entity::Entity(ALLEGRO_BITMAP *image, Vector s, float width, float height) :sprite(image), s(s), width(width), height(height)
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
	if (s.y < ref.y) {
		ref = s;
	}
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
		out = 2 * M_PI + out;
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

static float ccw (Vector p1, Vector p2, Vector p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

std::stack<Vector> Entity::convexHull(void)
{
	deque <Entity*>::iterator it;
	std::stack<Vector> vecs;
	std::stack<float> turns;
	float thisTurn;
	stringstream ss;
	char label[8];

	sort(ents.begin(), ents.end(), compByY);
	ref = ents.front()->s;
	CompPolar origin(ref);
	sort(ents.begin(), ents.end(), origin);

	vecs.push(ref);
	turns.push(-INFINITY);

	it = ents.begin();
	int i = 0;
	while (it != ents.end()) {
		Entity *e = *it;
		//cout << i << ":\n";
		ss << i++;
		ss >> label;
		al_draw_text(font, al_map_rgb(255, 255, 255), 
					 e->s.x, e->s.y, ALLEGRO_ALIGN_CENTRE, label);
		//cout << "thisTurn = " << thisTurn << endl;
		//cout << "lastTurn = " << turns.top() << endl;

		thisTurn = getPolarCoord(e->s - vecs.top());
		while (thisTurn < turns.top()) {
			vecs.pop();
			turns.pop();
			thisTurn = getPolarCoord(e->s - vecs.top());
			//cout << "thisTurn = " << thisTurn << " *\n";
		}
		
		vecs.push(e->s);
		turns.push(thisTurn);
		it++;
	}
	vecs.push(ref);
	return vecs;
}

