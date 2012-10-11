/*
 * Bouncer.h
 *
 *  Created on: 08/10/2012
 *      Author: tris
 */

#ifndef BOUNCER_H_
#define BOUNCER_H_

#include "main.h"
#include "Entity.h"

#define BOUNCER_SIZE 4

class Bouncer : public Entity
{
public:

	Vector v;

	Bouncer(ALLEGRO_BITMAP *image, const Vector &v);
	virtual ~Bouncer();

	void step(void);
	void post_step(void);
private:
	void collide (Vector es);
};

#endif /* BOUNCER_H_ */
