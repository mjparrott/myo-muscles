#include "UI.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>

UI::UI()
{
	display = NULL;
 
	if(!al_init())
	{
		cerr << "failed to initialize allegro!" << endl;
		return -1;
	}

	al_init_font_addon(); // initialize font addon
	al_init_ttf_addon();

	display = al_create_display(SCREEN_WEIDTH, SCREEN_HEIGHT);
	if(!display)
	{
		cerr << "failed to create display!" << endl;
		return -1;
	}
}

UI:~UI()
{
	al_destroy_display(display);
}

ALLEGRO_FONT *UI::createFont(std::string file, int size, int n)
{
	return al_load_ttf_font(file, size, n);
}

void UI::drawText()
{
}

void UI::draw()
{
}