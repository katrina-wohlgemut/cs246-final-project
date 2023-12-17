#include "board.h"
#include "block.h"
#include "window.h"

Board::Board(GamePlay &p1, GamePlay &p2, bool onlyText): p1{p1}, p2{p2}, oldBoard1{p1.t.cells}, oldBoard2{p1.t.cells}, wasBlind1{false}, wasBlind2{false} {
	oldLevel1 = p1.c->getLevel();
	oldLevel2 = p2.c->getLevel();
	oldScore1 = p1.c->getScore();
	oldScore2 = p2.c->getScore();
	oldHiScore1 = p1.c->getHiScore();
	oldHiScore2 = p2.c->getHiScore();

	// Set up graphical display
	if (!onlyText) {
		x = std::make_unique<Xwindow>();
		x->drawString(200, 15, std::string{"BIQUADRIS"});
		x->drawString(100, 30, std::string{"Level:"});
		std::ostringstream s;
		s << oldLevel1;
		x->drawString(150, 30, s.str());
		x->drawString(290, 30, std::string{"Level:"});
		s.str("");
		s << oldLevel2;
		x->drawString(340, 30, s.str());
		x->drawString(100, 45, std::string{"Score:"});
		s.str("");
		s << oldScore1;
		x->drawString(150, 45, s.str());
		x->drawString(290, 45, std::string{"Score:"});
		s.str("");
		s << oldScore2;
		x->drawString(340, 45, s.str());
		x->drawString(100, 60, std::string{"HiScore:"});
		s.str("");
		s << oldHiScore1;
		x->drawString(165, 60, s.str());
		x->drawString(290, 60, std::string{"HiScore:"});
		s.str("");
		s << oldHiScore2;
		x->drawString(355, 60, s.str());
		x->fillRectangle(100, 260, 110, 2, 1);
		x->fillRectangle(290, 260, 110, 2, 1);
		x->drawString(100, 315, std::string{"Next:"});
		x->drawString(290, 315, std::string{"Next:"});
	}
}
void Board::graphicDrawBlock(const std::shared_ptr<Block> &b, int height, char pos) {
	int colour = getColour(b->type);
	int size = b->xcoor.size();
	if (pos == 'l') {
		for (int i = 0; i < size; ++i) {
			int newX = 100 + b->xcoor[i]*10;
			int newY = height + b->ycoor[i]*10;
			x->fillRectangle(newX, newY, 10, 10, colour);
		}
	} else { 
		for (int i = 0; i < size; ++i) {
			int newX = 290 + b->xcoor[i]*10;
			int newY = height + b->ycoor[i]*10;
			x->fillRectangle(newX, newY, 10, 10, colour);
		}
	}
}

int Board::getColour(char c) {
	if (c == 'I') {
		return 2;
	} else if (c == 'J') {
		return 3;
	} else if (c == 'L') {
		return 4;
	} else if (c == 'O') {
		return 5;
	} else if (c == 'S') {
		return 6;
	} else if (c == 'Z') {
		return 7;
	} else if (c == 'T') {
		return 8;
	} else if (c == '*') {
		return 9;
	} else if (c == '?') {
		return 1;
	} else {
		return 0;
	}
}

void Board::drawBlocks(const std::shared_ptr<Block> &b1, const std::shared_ptr<Block> &b2) const {
	std::vector<std::vector<char>> temp1;
	std::vector<std::vector<char>> temp2;
	for (int i = 0; i < 2; ++i) {
		std::vector<char> c;
		for (int j = 0; j < 4; ++j) {
			c.emplace_back(' ');
		}
		temp1.emplace_back(c);
		temp2.emplace_back(c);
	}
	int size = b1->xcoor.size();
	for (int i = 0; i < size; ++i) {
		temp1[b1->ycoor[i]-2][b1->xcoor[i]] = b1->type;
	}
	size = b2->xcoor.size();
	for (int i = 0; i < size; ++i) {
		temp2[b2->ycoor[i]-2][b2->xcoor[i]] = b2->type;
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) std::cout << temp1[i][j];
		for (int j= 0; j < 17; ++j) std::cout << ' ';
		for (int j = 0; j < 4; ++j) std::cout << temp2[i][j];
		std::cout << std::endl;
	}
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
	std::cout << "Level:";
	std::cout << std::setw(5) << std::right << b.p1.c->getLevel();
	std::cout << std::setw(5+numCol) << std::right << "Level:";
	std::cout << std::setw(5) << std::right << b.p2.c->getLevel() << std::endl;
	std::cout << "Score:";
	std::cout << std::setw(5) << std::right << b.p1.c->getScore();
	std::cout << std::setw(5+numCol) << std::right << "Score:";
	std::cout << std::setw(5) << std::right << b.p2.c->getScore() << std::endl;
	std::cout << "HiScore:";
	std::cout << std::setw(3) << std::right << b.p1.c->getHiScore();
	std::cout << std::setw(7+numCol) << std::right << "HiScore:";
	std::cout << std::setw(3) << std::right << b.p2.c->getHiScore() << std::endl;

	for (int i = 0; i < numCol; ++i) std::cout << '-';
	for (int i = 0; i < numCol - 1; ++i) std::cout << ' ';
	for (int i = 0; i < numCol; ++i) std::cout << '-';
	std::cout << std::endl;

	for (int i = 0; i < numRow; ++i) {
		for (int j = 0; j < numCol; ++j) {
			if (b.p1.t.isBlind() && i>=3 && i<=12 && j>=3 && j<=9) {
				out << '?';
			} else {	       
				out << b.p1.t.cells[i][j];
			}
		}
		for (int j = 0; j < numCol - 1; ++j) {
			out << ' ';
		}
		for (int j = 0; j < numCol; ++j) {
			if (b.p2.t.isBlind() && i>=3 && i<=12 && j>=3 && j<=9) {
				out << '?';
			} else {
				out << b.p2.t.cells[i][j];
			}
		}
		out << std::endl;
	}

	for (int i = 0; i < numCol; ++i) std::cout << '-';
	for (int i = 0; i < numCol - 1; ++i) std::cout << ' ';
	for (int i = 0; i < numCol; ++i) std::cout << '-';
	std::cout << std::endl;
	std::cout << std::setw(numCol) << std::left << "Next:";
	std::cout << std::setw(4+numCol) << std::right << "Next:" << std::endl;
	b.drawBlocks(b.p1.nextBlock, b.p2.nextBlock);
	return out;
}

