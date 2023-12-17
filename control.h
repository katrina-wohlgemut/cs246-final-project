#ifndef CONTROL_H
#define CONTROL_H
#include "level.h"
#include <memory>

class Control {
	int level;
	int score;
	int hiScore;
public:
	std::unique_ptr<Level> lev;
	Control(int level = 0);
	void changeScore(int n);
	// Sets level and score to 0 and level to level0, does not change hiScore
	void reset();
	int getLevel();
	int getScore();
	int getHiScore();
	void changeLevel(int n);
	void changeRandom(bool isRand);
	~Control();
};

#endif
