#include <string>
#include <iomanip>
#include <memory>
#include "gameplay.h"
#include "control.h"
#include "board.h"
#include "commander.h"

int main(int argc, char *argv[]) {
	std::string command;
	std::string name1 = "sequence1.txt";
	std::string name2 = "sequence2.txt";
	int level = 0;
	bool onlyText = false;

	// support command-line interface
	for (int i = 0; i < argc; ++i) {
		if (argv[i] == std::string{"-scriptfile1"}) {
			name1 = argv[i+1];
			++i;
		} else if (argv[i] == std::string{"-scriptfile2"}) {
			name2 = argv[i+1];
			++i;
		} else if (argv[i] == std::string{"-seed"}) {
			std::istringstream s{argv[i+1]};
			int n;
			s >> n;
			srand(n);
			++i;
		} else if (argv[i] == std::string{"-startlevel"}) {
			std::istringstream s{argv[i+1]};
			int n;
			s >> n;
			level = n;
			++i;
		} else if (argv[i] == std::string{"-text"}) {
			onlyText = true;
		}
	}

	GamePlay p1{level};
	GamePlay p2{level};

	Board b{p1, p2, onlyText};
	Commander com{p1, p2, b, onlyText, name1, name2};
	com.runGame();
}
