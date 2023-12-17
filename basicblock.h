#ifndef BASICBLOCK_H
#define BASICBLOCK_H
#include "block.h"

class BasicBlock: public Block {
public:
	BasicBlock(char type, int levelGen, bool isHeavy = false);
	// Adjusts the coordinates of the block to move the block num units in dir direction
	void move(int num, char dir) override;
	// Rotates the block counterclockwise if dir = c and clockwise if dir = w
	// Bottom left corner of smallest rectangle containing block is preserved
	void rotateBlock(char dir) override;
	// Changes the Block to be of type c
	void changeBlock(char c) override;
	~BasicBlock();
};

#endif
