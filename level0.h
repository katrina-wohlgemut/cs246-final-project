#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Level0: public Level {
public:
	Level0();
	std::shared_ptr<Block> generateBlock(std::ifstream &f) override;
	void changeRandom(bool isRand) override {}
	void setTimer(int n) override {}
	int getTimer() override {return 0;}
	~Level0();
};

#endif
