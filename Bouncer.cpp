/*
 * Bouncer.cpp
 *
 *  Created on: 08/10/2012
 *      Author: tris
 */

#include "Bouncer.h"
#include "Vector.h"
using namespace std;


Bouncer::Bouncer(ALLEGRO_BITMAP *image, const Vector &s) :
		Entity(image, s, BOUNCER_SIZE, BOUNCER_SIZE), v(0, 0)
{
}

Bouncer::~Bouncer()
{
}
/*
static bool interval_cross(float min1, float max1, float min2, float max2)
{
	if (max1 > min2 && max2 > min1) {
		return true;
	} else {
		return false;
	}
}*/

void Bouncer::step(void)
{
	if (s.x < 0) {
		v.x *= -1;
		//collide(s - (Vector::unitx * width));
	} else if (s.x > SCREEN_W - width) {
		v.x *= -1;
		//collide(s + (Vector::unity * width));
	}
	if (s.y < 0) {
		v.y *= -1;
		//collide(s - (Vector::unitx * height));
	} else if (s.y > SCREEN_H - height) {
		v.y *= -1;
		//collide(s + (Vector::unity * height));
	}

	/*
	list<Entity *>::iterator it;

	for (it = ents.begin(); it != ents.end(); it++) {
		Entity *e = (*it);
		if (e == this) {continue;}

		if (interval_cross(s.x, s.x + width, e->s.x, e->s.x + e->width)
			&& interval_cross(s.y, s.y+height, e->s.y, e->s.y + e->height)) {
			this->collide(e->s);
		}
	}*/

}
/*
void Bouncer::collide(Vector es)
{
	Vector normal = s - es;
	float normalsqr = normal*normal;
	float normalvel = s * normal;
	if ((normalvel < 0)) {
		v -= normal * (2 * normalvel / normalsqr);
	}
}
*/

void Bouncer::post_step(void) {
	s += v;
}
