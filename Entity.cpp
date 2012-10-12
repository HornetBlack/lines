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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

extern ALLEGRO_FONT* font;

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

#define SWAP(a, b) {char tmp = a; a = b; b = tmp;}

//Memory unsafe
static char* itoa(int i)
{
	char* out = new char[8];
	for (int k = 0; k < 8; k++) {
		out[k] = '\0';
	}
	while (i > 0) {
		int next = i%10;
		int move = out[0];
		for (int k = 0; out[k] < 7; k++) {
			SWAP(move, out[k+1]);
		}
		out[0] = next;
		i /= 10;
	}

	return out;
}

std::stack<Vector> Entity::convexHull(void)
{
	deque <Entity*>::iterator it;
	Vector ref;
	std::stack<Vector> vecs;
	std::stack<float> turns;
	float thisTurn;

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
		thisTurn = getPolarCoord(e->s - vecs.top());
		//cout << i << ":\n";
		sprintf(label, "%d", i++);
		al_draw_text(font, al_map_rgb(255, 255, 255), e->s.x, e->s.y, ALLEGRO_ALIGN_CENTRE, label);
		//cout << "thisTurn = " << thisTurn << endl;
		//cout << "lastTurn = " << turns.top() << endl;
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

