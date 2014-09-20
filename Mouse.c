#include "Mouse.h"
#include <iostream>
#include <allegro5/allegro.h>

using namespace std;

Mouse::Mouse()
{
	if(!al_install_mouse())
	{
		cerr << "Failed to initialize mouse!" << endl;
	}
	event_queue = al_create_event_queue();
	if(!event_queue)
	{
		cerr << "Failed to create event_queue!\n" << endl;
	}
	al_register_event_source(event_queue, al_get_mouse_event_source());
}

Mouse::~Mouse()
{
	al_destroy_event_queue(event_queue);
}

void getMouse(ALLEGRO_EVENT *ev)
{
	al_wait_for_event(event_queue, ev);
	
}