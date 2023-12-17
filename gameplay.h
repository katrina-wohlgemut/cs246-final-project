#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "text.h"
#include "control.h"
#include <vector>
#include <iostream>
#include <memory>
extern const int numRow;
extern const int numCol;
class Block;

class GamePlay {
	std::vector<std::shared_ptr<Block>> bPtrs;
	bool extraHeavy = false;
	void removeRow(int row);
	// returns true if block is not off the board or interfering with another block
	bool moveValid(std::shared_ptr<Block> &b);
	void redrawBoard();
public:
	Text t;
	std::unique_ptr<Control> c;
	std::shared_ptr<Block> nextBlock;
	GamePlay(int level);

	// returns the number of rows that were completed and removes completed rows
	int rowsComplete();

	// adds the new block as the next block and makes the next block the current block
	// returns true if this is successful and false otherwise
	bool addBlock(std::shared_ptr<Block> b);
	// l, r, d for left, right, and down respectively (for dir)
	// returns whether or not the block could be moved
	bool moveBlock(std::shared_ptr<Block> b, int num, char dir);
	// supports w for clockwise and c for counterclockwise
	void rotateBlock(std::shared_ptr<Block> b, char dir);
	//returns the current block that can be manipulated
	std::shared_ptr<Block> getCurrentBlock();
	void reset();
	bool changeBlock(std::shared_ptr<Block> b, char c);
	bool placeBlock(std::shared_ptr<Block> b);
	bool getExtraHeavy();
	void setExtraHeavy(bool b);
	virtual ~GamePlay();
};

#endif
