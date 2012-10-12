
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <stack>
#include <sstream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "main.h"
#include "Bouncer.h"
#include "Entity.h"

using namespace std;

ALLEGRO_FONT *font = NULL;

#define BOUNCER_SPEED 4

// Starts allegro, mouse, keyboard, display, event_queue and FPS timer.
static int init(
		ALLEGRO_DISPLAY **display,
		ALLEGRO_EVENT_QUEUE **event_queue,
		ALLEGRO_TIMER **timer);

// Cleans up allegro.
static void cleanup(
		ALLEGRO_DISPLAY *display,
		ALLEGRO_EVENT_QUEUE *event_queue,
		ALLEGRO_TIMER *timer);

// Runs the main loop.
static void run_loop(
		ALLEGRO_DISPLAY *display,
		ALLEGRO_EVENT_QUEUE *event_queue,
		ALLEGRO_TIMER *timer);

// Creates a purple square
static ALLEGRO_BITMAP *new_bmp(int size, ALLEGRO_DISPLAY *display);

int main(int argc, char *argv[])
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	srand(0x389754);

	if (!init(&display, &event_queue, &timer)) {
		return EXIT_FAILURE;
	}

	run_loop(display, event_queue, timer);

	cleanup(display, event_queue, timer);
	return EXIT_SUCCESS;
}

static int init(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue,
		ALLEGRO_TIMER **timer)
{
	if (display == NULL || timer == NULL || event_queue == NULL) {
		LOG("Invalid arguments for init.");
		return 0;
	}

	// Start allegro
	if (!al_init()) {
		LOG("Failed to start allegro.");
		return 0;
	}

	// Start primitives add-on
	if (!al_init_primitives_addon()) {
		LOG("Failed to start primatives addon");
	}

	// Start mouse
	if (!al_install_mouse()) {
		LOG("Failed to start mouse.");
		return 0;
	}

	// Start keyboard
	if (!al_install_keyboard()) {
		LOG("Failed to start keyboard.");
		return 0;
	}

	// Create timer
	*timer = al_create_timer(1.0 / FPS);
	if (*timer == NULL) {
		LOG("Failed to create main timer.");
		return 0;
	}

	// Create display
	*display = al_create_display(SCREEN_W, SCREEN_H);
	if (*display == NULL) {
		LOG("Failed to create display.");
		al_destroy_timer(*timer);
		return 0;
	}

	// Create event queue
	*event_queue = al_create_event_queue();
	if (*event_queue == NULL) {
		LOG("Failed to create event queue.");
		al_destroy_timer(*timer);
		al_destroy_display(*display);
		return 0;
	}

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
	// Load font
	font = al_load_ttf_font("pirulen.ttf",14,0 );
    if (font == NULL){
		fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
		return 0;
	}

	// Register display events
	al_register_event_source(*event_queue,
			al_get_display_event_source(*display));
	// Register FPS timer
	al_register_event_source(*event_queue, al_get_timer_event_source(*timer));
	// Register mouse events
	al_register_event_source(*event_queue, al_get_mouse_event_source());
	// Register keyboard events
	al_register_event_source(*event_queue, al_get_keyboard_event_source());

	return 1;
}

static void cleanup(ALLEGRO_DISPLAY *display, 
					ALLEGRO_EVENT_QUEUE *event_queue,
					ALLEGRO_TIMER *timer)
{
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
}

