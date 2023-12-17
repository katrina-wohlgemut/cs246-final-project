#ifndef TEXT_H
#define TEXT_H
#include <vector>
#include <iostream>
extern const int numRow;
extern const int numCol;

class Text {
	bool blind = false;
public:
	std::vector<std::vector<char>> cells;
	Text();
	// Makes cells contain only spaces
	void reset();
	bool isBlind() const;
	void changeBlind(bool b);
	~Text();
};

#endif
