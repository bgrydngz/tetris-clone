#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include "Block.h"
#include "Globals.h"

class Map
{
public:
  void clear();
  void update(std::vector<Block*> blocks);
  int checkWin();
  void print();

private:
  int mMap[MAP_X][MAP_Y];
};

#endif // MAP_H
