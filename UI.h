#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include "DataCollector.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class UI
{
public:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_FONT *headerFont;
	ALLEGRO_FONT *infoFont;
	ALLEGRO_BITMAP *background;
	
	UI();
	~UI();
	ALLEGRO_FONT *createFont(std::string file, int size, int n);
	void drawText(ALLEGRO_FONT *font, ALLEGRO_COLOR c, float x, float y, int flags, std::string text);
	void draw(const DataCollector &collector);

private:
	void drawBackground();
};

#endif