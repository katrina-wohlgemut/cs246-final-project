#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"

class Level2: public Level {
public:
	Level2();
	std::shared_ptr<Block> generateBlock(std::ifstream &f) override;
	void changeRandom(bool isRand) override {}
	void setTimer(int n) override {}
	int getTimer() override {return 0;}
	~Level2();
};

#endif
