#ifndef BOARD_H
#define BOARD_H
#include "gameplay.h"
#include <iomanip>
#include <vector>
#include <iostream>
#include <memory>
extern const int numRow;
extern const int numCol;

class Xwindow;
class Block;

class Board {
	GamePlay &p1;
	GamePlay &p2;
	std::vector<std::vector<char>> oldBoard1;
	std::vector<std::vector<char>> oldBoard2;
	int oldLevel1;
	int oldLevel2;
	int oldScore1;
	int oldScore2;
	int oldHiScore1;
	int oldHiScore2;
	bool wasBlind1;
	bool wasBlind2;
	std::unique_ptr<Xwindow> x;
	// Text-based display of next blocks
	void drawBlocks(const std::shared_ptr<Block> &b1, const std::shared_ptr<Block> &b2)const;
	// Converts char c to appropriate colour int (to be used with xwindow)
	int getColour(char c);
	// Draws next blocks graphically
	void graphicDrawBlock(const std::shared_ptr<Block> &b, int height, char pos);
public:
	Board(GamePlay &p1, GamePlay &p2, bool onlyText);
	// Graphical display of board
	void displayGraphics(std::string command);
	~Board();
	// Text display of board
	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