static void run_loop(ALLEGRO_DISPLAY *display, 
					 ALLEGRO_EVENT_QUEUE *event_queue,
					 ALLEGRO_TIMER *timer)
{
	bool redraw = true;
	bool doexit = false;
	bool keys[ALLEGRO_KEY_MAX];

	for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
		keys[i] = 0;
	}

	ALLEGRO_BITMAP *bouncer_img = new_bmp(BOUNCER_SIZE, display);

	deque <Entity*>::iterator it;

	Vector prev;
	Vector curr;

	for (int i = 0; i < 10; i++) {
		Vector s;
		s.x = rand() % (SCREEN_W - BOUNCER_SIZE);
		s.y = rand() % (SCREEN_H - BOUNCER_SIZE);
		Bouncer *b = new Bouncer(bouncer_img, s);
        //Random speed between -4 and 4
		b->v.x = (1/2 - (float)rand()/(float)RAND_MAX) * BOUNCER_SPEED; 
		b->v.y = (1/2 - (float)rand()/(float)RAND_MAX) * BOUNCER_SPEED;
		Entity::ents.push_back(b);
	}

	time_t last_frame = time(NULL);
	time_t this_frame;
	int frame_count = 0;
	char fps_string[16];
	fps_string[0] = '1';
	fps_string[1] = '\0';

	al_start_timer(timer);
	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		
		// Every tick
		if (ev.type == ALLEGRO_EVENT_TIMER) 
		{
			redraw = true;
			for (it = Entity::ents.begin(); 
				 it != Entity::ents.end(); it++) 
			{
				(*it)->step();
				(*it)->post_step();
			}
		}

		// Close button
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break; // Prevents another frame being rendered.
		}

		// Mouse button release
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

		}

		// Mouse button release
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

		}

		// Key press
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			keys[ev.keyboard.keycode] = true;
			
			if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_PLUS) {
				Vector s;
				s.x = rand() % (SCREEN_W - BOUNCER_SIZE);
				s.y = rand() % (SCREEN_H - BOUNCER_SIZE);
				Bouncer *b = new Bouncer(bouncer_img, s);
				b->v.x = (1/2 - (float)rand()/(float)RAND_MAX) * BOUNCER_SPEED; //Random speed between -4 and 4
				b->v.y = (1/2 - (float)rand()/(float)RAND_MAX) * BOUNCER_SPEED;
				Entity::ents.push_back(b);
			}
			
			else if (ev.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS) {
				Entity *e = Entity::ents.back();
				Entity::ents.pop_back();
				delete e;
			}
			
		} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			keys[ev.keyboard.keycode] = false;
		}

		// Render frame
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(COLOR_BLACK);

			for (it = Entity::ents.begin(); 
				 it != Entity::ents.end(); 
				 it++) {
				Entity *e = *it;
				al_draw_bitmap(e->sprite, e->s.x - e->width/2, 
							   e->s.y - e->height/2, 0);
			}

			std::stack<Vector> convex(Entity::convexHull());
			
			prev = convex.top();
			convex.pop();
			curr = convex.top();
			convex.pop();
			do {
				al_draw_line(prev.x, prev.y, 
							 curr.x, curr.y, COLOR_PURPLE, 0);
				prev = curr;
				curr = convex.top();
				convex.pop();
			} while (!convex.empty());
		
			this_frame = time(NULL);
			
			if (difftime(this_frame, last_frame) >= 1.0) {
				sprintf(fps_string, "%d" , frame_count);
				frame_count = 0;
				last_frame = this_frame;
			}
			frame_count++;
			
			al_draw_text(font, al_map_rgb(255, 255, 0), 0, 0,
						 ALLEGRO_ALIGN_LEFT, fps_string);

			al_flip_display();
		}
	}
	for (it = Entity::ents.begin(); it != Entity::ents.end(); it++) {
		delete *it;
	}
	al_destroy_bitmap(bouncer_img);
	printf("\n");
}

static ALLEGRO_BITMAP *new_bmp(int size, ALLEGRO_DISPLAY *display)
{
	ALLEGRO_BITMAP *bouncer = al_create_bitmap(size, size);
	if (bouncer == NULL) {
		LOG("Failed to create bitmap!");
		abort();
	}

	al_set_target_bitmap(bouncer);
	al_clear_to_color(COLOR_PURPLE);
	al_set_target_bitmap(al_get_backbuffer(display));

	return bouncer;
}
