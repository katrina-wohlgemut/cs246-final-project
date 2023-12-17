#include "level1.h"

Level1::Level1() {}

std::shared_ptr<Block> Level1::generateBlock(std::ifstream &f) {
	int n = std::rand() % 12;
	char c;
	if (n == 0) {
		c = 'S';
	} else if (n == 1) {
		c = 'Z';
	} else if (n == 2 || n == 3) {
		c = 'I';
	} else if (n == 4 || n == 5) {
		c = 'J';
	} else if (n == 6 || n == 7) {
		c = 'L';
	} else if (n == 8 || n == 9) {
		c = 'O';
	} else {
		c = 'T';
	}
	auto b = std::make_shared<BasicBlock>(c, 1);
	return b;
}

Level1::~Level1() {}


