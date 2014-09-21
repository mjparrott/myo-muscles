#include "UI.h"
#include "Main.h"
#include "DataCollector.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <sstream>

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
	al_init_image_addon();

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if(!display)
	{
		cerr << "failed to create display!" << endl;
	}
	
	headerFont = createFont(MAIN_FONT, 50, 0);
	infoFont = createFont(MAIN_FONT, 20, 0);
	background = al_load_bitmap(MAIN_BACKGROUND.c_str());
	warmupPic = al_load_bitmap(WARMUP_PIC.c_str());
	benchPressPic = al_load_bitmap(BENCH_PRESS_PIC.c_str());
	frontRaisePic = al_load_bitmap(FRONT_RAISE_PIC.c_str());
}

UI::~UI()
{
	al_destroy_bitmap(background);
	al_destroy_bitmap(warmupPic);
	al_destroy_bitmap(benchPressPic);
	al_destroy_bitmap(frontRaisePic);
	al_destroy_font(headerFont);
	al_destroy_font(infoFont);
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

void UI::clear()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void UI::draw(const DataCollector &collector)
{
	clear();
	drawBackground();
	drawExercise(collector.currentExercise, collector.workoutStarted);
	
	drawText(headerFont, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, 10.0, ALLEGRO_ALIGN_CENTRE, TITLE);
	drawText(infoFont, al_map_rgb(255, 0, 0), 40.0, 60.0, 0, exercises[collector.currentExercise]);
	stringstream ss;
	ss << "Sets: " << collector.sets + 1;
	drawText(infoFont, al_map_rgb(255, 0, 0), 50.0, 100.0, 0, ss.str());
	ss.str(""); ss.clear();
	ss << "Reps: " << collector.halfReps / 2;
	drawText(infoFont, al_map_rgb(255, 0, 0), 50.0, 130.0, 0, ss.str());
	if(collector.showError > 0) {
		drawText(infoFont, al_map_rgb(255, 0, 0), 450.0, 120.0, 0, "ERROR");
	}
	al_flip_display();
}

void UI::drawBackground()
{
	al_draw_bitmap(background, 0, 0, 0);
	al_draw_bitmap(background, 350, 0, 0);
	al_draw_bitmap(background, 0, 300, 0);
	al_draw_bitmap(background, 350, 300, 0);
	al_draw_bitmap(background, 700, 0, 0);
	al_draw_bitmap(background, 700, 300, 0);
	al_draw_bitmap(background, 0, 600, 0);
	al_draw_bitmap(background, 350, 600, 0);
	al_draw_bitmap(background, 700, 600, 0);
}

void UI::drawExercise(int exerciseNum, bool started)
{
	if(!started) return;
	if(exerciseNum == 0)
	{
		al_draw_bitmap(warmupPic, 100, 200, ALLEGRO_ALIGN_CENTRE);
	}
	else if(exerciseNum == 1)
	{
		al_draw_bitmap(benchPressPic, 90, 190, ALLEGRO_ALIGN_CENTRE);
	}
	else if(exerciseNum == 2)
	{
		al_draw_bitmap(frontRaisePic, 90, 190, ALLEGRO_ALIGN_CENTRE);
	}
}