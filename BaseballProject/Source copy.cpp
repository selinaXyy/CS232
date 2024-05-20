#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <algorithm>

using namespace std;

const int TEAM_SIZE = 12;
const int NUM_OF_INNINGS = 5;
const string POSITIONS[TEAM_SIZE] = { "P", "C", "1B", "2B", "3B", "SS", "LF", "LCF", "RF", "RCF", "OUT", "OUT" };
const int FOREVER_LOOP_CHECK = 300;

void reset1DArray(int arrayPar[]);
void reset2DArray(string arrayPar[][NUM_OF_INNINGS + 1]);
int returnNewPositionIndex(int prevPositionIndexPar);
void sortLineUp(int playerAvgArrPar[], string nameAndPositionArrPar[][NUM_OF_INNINGS + 1]);
void setPositions(string nameAndPositionArrPar[][NUM_OF_INNINGS + 1], int positionsAssignedArrPar[TEAM_SIZE]);
void displayArray(string nameAndPositionArrPar[][NUM_OF_INNINGS + 1]);

int main() {
	////declaration
	//nameAndPosition[playerName][playerPosition]
	string nameAndPosition[TEAM_SIZE][NUM_OF_INNINGS + 1]; //+1 because nameAndPosition[][0] is used to store names
	int playerAvg[TEAM_SIZE];
	int positionAssigned[TEAM_SIZE];

	////get user input
	//get players
	reset2DArray(nameAndPosition);
	cout << "Enter 12 player names:" << endl;
	for (int i = 0; i < TEAM_SIZE; i++) {
		cout << "What is player " << i + 1 << "'s name: ";
		cin >> nameAndPosition[i][0];
	}
	cout << endl;
	//get scores
	reset1DArray(playerAvg);
	cout << "Enter the averages for each player:" << endl;
	cout << "-----------------------------------" << endl;
	for (int i = 0; i < TEAM_SIZE; i++) {
		cout << "What is " << nameAndPosition[i][0] << "'s average: ";
		cin >> playerAvg[i];
	}
	cout << endl;

	////calculation & output
	cout << "Game lineup and field positions:" << endl;
	cout << "--------------------------------" << endl;
	cout << left;
	cout << setw(11) << "Name" << setw(11) << "Inning 1" << setw(11) << "Inning 2" << setw(11) << "Inning 3" << setw(11) << "Inning 4" << setw(11) << "Inning 5" << endl;
	sortLineUp(playerAvg, nameAndPosition);

	// display 3 different position allocations
	for (int i = 0; i < 3; i++) {
		setPositions(nameAndPosition, positionAssigned);
		displayArray(nameAndPosition);
		cout << endl << endl;
	}

	return 0;
}

void reset1DArray(int arrayPar[]) {
	for (int i = 0; i < TEAM_SIZE; i++) {
		arrayPar[i] = 0;
	}
}

void reset2DArray(string arrayPar[][NUM_OF_INNINGS + 1]) {
	for (int i = 0; i < TEAM_SIZE; i++) {

		// j = 0 is already used to store player names
		for (int j = 1; j < NUM_OF_INNINGS + 1; j++) {
			arrayPar[i][j] = "";
		}
	}
}

int returnNewPositionIndex(int prevPositionIndexPar) {
	int newPositionIndex;
	// if the player just played infield
	if (prevPositionIndexPar < 6)
		newPositionIndex = 6 + rand() % (TEAM_SIZE - 6);
	// if the player just played outfield
	else
		newPositionIndex = rand() % 6;
	return newPositionIndex;
}

void sortLineUp(int playerAvgArrPar[], string nameAndPositionArrPar[][NUM_OF_INNINGS + 1]) {
	int maxAvg;
	int maxAvgIndex;
	int tempInt;
	string tempStr;

	for (int i = 0; i < TEAM_SIZE; i++) {
		maxAvg  = playerAvgArrPar[i];
		maxAvgIndex = i;
		for (int j = i + 1; j < TEAM_SIZE; j++) {
			if (playerAvgArrPar[j] > maxAvg) {
				maxAvg = playerAvgArrPar[j];
				maxAvgIndex = j;
			}
		}
		//swap 1D array
		tempInt = playerAvgArrPar[i];
		playerAvgArrPar[i] = playerAvgArrPar[maxAvgIndex];
		playerAvgArrPar[maxAvgIndex] = tempInt;

		// swap 2D array
		tempStr = nameAndPositionArrPar[i][0];
		nameAndPositionArrPar[i][0] = nameAndPositionArrPar[maxAvgIndex][0];
		nameAndPositionArrPar[maxAvgIndex][0] = tempStr;
	}
}

void setPositions(string nameAndPositionArrPar[][NUM_OF_INNINGS + 1], int positionsAssignedArrPar[TEAM_SIZE]) {
	bool allPositionsSet = false;
	int randPositionIndex;
	string prevPosition = "";
	int prevPositionIndex;
	int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	srand(seed);

	while (!allPositionsSet) {
		int i = 1; // col
		int j = 0; // row
		bool restart = false;
		while (i < NUM_OF_INNINGS + 1) {
			reset1DArray(positionsAssignedArrPar); 
			while (j < TEAM_SIZE) {
				// if it is the first inning, just randomly assign positions
				if (i == 1) {
					randPositionIndex = rand() % TEAM_SIZE;
					if (positionsAssignedArrPar[randPositionIndex] == 0) {
						positionsAssignedArrPar[randPositionIndex] = 1;
						nameAndPositionArrPar[j][i] = POSITIONS[randPositionIndex];
						j++;
					}
				}
				else {
					// if the player was in infield last inning, the player needs to be in outfield this inning. Vise versa.
					// no player can be reassigned to a position that they have played in this current game
					int inningCnt = 1;
					int loopCnt = 0;
					prevPosition = nameAndPositionArrPar[j][i - 1];
					prevPositionIndex = find(POSITIONS, POSITIONS + TEAM_SIZE, prevPosition) - POSITIONS; // returns the index of the previous position in POSITIONS
					randPositionIndex = returnNewPositionIndex(prevPositionIndex);

					while (inningCnt < i) {
						// if position was assigned in current inning, genrate a new position
						if (positionsAssignedArrPar[randPositionIndex] != 0)
							randPositionIndex = returnNewPositionIndex(prevPositionIndex);
						else {
							if (nameAndPositionArrPar[j][inningCnt] != POSITIONS[randPositionIndex])
								inningCnt++;
							// if position was assigned to current player before, generate a new position & recheck
							else {
								inningCnt = 1;
								randPositionIndex = returnNewPositionIndex(prevPositionIndex);
							}
						}

						loopCnt++;
						// if a forever loop is entered 
						// (position can be assigned to this player has already been played by the player)
						if (loopCnt > FOREVER_LOOP_CHECK) {
							restart = true;
							break;
						}
					}// while (inningCnt < i)
					if (restart)
						break;
					positionsAssignedArrPar[randPositionIndex] = 1;
					nameAndPositionArrPar[j][i] = POSITIONS[randPositionIndex];
					j++;
				}
			}// while (j < TEAM_SIZE)
			if (restart)
				break;
			i++;
			j = 0; // reset row
		}// while (i < NUM_OF_INNINGS + 1)
		if (!restart)
			allPositionsSet = true;
	}// while (!allPositionsSet)
}

void displayArray(string nameAndPositionArrPar[][NUM_OF_INNINGS + 1]) {
	for (int i = 0; i < TEAM_SIZE; i++) {
		for (int j = 0; j < NUM_OF_INNINGS + 1; j++) 
			cout << setw(11) << nameAndPositionArrPar[i][j];
		cout << endl;
	}
}