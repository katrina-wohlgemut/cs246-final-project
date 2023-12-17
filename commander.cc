#include "commander.h"

Commander::Commander(GamePlay &p1, GamePlay &p2, Board &b, bool onlyText, std::string name1, std::string name2): f1{std::make_unique<std::ifstream>(name1)}, f2{std::make_unique<std::ifstream>(name2)}, p1{p1}, p2{p2}, b{b}, onlyText{onlyText}, name1{name1}, name2{name2} {
}

std::string Commander::changeCommand(std::string command) {
	std::vector<std::string> v = {"left", "right", "down", "drop", "levelup", "leveldown", "restart", "random", "norandom", "sequence", "clockwise", "counterclockwise", "I", "J", "L", "O", "S", "Z", "T"};
	int cLen = command.length();
	int size = v.size();
	int numFound = 0;
	std::string newCommand;
	for (int i = 0; i < size; ++i) {
		int sLen = v[i].length();
		for (int j = 0; j < cLen; ++j) {
			if (j >= sLen) break;
			if (v[i][j] != command[j]) break;
			if (j == cLen - 1) {
				newCommand = v[i];
				++numFound;
			}		
		}
	}
	if (numFound == 1) return newCommand;
	return command;
}

int Commander::specialBlock(GamePlay& p) {
	p.c->lev->setTimer((-1)*p.c->lev->getTimer());
	auto b2 = std::make_shared<BasicBlock>('*', 4);
	if (!p.placeBlock(b2)) {
		return 2;
	}
	while (p.moveBlock(b2, 1, 'd')) {}
	return 1;
}

int Commander::doCommand(std::string command, GamePlay& p, std::unique_ptr<std::ifstream> &f, std::string baseFile, int multiplier) {
	int outcome = 0;
	auto currentBlock = p.getCurrentBlock();
	if (command == std::string{"drop"}) {
		if (p.t.isBlind()) {
			p.t.changeBlind(false);
		}
		if (p.getExtraHeavy()) p.setExtraHeavy(false);
		for (int i = 0; i < multiplier; ++i) {
			currentBlock = p.getCurrentBlock();
			while (p.moveBlock(currentBlock, 1, 'd')) {}
			p.c->lev->setTimer(1);
			int n = p.c->lev->getTimer();
			if (n > 5) {
				outcome = specialBlock(p);
				if (outcome == 2) break;
			}
			std::shared_ptr<Block> b;
			// Reset file if at end of file
			try{
				b = p.c->lev->generateBlock(*f);
			} catch (std::string msg) {
				f->clear();
				f->seekg(0, std::ios::beg);
				b = p.c->lev->generateBlock(*f);
			}
			if (!p.addBlock(std::move(b))) {
				outcome = 2;
				break;
			}
			outcome = 1;
		}
	} else if (command == std::string{"left"})  {
		for (int i = 0; i < multiplier; ++i)
			p.moveBlock(currentBlock,1, 'l');
		if (currentBlock->getIsHeavy()) {
			p.moveBlock(currentBlock, 1, 'd');
		}	
		if (p.getExtraHeavy()) {
			if (!p.moveBlock(currentBlock, 2, 'd')) {
				return doCommand(std::string{"drop"}, p, f, baseFile, 1);
			}
		}	
	} else if (command == std::string{"right"}) {
		for (int i = 0; i < multiplier; ++i)
			p.moveBlock(currentBlock, 1, 'r');
		if (currentBlock->getIsHeavy()) {
			p.moveBlock(currentBlock, 1, 'd');
		}
		if (p.getExtraHeavy()) {
			if (!p.moveBlock(currentBlock, 2, 'd')) {
				return doCommand(std::string{"drop"}, p, f, baseFile, 1);
			}
		}	
	} else if (command == std::string{"down"}) {
		for (int i = 0; i < multiplier; ++i)
			p.moveBlock(currentBlock, 1, 'd');
		if (currentBlock->getIsHeavy()) {
			p.moveBlock(currentBlock, 1, 'd');
		}	
	} else if (command == std::string{"levelup"}) {
		p.c->changeLevel(multiplier);
	} else if (command == std::string{"leveldown"}) {
		p.c->changeLevel(multiplier*(-1));
		if (p.c->getLevel() == 0) {
			f.reset(new std::ifstream{baseFile});
		}
	} else if (command == std::string{"norandom"}) {
		std::string name;
		if (std::cin >> name) {
			if (p.c->getLevel() == 3 || p.c->getLevel() == 4) {
				p.c->changeRandom(false);
				f.reset(new std::ifstream{name});
			}
		}
	} else if (command == std::string{"random"}) {
		if (p.c->getLevel() == 3 || p.c->getLevel() == 4) {
			p.c->changeRandom(true);
		}
	} else if (command == std::string{"clockwise"}) {
		for (int i = 0; i < multiplier; ++i) {
			p.rotateBlock(currentBlock, 'w');
		}
	} else if (command == std::string{"counterclockwise"}) {
		for (int i = 0; i < multiplier; ++i) {
			p.rotateBlock(currentBlock, 'c');
		}
		if (currentBlock->getIsHeavy()) {
			p.moveBlock(currentBlock, 1, 'd');
		}
	} else if (command == std::string{"I"}) {
		p.changeBlock(currentBlock, 'I');
	} else if (command == std::string{"J"}) {
		p.changeBlock(currentBlock, 'J');
	} else if (command == std::string{"L"}) {
		p.changeBlock(currentBlock, 'L');
	} else if (command == std::string{"O"}) {
		p.changeBlock(currentBlock, 'O');
	} else if (command == std::string{"S"}) {
		p.changeBlock(currentBlock, 'S');
	} else if (command == std::string{"Z"}) {
		p.changeBlock(currentBlock, 'Z');
	} else if (command == std::string{"T"}) {
		p.changeBlock(currentBlock, 'T');
	}

	return outcome;
}


