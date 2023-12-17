#include "control.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

Control::Control(int level): level{level}, score{0}, hiScore{0} {
	if (level == 0) {
		lev = std::make_unique<Level0>();
	} else if (level == 1) {
		lev = std::make_unique<Level1>();
	} else if (level == 2) {
		lev = std::make_unique<Level2>();
	} else if (level == 3) {
		lev = std::make_unique<Level3>();
	} else if (level == 4) {
		lev = std::make_unique<Level4>();
	}
}

void Control::changeLevel(int n) {
	level += n;
	if (level < 0) level = 0;
	if (level > 4) level = 4;
	if (level == 0) {
		lev.reset(new Level0);
	} else if (level == 1) {
		lev.reset(new Level1);
	} else if (level == 2) {
		lev.reset(new Level2);
	} else if (level == 3) {
		lev.reset(new Level3);
	} else if (level == 4) {
		lev.reset(new Level4);
	}
}

void Control::changeScore(int n) {
	score += n;
	if (score > hiScore) hiScore = score;
}

void Control::reset() {
	score = 0;
	level = 0;
	lev.reset(new Level0);
}

int Control::getLevel() {
	return level;
}

int Control::getScore() {
	return score;
}

int Control::getHiScore() {
	return hiScore;
}

void Control::changeRandom(bool isRand) {
	lev->changeRandom(isRand);
}

Control::~Control() {
}
