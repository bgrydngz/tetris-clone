#include "Block.h"

Block::Block(BLOCKS block, COLORS color)
{
  mColor = color;
  mBlock = block;

  createBlock(mBlock);

  mAlive = true;
  timer = 0;
  stepTime = 0.3f;
}

void Block::update(float &delta)
{
  timer += delta;
  if(timer >= stepTime && getBottomY() < SCREEN_HEIGHT && mAlive)
  {
    timer = 0;
    for(auto i : mRects)
      i->y += BOX_SIZE;

    if(getBottomY() >= SCREEN_HEIGHT)
    {
      moveRect(0, -BOX_SIZE);
      mAlive = false;
    }
  }
}

void Block::render(SDL_Renderer* renderer)
{
  for(auto i : mRects)
  {
    setColor(renderer, mColor);
    SDL_RenderFillRect(renderer, i);
    setColor(renderer, WHITE);
    SDL_RenderDrawRect(renderer, i);
  }
}

void Block::setColor(SDL_Renderer *renderer, COLORS color)
{
  switch(color)
  {
  case RED:
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    break;

  case BLUE:
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    break;

  case GREEN:
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    break;

  case YELLOW:
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    break;

  case ORANGE:
    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    break;

  case PURPLE:
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    break;

  case CYAN:
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    break;

  case BLACK:
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    break;

  case WHITE:
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    break;
  }
}

void Block::createBlock(BLOCKS block)
{
  switch(block)
  {
  case L_BLOCK:
    mRects.push_back(new SDL_Rect{120, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 30, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 60, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{150, 60, RECT_SIZE, RECT_SIZE});
    break;

  case J_BLOCK:
    mRects.push_back(new SDL_Rect{150, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{150, 30, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{150, 60, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 60, RECT_SIZE, RECT_SIZE});
    break;

  case S_BLOCK:
    mRects.push_back(new SDL_Rect{150, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 30, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{90, 30, RECT_SIZE, RECT_SIZE});
    break;

  case Z_BLOCK:
    mRects.push_back(new SDL_Rect{90, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 30, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{150, 30, RECT_SIZE, RECT_SIZE});
    break;

  case I_BLOCK:
    mRects.push_back(new SDL_Rect{120, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 30, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 60, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 90, RECT_SIZE, RECT_SIZE});
    break;

  case O_BLOCK:
    mRects.push_back(new SDL_Rect{120, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{150, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 30, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{150, 30, RECT_SIZE, RECT_SIZE});
    break;

  case T_BLOCK:
    mRects.push_back(new SDL_Rect{90, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{150, 0, RECT_SIZE, RECT_SIZE});
    mRects.push_back(new SDL_Rect{120, 30, RECT_SIZE, RECT_SIZE});
    break;
  }
}

void Block::moveLeft()
{
  if(getLeftX() > 0)
    for(auto i : mRects)
      i->x -= BOX_SIZE;
}

void Block::moveRight()
{
  if(getRightX() < LINE_X)
    moveRect(BOX_SIZE, 0);
  if(getRightX() > LINE_X)
    moveRect(-BOX_SIZE, 0);
}

void Block::turn()
{
  if(mBlock == O_BLOCK)
    return;

  else
  {
    int x0 = getLeftX();
    int y0 = getTopY();

    for(auto i : mRects)
    {
      i->x -= x0;
      i->y -= y0;

      std::swap(i->x, i->y);

      i->y *= -1;

      i->x += x0;
      i->y += y0;
    }

    moveRect(0, BOX_SIZE); // there was bug, rects were keep moving up
  }
}

void Block::speedUp()
{
  stepTime = 0.05f;
}

int Block::getTopY()
{
  int y = SCREEN_HEIGHT;
  for(auto i : mRects)
    if(i->y < y)
      y = i->y;

  return y;
}

int Block::getBottomY()
{
  int y = 0;
  for(auto i : mRects)
    if(i->y > y)
      y = i->y;

  return y + RECT_SIZE;
}

int Block::getLeftX()
{
  int x = SCREEN_WIDTH;
  for(auto i : mRects)
    if(i->x < x)
      x = i->x;

  return x;
}

int Block::getRightX()
{
  int x = 0;
  for(auto i : mRects)
    if(i->x > x)
      x = i->x;

  return x + RECT_SIZE;
}

bool Block::alive()
{
  return mAlive;
}

void Block::setAlive(bool alive)
{
  mAlive = alive;
}

void Block::setPos(int x, int y)
{
  int x0 = getLeftX();
  int y0 = getTopY();

  int dx = x - x0;
  int dy = y - y0;

  moveRect(dx, dy);
}

void Block::moveRect(int x, int y)
{
  for(auto i : mRects)
  {
    i->x += x;
    i->y += y;
  }
}

// move all rects above row
void Block::moveDownRect(int y, int row)
{
  for(auto i : mRects)
  {
    if(i->y < row * BOX_SIZE)
      i->y += y;
  }
}

COLORS Block::getColor()
{
  return mColor;
}

BLOCKS Block::getBlock()
{
  return mBlock;
}

std::vector<SDL_Rect*> Block::getRects() const
{
  return mRects;
}

bool Block::checkCollision(SDL_Rect &a)
{
  for(auto i : mRects)
    if(i->x >= a.x &&
    i->x <= a.x + a.w &&
    i->y >= a.y &&
    i->y <= a.y + a.h)
    {
      return true;
    }

  return false;
}

void Block::deleteRect(int x, int y)
{
	//for(auto i = mRects.begin(); i < mRects.end(); ++i) // ERROR: vector iterator not incrementable
	//{
	//  if((*i)->x == x && (*i)->y == y)
	//    // mRects.erase(i);

	//}

	std::vector <SDL_Rect*>::iterator it = mRects.begin();
	while (it != mRects.end())
	{
		SDL_Rect *temp = (*it);

		if ((*it)->x == x && (*it)->y == y)
		{
			//it = mRects.erase(it);
			delete[] temp;
			it = mRects.erase(it);
		}

		if (it == mRects.end() || mRects.size() == 0)
		{
			break;
		}

		++it;
	}
}