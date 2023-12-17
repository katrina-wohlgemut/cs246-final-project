#include "level0.h"

Level0::Level0() {}

std::shared_ptr<Block> Level0::generateBlock(std::ifstream &f) {
	char c = ' ';
	// End of file
	if (! (f >> c)) {
		throw std::string{"End of file"};
	}
	auto b = std::make_shared<BasicBlock>(c, 0);
	return b;
}


Level0::~Level0() {}
