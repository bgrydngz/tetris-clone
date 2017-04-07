#include "Map.h"

void Map::clear()
{
  for(int i = 0; i < MAP_X; ++i)
    for(int j = 0; j < MAP_Y; ++j)
      mMap[i][j] = 0;
}
void Map::update(std::vector<Block*> blocks)
{
  clear();

  for(auto i : blocks)
  {
    for(auto j : i->getRects())
    {
      int x = j->x / BOX_SIZE;
      int y = j->y / BOX_SIZE;

      mMap[x][y] = 1;
    }
  }
}

int Map::checkWin()
{
  for(int i = MAP_Y; i > 0; --i)
    for(int j = 0; j < MAP_X; ++j)
      {
        if(mMap[j][i] == 0)
          break;

        if(j == MAP_X-1)
          return i;
      }

  return -1;
}

void Map::print()
{
  for(int i = 0; i < MAP_Y; ++i)
  {
    for(int j = 0; j < MAP_X; ++j)
    {
      std::cout << mMap[j][i] << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << std::endl;
}
