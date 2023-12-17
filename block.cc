#include "block.h"

Block::Block(char type, int levelGen, bool isHeavy): levelGen{levelGen}, isHeavy{isHeavy}, type{type} {
	// Generates appropriate starting position for block type
	if (type == 'I') {
		for (int i = 0; i < 4; ++i) {
			xcoor.emplace_back(i);
			ycoor.emplace_back(3);
		}
	} else if (type == 'J') {
		xcoor.emplace_back(0);
		ycoor.emplace_back(2);
		for (int i = 0; i < 3; ++i) {
			xcoor.emplace_back(i);
			ycoor.emplace_back(3);
		}
	} else if (type == 'L') {
		xcoor.emplace_back(2);
		ycoor.emplace_back(2);
		for (int i = 0; i < 3; ++i) {
			xcoor.emplace_back(i);
			ycoor.emplace_back(3);
		}
	} else if (type == 'O') {
		xcoor.emplace_back(0);
		xcoor.emplace_back(1);
		xcoor.emplace_back(0);
		xcoor.emplace_back(1);
		ycoor.emplace_back(2);
		ycoor.emplace_back(2);
		ycoor.emplace_back(3);
		ycoor.emplace_back(3);
	} else if (type == 'S') {
		xcoor.emplace_back(1);
		xcoor.emplace_back(2);
		xcoor.emplace_back(0);
		xcoor.emplace_back(1);
		ycoor.emplace_back(2);
		ycoor.emplace_back(2);
		ycoor.emplace_back(3);
		ycoor.emplace_back(3);
	} else if (type == 'Z') {
		xcoor.emplace_back(0);
		xcoor.emplace_back(1);
		xcoor.emplace_back(1);
		xcoor.emplace_back(2);
		ycoor.emplace_back(2);
		ycoor.emplace_back(2);
		ycoor.emplace_back(3);
		ycoor.emplace_back(3);
	} else if (type == 'T') {
		xcoor.emplace_back(0);
		xcoor.emplace_back(1);
		xcoor.emplace_back(2);
		xcoor.emplace_back(1);
		ycoor.emplace_back(2);
		ycoor.emplace_back(2);
		ycoor.emplace_back(2);
		ycoor.emplace_back(3);
	} else if (type == '*') {
		xcoor.emplace_back(numCol / 2);
		ycoor.emplace_back(3);
	}
}

int Block::getLevelGen() {
	return levelGen;
}

bool Block::getIsHeavy() { return isHeavy;}

Block::~Block() {}
