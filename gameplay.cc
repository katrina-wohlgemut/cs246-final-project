#include "gameplay.h"
#include "block.h"
const int numRow = 18;
const int numCol = 11;

GamePlay::GamePlay(int level): c{std::make_unique<Control>(level)} {}

void GamePlay::removeRow(int row) {
	// Clear row
	for (int i = 0; i < numCol; ++i) {
		t.cells[row][i] = ' ';
	}
	// Remove cells from blocks in the row
	int ptrSize = bPtrs.size();
	for (int i = 0; i < ptrSize-1; ++i) {
		if (bPtrs[i]->xcoor.empty()) continue;
		int size = bPtrs[i]->xcoor.size();
		for (int j = 0; j < size; ++j) {
			if (bPtrs[i]->ycoor[j] == row) {
				bPtrs[i]->ycoor.erase(bPtrs[i]->ycoor.begin()+j);
				bPtrs[i]->xcoor.erase(bPtrs[i]->xcoor.begin()+j);
				--size;
				--j;
			} else if (bPtrs[i]->ycoor[j] < row) {
				// Shift blocks above down a row
				bPtrs[i]->ycoor[j] += 1;			
			}
		}
		// Block has completely disappeared
		if (bPtrs[i]->xcoor.empty()) {
			c->changeScore((bPtrs[i]->getLevelGen()+1)*(bPtrs[i]->getLevelGen()+1));
		}
	}
	redrawBoard();
}

void GamePlay::redrawBoard() {
	t.reset();
	int ptrSize = bPtrs.size();
	for (int i = 0; i < ptrSize; ++i) {
		int size = bPtrs[i]->xcoor.size();
		for (int j = 0; j < size; ++j) {
			t.cells[bPtrs[i]->ycoor[j]][bPtrs[i]->xcoor[j]] = bPtrs[i]->type;
		}
	}
}

int GamePlay::rowsComplete() {
	int numRows = 0;
	for (int i = 0; i < numRow; ++i) {
		for (int j = 0; j < numCol; ++j) {
			if (t.cells[i][j] == ' ') break;
			if (j == numCol - 1) {
				removeRow(i);
				++numRows;
			}
		}
	}
	return numRows;
}

bool GamePlay::moveBlock(std::shared_ptr<Block> b, int num, char dir) {
	bool moved = false;
	int size = b->xcoor.size();
	// Clear spot in board
	for (int i = 0; i < size; ++i) {
		t.cells[b->ycoor[i]][b->xcoor[i]] = ' ';
	}
	std::vector<int> x = b->xcoor;
	std::vector<int> y = b->ycoor;
	b->move(num, dir);
	if (moveValid(b)) {
		moved = true;
	} else {
		// If move not valid, revert to original
		b->xcoor = x;
		b->ycoor = y;
	}
	for (int i = 0; i < size; ++i) {
		t.cells[b->ycoor[i]][b->xcoor[i]] = b->type;
	}
	return moved;
}

void GamePlay::rotateBlock(std::shared_ptr<Block> b, char dir) {
	int size = b->xcoor.size();
	for (int i = 0; i < size; ++i) {
		t.cells[b->ycoor[i]][b->xcoor[i]] = ' ';
	}
	std::vector<int> x = b->xcoor;
	std::vector<int> y = b->ycoor;
	b->rotateBlock(dir);
	if (!moveValid(b)) {
		// If move not valid, revert to original
		b->xcoor = x;
		b->ycoor = y;
	}
	for (int i = 0; i < size; ++i) {
		t.cells[b->ycoor[i]][b->xcoor[i]] = b->type;
	}
}

bool GamePlay::moveValid(std::shared_ptr<Block> &b) {
	int size = b->xcoor.size();
	for (int i = 0; i < size; ++i) {
		if (b->ycoor[i] < 0 || b->ycoor[i] >= numRow || b->xcoor[i] < 0 || b->xcoor[i] >= numCol) {
			return false;
		} else if (t.cells[b->ycoor[i]][b->xcoor[i]] != ' ' && t.cells[b->ycoor[i]][b->xcoor[i]] != '?') {
			return false;
		}
	}
	return true;
}

bool GamePlay::changeBlock(std::shared_ptr<Block> b, char c) {
	bool changed = true;
	char orig = b->type;
	int size = b->xcoor.size();
	for (int i = 0; i < size; ++i) {
		t.cells[b->ycoor[i]][b->xcoor[i]] = ' ';
	}
	std::vector<int> x = b->xcoor;
	std::vector<int> y = b->ycoor;
	b->changeBlock(c);
	if (!moveValid(b)) {
		changed = false;
		b->xcoor = x;
		b->ycoor = y;
		b->type = orig;
	}
	for (int i = 0; i < size; ++i) {
		t.cells[b->ycoor[i]][b->xcoor[i]] = b->type;
	}
	return changed;
}

bool GamePlay::addBlock(std::shared_ptr<Block> b) {
	int size = b->xcoor.size();
	// If can't place nextBlock on board
	if (!moveValid(nextBlock)) return false;
	if (nextBlock != nullptr) {
		for (int i = 0; i < size; ++i) {
			t.cells[nextBlock->ycoor[i]][nextBlock->xcoor[i]] = nextBlock->type;
		}
		bPtrs.emplace_back(std::move(nextBlock));

	}
	nextBlock = b;
	return true;
}

bool GamePlay::placeBlock(std::shared_ptr<Block> b) {
	int size = b->xcoor.size();
	if (!moveValid(b)) return false;
	for (int i = 0; i < size; ++i) {
		t.cells[b->ycoor[i]][b->xcoor[i]] = b->type;
	}
	bPtrs.emplace_back(b);
	return true;
}

std::shared_ptr<Block> GamePlay::getCurrentBlock() {
	for (auto i = bPtrs.rbegin(); i != bPtrs.rend(); ++i) {
		if ((*i)->type != '*') return *i;
	}
	return bPtrs.back();
}


void GamePlay::reset() {
	c->reset();
	for (int i = 0; i < numRow; ++i) {
		for (int j = 0; j < numCol; ++j) {
			t.cells[i][j] = ' ';
		}
	}
	bPtrs.clear();
}

bool GamePlay::getExtraHeavy() {return extraHeavy;}

void GamePlay::setExtraHeavy(bool b) {extraHeavy = b;}

GamePlay::~GamePlay() {
}
