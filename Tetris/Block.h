#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "Globals.h"

class Block
{
public:
  Block(BLOCKS block, COLORS color);

  void moveLeft();
  void moveRight();
  void turn();
  void speedUp();
  bool alive();

  void update(float &delta);
  void render(SDL_Renderer* renderer);

  void setAlive(bool alive);
  void setPos(int x, int y);
  void moveRect(int x, int y);
  void moveDownRect(int y, int row);

  bool checkCollision(SDL_Rect &a);
  void deleteRect(int x, int y);

  COLORS getColor();
  BLOCKS getBlock();

  std::vector<SDL_Rect*> getRects() const;

private:
  std::vector<SDL_Rect*> mRects;
  COLORS mColor;
  BLOCKS mBlock;
  bool mAlive; // if true, player still controls it

  void setColor(SDL_Renderer *renderer, COLORS color);
  void createBlock(BLOCKS block);

  int getTopY();
  int getBottomY();
  int getLeftX();
  int getRightX();

  float timer, stepTime;
};

#endif // BLOCK_H
