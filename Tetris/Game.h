#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "Globals.h"
#include "Block.h"
#include "Map.h"
#include "Score.h"

class Game
{
public:
  Game();
  ~Game();

  void init(std::string title, const int w, const int h);
  void load();
  bool running();
  void handleEvent();
  void update();
  void render();
  void clear();

private:
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  SDL_Event mEv;

  bool mRunning;

  float prev, current, delta;

  std::vector<Block*> mBlocks;
  Block *mCurrentBlock;

  std::pair<BLOCKS, COLORS> mNextBlockData;
  Block *mNextBlock;

  Map mMap;

  Score mScore;

  void addBlock();
  std::pair<BLOCKS, COLORS> randomBlock();
  void clearRow(int row);
  bool checkGameOver();
};

#endif // GAME_H
