#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <allegro5/allegro.h>

class Mouse
{
public:
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE *event_queue;
	
	Mouse();
	~Mouse();
	void getMouse(ALLEGRO_EVENT *ev);
};

#endif