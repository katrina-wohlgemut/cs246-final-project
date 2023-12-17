#ifndef LEVEL_H
#define LEVEL_H
#include "block.h"
#include "basicblock.h"
#include <fstream>
#include <cstdlib>
#include <memory>

class Level {
public:
	Level();
	// Generates Block of appropriate type
	virtual std::shared_ptr<Block> generateBlock(std::ifstream &f)=0;
	virtual void changeRandom(bool isRand)=0;
	virtual void setTimer(int n)=0;
	virtual int getTimer()=0;
	virtual ~Level();
};
#endif
