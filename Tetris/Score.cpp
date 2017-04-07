#include "Score.h"

void Score::addScore(int score)
{
  mScore += score;

  //TEMP
  printScore();
}

void Score::clear()
{
  mScore = 0;
  mHighScores.clear();
}

void Score::printScore()
{
  // system("clear");
  std::cout << "Score: " << mScore << std::endl;
}

void Score::printHighScores()
{
  std::cout << "High scores: " << std::endl;
  for(auto i : mHighScores)
    std::cout << i << std::endl;
}

void Score::readHighScores(std::string file)
{
  mHighScores.clear();
  std::ifstream inf(file.c_str());
  if(!inf)
  {
    std::cout << file.c_str() <<
    " could not be opened for reading. New file has been created.\n";
    createNewFile(file);
    inf.open(file.c_str());
  }

  while(true)
    {
      unsigned long int score;

      inf >> score;
      if(inf.eof())
        break;

      mHighScores.push_back(score);
    }

  inf.close();
  // mHighScores.push_back(0);

  //std::cout << "First: \n";
  //printHighScores();
}

void Score::writeHighScores(std::string file)
{
  std::ofstream outf(file.c_str());
  if(!outf)
    std::cout << file.c_str() << " could not be opened for writing.\n";

  else
    for(auto i : mHighScores)
      if(i != 0)
        outf << i << std::endl;

  outf.close();

  //std::cout << "Last: \n";
  //printHighScores();
}

void Score::addToHighScores()
{
  mHighScores.push_back(mScore);
  std::sort(mHighScores.rbegin(), mHighScores.rend());

  if(mHighScores.size() > 10)
    mHighScores.pop_back();
}

void Score::createNewFile(std::string file)
{
  std::ofstream os(file.c_str());

  if(os)
    for(int i = 9; i >= 1; --i)
      os << i * 100 << std::endl;

  os.close();
}

unsigned long int Score::getScore()
{
  return mScore;
}
