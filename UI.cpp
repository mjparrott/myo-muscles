#include "UI.h"
#include "Main.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

using namespace std;

UI::UI()
{
	display = NULL;
 
	if(!al_init())
	{
		cerr << "failed to initialize allegro!" << endl;
	}

	al_init_font_addon(); // initialize font addon
	al_init_ttf_addon();

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if(!display)
	{
		cerr << "failed to create display!" << endl;
	}
	
	headerFont = createFont("font.ttf", 20, 0);
}

UI::~UI()
{
	al_destroy_display(display);
}

ALLEGRO_FONT *UI::createFont(std::string file, int size, int n)
{
	return al_load_ttf_font(file.c_str(), size, n);
}

void UI::drawText(ALLEGRO_FONT *font, ALLEGRO_COLOR c, float x, float y, int flags, string text)
{
	al_draw_text(font, c, x, y, flags, text.c_str());
}

void UI::draw()
{
	drawText(headerFont, al_map_rgb(255, 0, 0), 10.0, 10.0, 0, TITLE);
	al_flip_display();
}