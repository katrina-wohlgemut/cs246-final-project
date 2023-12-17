#include "text.h"

Text::Text() {
	for (int i = 0; i < 18; ++i) {
		std::vector<char> c;
		for (int j = 0; j < 11; ++j) {
			c.emplace_back(' ');
		}
		cells.emplace_back(c);
	}
}
void Text::reset() {
	for (int i = 0; i < numRow; ++i) {
		for (int j = 0; j < numCol; ++j) {
			cells[i][j] = ' ';
		}
	}
}

void Text::changeBlind(bool b) {
	blind = b;
}

bool Text::isBlind()const {return blind;}

Text::~Text() {}

