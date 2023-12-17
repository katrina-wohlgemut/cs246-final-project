#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"

class Level4: public Level {
	bool random;
	int timer;
public:
	Level4();
	std::shared_ptr<Block> generateBlock(std::ifstream &f) override;
	void changeRandom(bool isRand) override;
	int getTimer() override;
	void setTimer(int n) override;
	~Level4();
};

#endif
