/*
 * main.h
 *
 *  Created on: 08/10/2012
 *      Author: tris
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#define LOG_FILE  stderr
#define LOG(_str) fprintf(LOG_FILE, "%s\n", _str)

#define COLOR_BLACK  al_map_rgb(0,0,0)
#define COLOR_PURPLE al_map_rgb(255,0,255)

const float FPS = 30;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

extern ALLEGRO_FONT *font;

#endif /* MAIN_H_ */
