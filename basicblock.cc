#include "basicblock.h"
#include <memory>

BasicBlock::BasicBlock(char type, int levelGen, bool isHeavy): Block{type, levelGen, isHeavy} {}
void BasicBlock::move(int num, char dir) {
	int size = xcoor.size();
	if (dir == 'l') {
		for (int i = 0; i < size; ++i) {
			(xcoor[i]) -= num;
		}
	} else if (dir == 'r') {
		for (int i = 0; i < size; ++i) {
			(xcoor[i]) += num;
		}
	} else {
		for (int i = 0; i < size; ++i) {
			(ycoor[i]) += num;
		}
	}
}

void BasicBlock::rotateBlock(char dir) {
	int minX = numCol;
	int maxX = 0;
	int minY = numRow;
	int maxY = 0;
	for (auto x:xcoor) {
		if (x > maxX) maxX = x;
		if (x < minX) minX = x;
	}
	for (auto y:ycoor) {
		if (y > maxY) maxY = y;
		if (y < minY) minY = y;
	}

	// Finding smallest square side length that contains Block
	int max;
	if (maxX - minX > maxY - minY) max = maxX - minX;
	else max = maxY - minY;
	minY = maxY - max;
	int size = xcoor.size();
	for (int i = 0; i < size; ++i) {
		xcoor[i] -= minX;
		ycoor[i] -= minY;
	}

	if (dir == 'c') {
		for (int i = 0; i < size; ++i) {
			int xTemp = xcoor[i];
			xcoor[i] = ycoor[i] + minX;
			ycoor[i] = max - xTemp + minY;
		}
	} else if (dir == 'w') {
		for (int i = 0; i < size; ++i) {
			int yTemp = ycoor[i];
			ycoor[i] = xcoor[i] + minY;
			xcoor[i] = max - yTemp + minX;
		}
	}

}

void BasicBlock::changeBlock(char c) {
	auto b = std::make_unique<BasicBlock>(c, getLevelGen(), getIsHeavy());
	int minX = numCol;
	int maxY = 0;
	for (auto x: xcoor){
		if (x < minX) minX = x;
	}
	for (auto y: ycoor) {
		if (y > maxY) maxY = y;
	}
	xcoor = b->xcoor;
	ycoor = b->ycoor;
	int size = xcoor.size();
	for (int i = 0; i < size; ++i) {
		xcoor[i] += minX;
		ycoor[i] += maxY - 3;
	}
	type = c;
}	


BasicBlock::~BasicBlock() {}
