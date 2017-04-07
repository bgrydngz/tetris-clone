#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

class Score
{
public:

  void addScore(int score);
  void clear();
  void printScore();
  void printHighScores();

  void readHighScores(std::string file);
  void writeHighScores(std::string file);
  void addToHighScores();
  void createNewFile(std::string file);

  unsigned long int getScore();

private:
  unsigned long int mScore;
  std::vector<unsigned long int> mHighScores;
};

#endif //SCORE_H
