#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class UI
{
public:
	ALLEGRO_DISPLAY *display;
	
	UI();
	~UI();
	ALLEGRO_FONT *createFont(std::string file, int size, int n);
	void drawText();
	void draw();
};

#endif