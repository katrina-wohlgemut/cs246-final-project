#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
extern const int numRow;
extern const int numCol;

class Block {
	int levelGen;
	bool isHeavy;
public:
	std::vector<int> xcoor;
	std::vector<int> ycoor;
	char type;
	
	Block(char type, int levelGen, bool isHeavy = false);
	// Moves block num units in dir direction
	virtual void move(int num, char dir)=0;
	// Rotates block counterclockwise if dir = c, and clockwise if dir = w
	// Bottom left corner of smallest rectangle containing block is preserved
	virtual void rotateBlock(char dir)=0;
	int getLevelGen();
	bool getIsHeavy();
	// Chnages block to type c
	virtual void changeBlock(char c)=0;
	virtual ~Block();
};

#endif
