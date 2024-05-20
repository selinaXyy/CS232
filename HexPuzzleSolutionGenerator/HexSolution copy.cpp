#include "HexSolution.h"
#include <iostream>
#include <ctime>
using namespace std;

const int CELL_NUM = 7;
const int SIDE_NUM = 6;

enum cellOrder{middle, top, topRight, bottomRight, bottom, bottomLeft, topLeft};

HexSolution::HexSolution() {
	srand(time(NULL));
}

int HexSolution::returnValidSideVal(int sidesGivenArr[SIDE_NUM]) {
	int randSideNum = rand() % 6 + 1;
	bool validSide;
	int checkCnt;

	do {
		checkCnt = 0;
		validSide = true;
		while (sidesGivenArr[checkCnt] != 0) {
			if (randSideNum == sidesGivenArr[checkCnt]) {
				validSide = false;
				randSideNum = rand() % 6 + 1;
				break;
			}
			else
				checkCnt++;
		}
	} while (!validSide);

	return randSideNum;
}

void HexSolution::setHexSolution() {
	////declarations
	int cellsGiven[CELL_NUM] = { 0, 0, 0, 0, 0, 0, 0 };
	int sidesGiven[SIDE_NUM] = { 0, 0, 0, 0, 0, 0 };
	int cellCnt = 0, sideCnt;
	int randCellNum, randSideNum;

	////set cell nums
	while (cellCnt < CELL_NUM) {
		randCellNum = rand() % 7 + 1;

		//set middle cell
		if (cellCnt != cellOrder::middle) {
			bool isValid;
			//check if cell num is valid to assign
			do {
				int checkCnt = 0;
				isValid = true;

				while (cellsGiven[checkCnt] != 0) {
					if (cellsGiven[checkCnt] == randCellNum) {
						isValid = false; //cell num not valid
						randCellNum = rand() % 7 + 1; //generate a new cell num
						break;
					}
					else
						checkCnt++;
				}
			} while (!isValid);
		}
		hexCellArr[cellCnt].num = randCellNum;
		cellsGiven[cellCnt] = randCellNum;
		cellCnt++;
	}

	////set cell sides
	cellCnt = 0;
	while (cellCnt < CELL_NUM) {
		sideCnt = 0;
		//reset sides given
		for (int i = 0; i < SIDE_NUM; i++)
			sidesGiven[i] = 0;

		//set middle cell
		if (cellCnt == cellOrder::middle) {
			while (sideCnt < SIDE_NUM) {
				randSideNum = returnValidSideVal(sidesGiven);
				sidesGiven[sideCnt] = randSideNum;

				//top
				if (sideCnt == 0) {
					hexCellArr[cellOrder::middle].top = randSideNum;
					hexCellArr[cellOrder::top].bottom = randSideNum;
				}
				//topRight
				else if (sideCnt == 1) {
					hexCellArr[cellOrder::middle].topRight = randSideNum;
					hexCellArr[cellOrder::topRight].bottomLeft = randSideNum;
				}
				//bottomRight
				else if (sideCnt == 2) {
					hexCellArr[cellOrder::middle].bottomRight = randSideNum;
					hexCellArr[cellOrder::bottomRight].topLeft = randSideNum;
				}
				//bottom
				else if (sideCnt == 3) {
					hexCellArr[cellOrder::middle].bottom = randSideNum;
					hexCellArr[cellOrder::bottom].top = randSideNum;
				}
				//bottomLeft
				else if (sideCnt == 4) {
					hexCellArr[cellOrder::middle].bottomLeft = randSideNum;
					hexCellArr[cellOrder::bottomLeft].topRight = randSideNum;
				}
				//topLeft
				else if (sideCnt == 5) {
					hexCellArr[cellOrder::middle].topLeft = randSideNum;
					hexCellArr[cellOrder::topLeft].bottomRight = randSideNum;
				}

				sideCnt++;
			}
		}
		//set other cells
		else {
			while (sideCnt < SIDE_NUM) {
				randSideNum = returnValidSideVal(sidesGiven);
				sidesGiven[sideCnt] = randSideNum;

				//top
				if (sideCnt == 0) {
					if (hexCellArr[cellCnt].top == 0)
						hexCellArr[cellCnt].top = randSideNum;
					else
						sidesGiven[sideCnt] = hexCellArr[cellCnt].top;
				}
				//topRight
				else if (sideCnt == 1) {
					if (hexCellArr[cellCnt].topRight == 0)
						hexCellArr[cellCnt].topRight = randSideNum;
					else
						sidesGiven[sideCnt] = hexCellArr[cellCnt].topRight;
				}
				//bottomRight
				else if (sideCnt == 2) {
					if (hexCellArr[cellCnt].bottomRight == 0)
						hexCellArr[cellCnt].bottomRight = randSideNum;
					else
						sidesGiven[sideCnt] = hexCellArr[cellCnt].bottomRight;
				}
				//bottom
				else if (sideCnt == 3) {
					if (hexCellArr[cellCnt].bottom == 0)
						hexCellArr[cellCnt].bottom = randSideNum;
					else
						sidesGiven[sideCnt] = hexCellArr[cellCnt].bottom;
				}
				//bottomLeft
				else if (sideCnt == 4) {
					if (hexCellArr[cellCnt].bottomLeft == 0)
						hexCellArr[cellCnt].bottomLeft = randSideNum;
					else
						sidesGiven[sideCnt] = hexCellArr[cellCnt].bottomLeft;
				}
				//topLeft
				else if (sideCnt == 5) {
					if (hexCellArr[cellCnt].topLeft == 0)
						hexCellArr[cellCnt].topLeft = randSideNum;
					else
						sidesGiven[sideCnt] = hexCellArr[cellCnt].topLeft;
				}

				sideCnt++;
			}
		}
		cellCnt++;
	}
}

