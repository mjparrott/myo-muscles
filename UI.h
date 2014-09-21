#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include "DataCollector.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;

class UI
{
public:
	UI();
	~UI();
	ALLEGRO_FONT *createFont(std::string file, int size, int n);
	void drawText(ALLEGRO_FONT *font, ALLEGRO_COLOR c, float x, float y, int flags, std::string text);
	void clear();
	void draw(const DataCollector &collector);
	void drawExercise(int exerciseNum, bool started);

private:
	ALLEGRO_DISPLAY *display;
	ALLEGRO_FONT *headerFont;
	ALLEGRO_FONT *infoFont;
	ALLEGRO_BITMAP *background;
	ALLEGRO_BITMAP *warmupPic;
	ALLEGRO_BITMAP *benchPressPic;
	ALLEGRO_BITMAP *frontRaisePic;
	
	void drawBackground();
	void printState(bool started, bool calibrating);
};

#endif