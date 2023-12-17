#include "level3.h"

Level3::Level3(): random{true} {}

void Level3::changeRandom(bool isRand) {
	random = isRand;
}

std::shared_ptr<Block> Level3::generateBlock(std::ifstream &f) {
	char c;
	// Generates randomly or from file depending on user commands
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
	auto b = std::make_shared<BasicBlock>(c, 3, true);
	return b;
}

Level3::~Level3() {}

