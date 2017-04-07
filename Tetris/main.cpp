/*
* Tetris SDL2/C++
*
* Programmer: Bugra Aydingoz
*
* Date: 30.01.2017
*/

#include "Game.h"
#include "Globals.h"

int main(int argc, char *argv[])
{
  Game game;

  game.init("Tetris - Bugra Aydingoz", SCREEN_WIDTH, SCREEN_HEIGHT);
  game.load();

  while(game.running())
  {
    game.handleEvent();
    game.update();
    game.render();
  }

  game.clear();
  return 0;
}