void Board::displayGraphics(std::string command) {
	// Only redraw next blocks if necessary
	if (command == std::string{"drop"} || command == std::string{"restart"}) {
		x->fillRectangle(100, 360, 40, 20, 0);
		x->fillRectangle(290, 360, 40, 20, 0);
		graphicDrawBlock(p1.nextBlock, 340, 'l');
		graphicDrawBlock(p2.nextBlock, 340, 'r');
	}

	// Only redraw text as necessary
	std::ostringstream s;
	if (oldLevel1 != p1.c->getLevel()) {
		oldLevel1 = p1.c->getLevel();
		s << oldLevel1;
		x->fillRectangle(140, 20, 20, 10, 0);
		x->drawString(150, 30, s.str());
	}
	s.str("");
	if (oldScore1 != p1.c->getScore()) {
		oldScore1 = p1.c->getScore();
		s << oldScore1;
		x->fillRectangle(140, 35, 30, 10, 0);
		x->drawString(150, 45, s.str());
	}
	s.str("");
	if (oldHiScore1 != p1.c->getHiScore()) {
		oldHiScore1 = p1.c->getHiScore();
		s << oldHiScore1;
		x->fillRectangle(155, 50, 30, 10, 0);
		x->drawString(165, 60, s.str());
	}
	s.str("");
	if (oldLevel2 != p2.c->getLevel()) {
		oldLevel2 = p2.c->getLevel();
		s << oldLevel2;
		x->fillRectangle(330, 20, 20, 10, 0);
		x->drawString(340, 30, s.str());
	}
	s.str("");
	if (oldScore2 != p2.c->getScore()) {
		oldScore2 = p2.c->getScore();
		s << oldScore2;
		x->fillRectangle(330, 35, 30, 10, 0);
		x->drawString(340, 45, s.str());
	}
	s.str("");
	if (oldHiScore2 != p2.c->getHiScore()) {
		oldHiScore2 = p2.c->getHiScore();
		s << oldHiScore2;
		x->fillRectangle(345, 50, 30, 10, 0);
		x->drawString(355, 60, s.str());
	}


	int colour;
	// Only redraw changed sections
	for (int i = 0; i < numRow; ++i) {
		for (int j = 0; j < numCol; ++j) {
			if (oldBoard1[i][j] != p1.t.cells[i][j]) {
				oldBoard1[i][j] = p1.t.cells[i][j];
				if (p1.t.isBlind() && i >= 3 && i <= 12 && j >= 3 && j <= 9) {
					if (oldBoard1[i][j] != '?') {
						oldBoard1[i][j] = '?';
						x->fillRectangle(100+j*10, 80+i*10, 10, 10, 1);
					} 
				} else {
					colour = getColour(oldBoard1[i][j]);
					x->fillRectangle(100+j*10, 80+i*10, 10, 10, colour);
				}
			} else if (p1.t.isBlind() && i >= 3 && i <= 12 && j >= 3 && j <= 9) {
				if (oldBoard1[i][j] != '?') {
					oldBoard1[i][j] = '?';
					x->fillRectangle(100+j*10, 80+i*10, 10, 10, 1);
				}
			}
		}
	}

	for (int i = 0; i < numRow; ++i) {
		for (int j = 0; j < numCol; ++j) {
			if (oldBoard2[i][j] != p2.t.cells[i][j]) {
				oldBoard2[i][j] = p2.t.cells[i][j];
				if (p2.t.isBlind() && i >= 3 && i <= 12 && j >= 3 && j <= 9) {
					if (oldBoard2[i][j] != '?') {
						oldBoard2[i][j] = '?';
						x->fillRectangle(290+j*10, 80+i*10, 10, 10, 1);
					} 
				} else {
					colour = getColour(oldBoard2[i][j]);
					x->fillRectangle(290+j*10, 80+i*10, 10, 10, colour);
				}
			}else if (p2.t.isBlind() && i >= 3 && i <= 12 && j >= 3 && j <= 9) {
				if (oldBoard2[i][j] != '?') {
					oldBoard2[i][j] = '?';
					x->fillRectangle(290+j*10, 80+i*10, 10, 10, 1);
				}
			}
		}
	}
}


Board::~Board() {
}
