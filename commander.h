#ifndef COMMANDER_H
#define COMMANDER_H
#include <string>
#include <iomanip>
#include <memory>
#include "gameplay.h"
#include "basicblock.h"
#include "control.h"
#include "board.h"

class Commander {
	std::unique_ptr<std::ifstream> f1;
	std::unique_ptr<std::ifstream> f2;
	GamePlay &p1;
	GamePlay &p2;
	Board &b;
	bool onlyText;
	std::string name1;
	std::string name2;

	// Gets game set up (one block in play, one block in next)
	void startGame(GamePlay &p1, GamePlay &p2, std::unique_ptr<std::ifstream> &f1, std::unique_ptr<std::ifstream> &f2, std::string name1, std::string name2);
	// Resets game when player lost
	void playerLost(GamePlay &p1, GamePlay &p2, std::unique_ptr<std::ifstream> &f1, std::unique_ptr<std::ifstream> &f2, std::string name1, std::string name2, int player);
	// Places special block in level 4
	int specialBlock(GamePlay &p);
	// Does appropriate command 
	// returns 0 if normal turn, 1 if it is the other player's turn, and 2 if the player lost
	int doCommand(std::string command, GamePlay& p, std::unique_ptr<std::ifstream> &f, std::string baseFile, int multiplier);
	// Changes shortcut command to full word command
	std::string changeCommand(std::string command);

public:
	Commander(GamePlay &p1, GamePlay &p2, Board &b, bool onlyText, std::string name1, std::string name2);
	// Run actual game play
	void runGame();
	~Commander();
};

#endif
