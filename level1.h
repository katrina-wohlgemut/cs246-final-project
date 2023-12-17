#ifndef LEVEL1_H
#define LEVEL1_H
#include "level.h"

class Level1: public Level {
public:
	Level1();
	std::shared_ptr<Block> generateBlock(std::ifstream &f) override;
	void changeRandom(bool isRand) override {}
	void setTimer(int n) override {}
	int getTimer() override {return 0;}
	~Level1();
};

#endif
