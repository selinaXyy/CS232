#ifndef _HEXSOLUTION
#define _HEXSOLUTION

const int NUM_OF_CELLS = 7;
const int NUM_OF_SIDES = 6;

struct hexCell {
	int num = 0;
	int top = 0;
	int topRight = 0;
	int bottomRight = 0;
	int bottom = 0;
	int bottomLeft = 0;
	int topLeft = 0;
};

class HexSolution {
private:
	hexCell hexCellArr[NUM_OF_CELLS];

public:
	HexSolution();
	int returnValidSideVal(int sidesGivenArr[NUM_OF_SIDES]);
	void setHexSolution();
	void displayHexSolution() const;
};

#endif