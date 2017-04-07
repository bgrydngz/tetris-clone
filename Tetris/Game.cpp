#include "Game.h"
#include <time.h>

Game::Game()
{
  mWindow = nullptr;
  mRenderer = nullptr;
  mRunning = true;
  current = 0;
  prev = 0;
  delta = 0;
  mCurrentBlock = nullptr;
  mNextBlock = nullptr;
}

Game::~Game()
{
}

void Game::init(std::string title, const int w, const int h)
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    SDL_Log("ERROR, Game::init(), SDL_Init(), %s", SDL_GetError());
    return;
  }

  mWindow = SDL_CreateWindow(title.c_str(),
   SDL_WINDOWPOS_UNDEFINED,
   SDL_WINDOWPOS_UNDEFINED,
   w,
   h,
   SDL_WINDOW_SHOWN);
  if(mWindow == nullptr)
  {
    SDL_Log("ERROR, Game::init(), SDL_CreateWindow(), %s", SDL_GetError());
    return;
  }

  mRenderer = SDL_CreateRenderer(mWindow,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(mRenderer == nullptr)
  {
    SDL_Log("ERROR, Game::init(), SDL_CreateRenderer(), %s", SDL_GetError());
    return;
  }

  SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

}

void Game::load()
{
  srand(time(0));

  mScore.clear();
  mScore.readHighScores(HIGH_SCORES_FILE);
  addBlock();
}

bool Game::running()
{
  return mRunning;
}

void Game::handleEvent()
{
  while(SDL_PollEvent(&mEv) != 0)
  {
    if(mEv.type == SDL_QUIT)
      mRunning = false;
    else if(mEv.type == SDL_KEYDOWN)
    {
      switch (mEv.key.keysym.sym)
      {
        case SDLK_ESCAPE:
          mRunning = false;
          break;

        case SDLK_LEFT:
          mCurrentBlock->moveLeft();
          break;

        case SDLK_RIGHT:
          mCurrentBlock->moveRight();
          break;

        case SDLK_DOWN:
          mCurrentBlock->speedUp();
          break;

        case SDLK_UP:
          mCurrentBlock->turn();
          break;
      } // END SWITCH
    } // END ELSEIF
  } // END LOOP
} // END FUNCTION

void Game::update()
{
  prev = current;
  current = SDL_GetTicks();
  delta = (current - prev) / 1000.0f;

  // update map and if there is win, clear things
  if(!mCurrentBlock->alive())
  {
    mMap.update(mBlocks);

    int row = mMap.checkWin();
    while(row != -1)
    {
      clearRow(row);
      mScore.addScore(SCORE_COMPLETE_ROW);

      for(auto i : mBlocks)
        i->moveDownRect(BOX_SIZE, row);


      mMap.update(mBlocks);
      row = mMap.checkWin();
    }

    addBlock();

    // if new block collides immidietly with old one, game is over
	if (checkGameOver())
	{
		mRunning = false;


		// write high scores
		mScore.addToHighScores();
		mScore.writeHighScores(HIGH_SCORES_FILE);

		// print high scores
		std::cout << std::endl;
		mScore.printHighScores();
		std::cout << std::endl << "Press enter to exit.";
		std::cin.get();
	}
  }


  mCurrentBlock->update(delta);

  //check collision
  for(auto i : mBlocks)
  {
    if(i == mCurrentBlock)
      continue;

    for(auto j : i->getRects())
    {
      if(mCurrentBlock->checkCollision((*j)))
      {
        mCurrentBlock->setAlive(false);
        mCurrentBlock->moveRect(0, -BOX_SIZE);

        break;
      }
    }
  }
}

void Game::render()
{
  SDL_RenderClear(mRenderer);

  // draw all blocks
  SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
  for(auto i : mBlocks)
    i->render(mRenderer);

  // draw next block to right of screen
  mNextBlock->render(mRenderer);

  // draw line between playground and score sign
  SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(mRenderer, LINE_X, 0, LINE_X, SCREEN_HEIGHT);

  SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
  SDL_RenderPresent(mRenderer);
}

void Game::clear()
{
  SDL_DestroyRenderer(mRenderer);
  mRenderer = nullptr;

  SDL_DestroyWindow(mWindow);
  mWindow = nullptr;

  SDL_Quit();
}

void Game::addBlock()
{
  if(mNextBlock == nullptr)
  {
    std::pair<BLOCKS, COLORS> block = randomBlock();
    mNextBlock = new Block(block.first, block.second);
  }

  mBlocks.push_back(new Block(mNextBlock->getBlock(),
    mNextBlock->getColor()));
  mCurrentBlock = mBlocks.back();

  std::pair<BLOCKS, COLORS> block = randomBlock();

  delete mNextBlock;
  mNextBlock = new Block(block.first, block.second);
  // move 240px right and 90px bottom
  mNextBlock->setPos(LINE_X + BOX_SIZE, 3 * BOX_SIZE);
  mNextBlock->setAlive(false);


  mScore.addScore(SCORE_NEW_BLOCK);
}

std::pair<BLOCKS, COLORS> Game::randomBlock()
{
  std::pair<BLOCKS, COLORS> newBlockData;
  int r = rand() % 7;

  switch (r) {
    case 0:
    newBlockData.first = O_BLOCK;
    newBlockData.second = RED;
    break;

    case 1:
    newBlockData.first = L_BLOCK;
    newBlockData.second = BLUE;
    break;

    case 2:
    newBlockData.first = J_BLOCK;
    newBlockData.second = GREEN;
    break;

    case 3:
    newBlockData.first = S_BLOCK;
    newBlockData.second = YELLOW;
    break;

    case 4:
    newBlockData.first = Z_BLOCK;
    newBlockData.second = ORANGE;
    break;

    case 5:
    newBlockData.first = I_BLOCK;
    newBlockData.second = PURPLE;
    break;

    case 6:
    newBlockData.first = T_BLOCK;
    newBlockData.second = CYAN;
    break;
  }

  return newBlockData;
}

void Game::clearRow(int row)
{
  int x = 0, y = row * BOX_SIZE;

  for(int i = 0; i < MAP_X; ++i)
  {
    x = i * BOX_SIZE;

    for(auto i : mBlocks)
      i->deleteRect(x, y);
  }
}

bool Game::checkGameOver()
{
  for(auto i : mBlocks)
  {
    if(i == mCurrentBlock)
      continue;

    for(auto j : i->getRects())
      if(mCurrentBlock->checkCollision((*j)))
        return true;
  }
  return false;
}
