#include "level4.h"

Level4::Level4(): random{true}, timer{0} {}

void Level4::changeRandom(bool isRand) {
	random = isRand;
}

int Level4::getTimer() {
	return timer;
}

void Level4::setTimer(int n) {
	timer += n;
	if (timer < 0) timer = 0;
}

std::shared_ptr<Block> Level4::generateBlock(std::ifstream &f) {
	char c;
	// Generates randomly or from file based on user commands
	if (random) {
		int n = rand() % 9;
		if (n == 0 || n == 1) {
			c = 'S';
		} else if (n == 2 || n == 3) {
			c = 'Z';
		} else if (n == 4) {
			c = 'I';
		} else if (n == 5) {
			c = 'J';
		} else if (n == 6) {
			c = 'L';
		} else if (n == 7) {
			c = 'O';
		} else if (n == 8) {
			c = 'T';
		}
	} else {
		if (! (f >> c)) {
			throw std::string{"End of file"};
		}
	}
	auto b = std::make_shared<BasicBlock>(c, 4, true);
	return b;
}

Level4::~Level4() {}