void HexSolution::displayHexSolution() const {
	//display tile num & side vals
	for (int i = 0; i < CELL_NUM; i++) {
		cout << "Tile " << hexCellArr[i].num << ": " << hexCellArr[i].top << " " << hexCellArr[i].topRight << " "
			<< hexCellArr[i].bottomRight << " " << hexCellArr[i].bottom << " " << hexCellArr[i].bottomLeft << " " << hexCellArr[i].topLeft
			<< endl;
	}
	cout << endl;

	//display graph
	cout << "           _" << hexCellArr[cellOrder::top].top << "_" << endl;
	cout << "          /   \\" << endl;
	cout << "         " << hexCellArr[cellOrder::top].topLeft << "     " << hexCellArr[cellOrder::top].topRight << endl;
	cout << "   _" << hexCellArr[cellOrder::topLeft].top << "_  /   " << hexCellArr[cellOrder::top].num << "   \\  _" << hexCellArr[cellOrder::topRight].top << "_" << endl;
	cout << "  /   \\ \\       / /   \\" << endl;
	cout << " " << hexCellArr[cellOrder::topLeft].topLeft << "     " << hexCellArr[cellOrder::topLeft].topRight << " " << hexCellArr[cellOrder::top].bottomLeft << "     " << hexCellArr[cellOrder::top].bottomRight << " " << hexCellArr[cellOrder::topRight].topLeft << "     " << hexCellArr[cellOrder::topRight].topRight << endl;
	cout << "/   " << hexCellArr[cellOrder::topLeft].num << "   \\ \\_" << hexCellArr[cellOrder::top].bottom << "_/ /   " << hexCellArr[cellOrder::topRight].num << "   \\" << endl;
	cout << "\\       / / " << hexCellArr[cellOrder::middle].top << " \\ \\       /" << endl;
	cout << " " << hexCellArr[cellOrder::topLeft].bottomLeft << "     " << hexCellArr[cellOrder::topLeft].bottomRight << " " << hexCellArr[cellOrder::middle].topLeft << "     " << hexCellArr[cellOrder::middle].topRight << " " << hexCellArr[cellOrder::topRight].bottomLeft << "     " << hexCellArr[cellOrder::topRight].bottomRight << endl;
	cout << "  \\_" << hexCellArr[cellOrder::topLeft].bottom << "_/ /   " << hexCellArr[cellOrder::middle].num << "   \\ \\_" << hexCellArr[cellOrder::topRight].bottom << "_/" << endl;
	cout << "  / " << hexCellArr[cellOrder::bottomLeft].top << " \\ \\       / / " << hexCellArr[cellOrder::bottomRight].top << " \\" << endl;
	cout << " " << hexCellArr[cellOrder::bottomLeft].topLeft << "     " << hexCellArr[cellOrder::bottomLeft].topRight << " " << hexCellArr[cellOrder::middle].bottomLeft << "     " << hexCellArr[cellOrder::middle].bottomRight << " " << hexCellArr[cellOrder::bottomRight].topLeft << "     " << hexCellArr[cellOrder::bottomRight].topRight << endl;
	cout << "/   " << hexCellArr[cellOrder::bottomLeft].num << "   \\ \\_" << hexCellArr[cellOrder::middle].bottom << "_/ /   " << hexCellArr[cellOrder::bottomRight].num << "   \\" << endl;
	cout << "\\       / / " << hexCellArr[cellOrder::bottom].top << " \\ \\       /" << endl;
	cout << " " << hexCellArr[cellOrder::bottomLeft].bottomLeft << "     " << hexCellArr[cellOrder::bottomLeft].bottomRight << " " << hexCellArr[cellOrder::bottom].topLeft << "     " << hexCellArr[cellOrder::bottom].topRight << " " << hexCellArr[cellOrder::bottomRight].bottomLeft << "     " << hexCellArr[cellOrder::bottomRight].bottomRight << endl;
	cout << "  \\_" << hexCellArr[cellOrder::bottomLeft].bottom << "_/ /   " << hexCellArr[cellOrder::bottom].num << "   \\ \\_" << hexCellArr[cellOrder::bottomRight].bottom << "_/" << endl;
	cout << "        \\       /" << endl;
	cout << "         " << hexCellArr[cellOrder::bottom].bottomLeft << "     " << hexCellArr[cellOrder::bottom].bottomRight << endl;
	cout << "          \\_" << hexCellArr[cellOrder::bottom].bottom << "_/" << endl;
	cout << endl;
}