void Commander::startGame(GamePlay &p1, GamePlay &p2, std::unique_ptr<std::ifstream> &f1, std::unique_ptr<std::ifstream> &f2, std::string name1, std::string name2) {
	auto b = std::move(p1.c->lev->generateBlock(*f1));
	auto b2 = std::move(p1.c->lev->generateBlock(*f1));
	p1.nextBlock = std::move(b);
	p1.addBlock(std::move(b2));
	auto b3 = std::move(p2.c->lev->generateBlock(*f2));
	auto b4 = std::move(p2.c->lev->generateBlock(*f2));
	p2.nextBlock = std::move(b3);
	p2.addBlock(std::move(b4));
	p1.c->lev->setTimer(1);
	p2.c->lev->setTimer(1);
}

void Commander::playerLost(GamePlay &p1, GamePlay &p2, std::unique_ptr<std::ifstream> &f1, std::unique_ptr<std::ifstream> &f2, std::string name1, std::string name2, int player) {
	std::cout << "Player " << player << " lost!" << std::endl;
	std::cout << "Type q to quit and r to restart" <<std::endl;
	char c;
	std::cin >> c;
	if (c == 'q') throw std::string{"done"};
	p1.reset();
	p2.reset();

	f1.reset(new std::ifstream{name1});
	f2.reset(new std::ifstream{name2});
	startGame(p1, p2, f1, f2, name1, name2);
}

void Commander::runGame() {		
	startGame(p1, p2, f1, f2, name1, name2);
	int player = 1;
	std::cout << b;
	if (!onlyText) b.displayGraphics(std::string{"drop"});
	std::cout << std::endl;
	std::string command;
	bool inSeq = false;
	std::unique_ptr<std::ifstream> f;
	while (true) {
		if (inSeq) {
			if (! (*f >> command)) {
				inSeq = false;
				continue;
			}
		} else {
			if (!(std::cin >> command)) break;
		}		
		int outcome = 0;
		int multiplier = 1;
		//get multipliers out first
		std::string num = "";
		int len = command.length();
		for (int i = 0; i < len; ++i) {
			if ('0' <= command[i] && command[i] <= '9') {
				num += command[i];
				command.erase(command.begin()+i);
				--len;
				--i;
			}
		}
		std::istringstream s{num};
		if (! (s >> multiplier)) multiplier = 1;
		command = changeCommand(command);
		if (command == std::string{"restart"}) {
			p1.reset();
			p2.reset();
			player = 1;
			f1.reset(new std::ifstream{name1});
			f2.reset(new std::ifstream{name2});
			startGame(p1, p2, f1, f2, name1, name2);
		} else if (command == std::string{"sequence"}) {
			std::string s;
			if (std::cin >> s) {
				inSeq = true;
				f.reset(new std::ifstream{s});
			}
		}
		if (player == 1) {
			outcome = doCommand(command, p1, f1, name1, multiplier);
			if (outcome == 1) {
				player = 2;
			} else if (outcome == 2) {
				try {
					playerLost(p1, p2, f1, f2, name1, name2, 1);
					player = 1;
				} catch (std::string msg) {break;}
			}
			int n = 0;
			if (command == std::string{"drop"})
				n = p1.rowsComplete();
			if (n > 0) {
				p1.c->changeScore((p1.c->getLevel()+n)*(p1.c->getLevel()+n));
				p1.c->lev->setTimer((-1)*p1.c->lev->getTimer());
				p1.c->lev->setTimer(1);
			} else if (p1.c->lev->getTimer() == 5) {
				specialBlock(p1);
			}

			if (command == std::string{"drop"} && n > 1) {
				std::cout << "Enter special action:" << std::endl;
				std::string action;
				std::cin >> action;
				if (action == std::string{"blind"}) {
					p2.t.changeBlind(true);
				} else if (action == std::string{"heavy"}) {
					p2.setExtraHeavy(true);
				} else if (action == std::string{"force"}) {
					char c;
					std::cin >> c;
					if (!p2.changeBlock(p2.getCurrentBlock(),c)) {
						try {
							playerLost(p1, p2, f1, f2, name1, name2, 2);
						} catch (std::string msg) {break;}
					}
				}
			}

		} else if (player == 2) {
			outcome = doCommand(command, p2, f2, name2, multiplier);
			if (outcome == 1) {
				player = 1;
			} else if (outcome == 2) {
				try {
					playerLost(p1, p2, f1, f2, name1, name2, 2);
					player = 1;
				} catch (std::string msg) {break;}
			}
			int n = p2.rowsComplete();
			if (n > 0) {
				p2.c->changeScore((p2.c->getLevel()+n)*(p2.c->getLevel()+n));
				p2.c->lev->setTimer((-1)*p2.c->lev->getTimer());
				p2.c->lev->setTimer(1);
			} else if (p2.c->lev->getTimer() == 5) {
				specialBlock(p2);
			}
			if (command == std::string{"drop"} && n > 1) {
				std::cout << "Enter special action:" << std::endl;
				std::string action;
				std::cin >> action;
				if (action == std::string{"blind"}) {
					p1.t.changeBlind(true);
				} else if (action == std::string{"heavy"}) {
					p1.setExtraHeavy(true);
				} else if (action == std::string{"force"}) {
					char c;
					std::cin >> c;
					if (!p1.changeBlock(p1.getCurrentBlock(),c)) {
						try {
							playerLost(p1, p2, f1, f2, name1, name2, 1);
						} catch (std::string msg) {break;}
					}
				}
			}
		}
		std::cout << b;
		std::cout << std::endl;
		if (!onlyText) b.displayGraphics(command);
	}
}

Commander::~Commander() {
}
