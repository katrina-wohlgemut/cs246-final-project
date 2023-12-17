#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"

class Level3: public Level {
	bool random;
public:
	Level3();
	std::shared_ptr<Block> generateBlock(std::ifstream &f) override;
	void changeRandom(bool isRand) override;
	void setTimer(int n) override {}
	int getTimer() override {return 0;}
	~Level3();
};

#endif
