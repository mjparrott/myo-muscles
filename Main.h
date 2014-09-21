#ifndef __MAIN_H__
#define __MAIN_H__

#include <allegro5/allegro.h>
#include <string>

const std::string TITLE = "Myo Muscles";
const std::string exercises[] = {"warmup","bench","shoulder"};

// Resources
const std::string MAIN_FONT = "resources/fonts/font.ttf";
const std::string MAIN_BACKGROUND = "resources/images/background.bmp";
const std::string WARMUP_PIC = "resources/images/warmup.bmp";
const std::string BENCH_PRESS_PIC = "resources/images/benchpress.bmp";
const std::string FRONT_RAISE_PIC = "resources/images/frontraise.bmp";
const int EXERCISE_COUNT = 3;

#endif