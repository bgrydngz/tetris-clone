#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

const int SCREEN_WIDTH  = 510;
const int SCREEN_HEIGHT = 690;

const int BOX_SIZE = 30;
const int RECT_SIZE = 29;
const int LINE_X = 360;

const int MAP_X = 12;
const int MAP_Y = 23;

const int SCORE_NEW_BLOCK = 50;
const int SCORE_COMPLETE_ROW = 500;

const std::string HIGH_SCORES_FILE = "data/highscores.dat";

enum BLOCKS
{
  O_BLOCK,
  L_BLOCK,
  J_BLOCK,
  S_BLOCK,
  Z_BLOCK,
  I_BLOCK,
  T_BLOCK,
  NUMBER_OF_BLOCKS
};

enum COLORS
{
  RED,
  BLUE,
  GREEN,
  YELLOW,
  ORANGE,
  PURPLE,
  CYAN,
  BLACK,
  WHITE,
  NUMBER_OF_COLORS
};

#endif // GLOBALS_H
