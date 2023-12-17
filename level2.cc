#include "level2.h"
#include <vector>

Level2::Level2() {}

std::shared_ptr<Block> Level2::generateBlock(std::ifstream &f) {
	int n = rand() % 7;
	std::vector<char> v = {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};
	auto b = std::make_shared<BasicBlock>(v[n], 2);
	return b;
}

Level2::~Level2() {}
