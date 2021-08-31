#include "residential.h"
using namespace std;

ResidentialCell::ResidentialCell() {}
ResidentialCell::ResidentialCell(char type, vector<vector<BaseCell> > vect) {
	Type = type;
	grid = vect;
}
void ResidentialCell::setRow(int row) { Row = row; }
void ResidentialCell::setCol(int col) { Col = col; }

void ResidentialCell::mainCall(vector<vector<BaseCell> > vect) {
	grid = vect;

	if (Population == 0) {
		PopulationZeroC1();
		PopulationZeroC2();
	}
	else if (Population == 1) {
		PopulationOne();
	}
	else if (Population == 2) {
		PopulationTwo();
	}
	else if (Population == 3) {
		PopulationThree();
	}
	else if (Population == 4)
		PopulationFour();
}

int ResidentialCell::getRow() { return Row; }
int ResidentialCell::getCol() { return Col; }

//checks if a powerline is adjecent to the cell
bool ResidentialCell::isPowerlineAdj() {

	if ((Row == 0) && (Col == 0)) {
		if ((grid[Row][Col + 1].GetType() == 'T') || (grid[Row][Col + 1].GetType() == '#')) {
			return true;
		}
		if ((grid[Row + 1][Col].GetType() == 'T') || (grid[Row + 1][Col].GetType() == '#')) {
			return true;
		}
		if ((grid[Row + 1][Col + 1].GetType() == 'T') || (grid[Row + 1][Col + 1].GetType() == '#')) {
			return true;
		}
		else { return false; }
	}
	//if cell is in the upper left hand corner
	if ((Row == (grid.size() - 1)) && (Col == 0)) {
		if ((grid[Row - 1][Col].GetType() == 'T') || (grid[Row - 1][Col].GetType() == '#')) {
			return true;
		}
		if ((grid[Row - 1][Col + 1].GetType() == 'T') || (grid[Row - 1][Col + 1].GetType() == '#')) {
			return true;
		}
		if ((grid[Row][Col + 1].GetType() == 'T') || (grid[Row][Col + 1].GetType() == '#')) {
			return true;
		}
		else { return false; }
	}
	//if cell is the lower left hand corner 

	if ((Row == 0) && (Col == (grid[Row].size() - 1))) {
		if ((grid[Row][Col - 1].GetType() == 'T') || (grid[Row][Col - 1].GetType() == '#')) {
			return true;
		}
		if ((grid[Row + 1][Col - 1].GetType() == 'T') || (grid[Row + 1][Col - 1].GetType() == '#')) {
			return true;
		}
		if ((grid[Row + 1][Col].GetType() == 'T') || (grid[Row + 1][Col].GetType() == '#')) {
			return true;
		}
		else { return false; }
	}
	//if cell is the upper right hand corner  

	if ((Row == (grid.size() - 1)) && (Col == (grid[Row].size() - 1))) {
		if ((grid[Row - 1][Col - 1].GetType() == 'T') || (grid[Row - 1][Col - 1].GetType() == '#')) {
			return true;
		}
		if ((grid[Row - 1][Col].GetType() == 'T') || (grid[Row - 1][Col].GetType() == '#')) {
			return true;
		}
		if ((grid[Row][Col - 1].GetType() == 'T') || (grid[Row][Col - 1].GetType() == '#')) {
			return true;
		}
		else { return false; }
	}
	//if cell is in thelower right hand corner

	if (Col == 0) {
		for (int n = -1; n <= 1; n++) {
			if (grid[Row + n][Col].GetType() == 'T' || grid[Row + n][Col].GetType() == '#')
				return true;
			if (grid[Row + n][Col + 1].GetType() == 'T' || grid[Row + n][Col + 1].GetType() == '#')
				return true;
		}
	}
	if (Col == 0) { return false; }
	//if cell is on left edge

	if (Row == 0) {
		for (int n = -1; n <= 1; n++) {
			if ((grid[Row][Col + n].GetType() == 'T') || (grid[Row][Col + n].GetType() == '#'))
				return true;
			if ((grid[Row + 1][Col + n].GetType() == 'T') || (grid[Row + 1][Col + n].GetType() == '#'))
				return true;
		}
	}
	if (Row == 0) { return false; }
	//if cell is on upper edge

	if (Col == (grid[Row].size() - 1)) {
		for (int n = -1; n <= 1; n++) {
			if ((grid[Row + n][Col].GetType() == 'T') || (grid[Row + n][Col].GetType() == '#'))
				return true;
			if ((grid[Row + n][Col - 1].GetType() == 'T') || (grid[Row + n][Col - 1].GetType() == '#'))
				return true;
		}
	}
	if (Col == (grid[Row].size() - 1)) { return false; }
	//if cell is on right edge

	if (Row == (grid.size() - 1)) {
		for (int n = -1; n <= 1; n++) {
			if ((grid[Row - 1][Col + n].GetType() == 'T') || (grid[Row - 1][Col + n].GetType() == '#'))
				return true;
			if ((grid[Row][Col + n].GetType() == 'T') || (grid[Row][Col + n].GetType() == '#'))
				return true;
		}
	}
	if (Row == (grid.size() - 1)) { return false; }
	//if cell is on Bottom edge

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((grid[Row + i][Col + j].GetType() == 'T') || grid[Row + i][Col + j].GetType() == '#')
				return true;
		}
	}//Cell is not on the boundry of the grid
	return false;
}

void ResidentialCell::PopulationZeroC1() {
	if (isPowerlineAdj()) {
		Population += 1;
		Workers += 1;
		AvailableWorkers += 1;
	}
}
void ResidentialCell::PopulationZeroC2() {
	PopulationIncrement(1, 1);
}
void ResidentialCell::PopulationOne() {
	PopulationIncrement(2, 1);
}
void ResidentialCell::PopulationTwo() {
	PopulationIncrement(4, 2);
}
void ResidentialCell::PopulationThree() {
	PopulationIncrement(6, 3);
}
void ResidentialCell::PopulationFour() {
	PopulationIncrement(8, 4);
}
void ResidentialCell::PopulationIncrement(int minCells, int minPopulation) {
	//Population increases 1 if cell is adjacent to at least minCells with at least a pop of minPopulation
	int count = 0;
	bool bl = true;

	if ((Row == 0) && (Col == 0)) {
		bl = false;
		if (grid[Row][Col + 1].GetPopulation() >= minPopulation) {
			++count;
		}
		if (grid[Row + 1][Col].GetPopulation() >= minPopulation) {
			++count;
		}
		if (grid[Row + 1][Col + 1].GetPopulation() >= minPopulation) {
			++count;
		}
	}//if cell is in the upper left hand corner


	if (bl) {
		if ((Row == (grid.size() - 1)) && (Col == 0)) {
			bl = false;
			if (grid[Row - 1][Col].GetPopulation() >= minPopulation) {
				++count;
			}
			if (grid[Row - 1][Col + 1].GetPopulation() >= minPopulation) {
				++count;
			}
			if (grid[Row][Col + 1].GetPopulation() >= minPopulation) {
				++count;
			}
		}
	}//if cell is the lower left hand corner 

	if (bl) {
		if ((Row == 0) && (Col == (grid[Row].size() - 1))) {
			bl = false;
			if (grid[Row][Col - 1].GetPopulation() >= minPopulation) {
				++count;
			}
			if (grid[Row + 1][Col - 1].GetPopulation() >= minPopulation) {
				++count;
			}
			if (grid[Row + 1][Col].GetPopulation() >= minPopulation) {
				++count;
			}
		}
	}//if cell is the upper right hand corner  

	if (bl) {
		if ((Row == (grid.size() - 1)) && (Col == (grid[Row].size() - 1))) {
			bl = false;
			if (grid[Row - 1][Col - 1].GetPopulation() >= minPopulation) {
				++count;
			}
			if (grid[Row - 1][Col].GetPopulation() >= minPopulation) {
				++count;
			}
			if (grid[Row][Col - 1].GetPopulation() >= minPopulation) {
				++count;
			}
		}
	}//if cell is in the lower right hand corner

	if (bl) {
		if (Col == 0) {
			bl = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (grid[Row + n][Col].GetPopulation() >= minPopulation)
						++count;
				}
				if (grid[Row + n][Col + 1].GetPopulation() >= minPopulation)
					++count;
			}
		}
	}//if cell is on left edge

	if (bl) {
		if (Row == 0) {
			bl = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (grid[Row][Col + n].GetPopulation() >= minPopulation)
						++count;
				}
				if (grid[Row + 1][Col + n].GetPopulation() >= minPopulation)
					++count;
			}
		}
	}//if cell is on upper edge

	if (bl) {
		if (Col == (grid[Row].size() - 1)) {
			bl = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (grid[Row + n][Col].GetPopulation() >= minPopulation)
						++count;
				}
				if (grid[Row + n][Col - 1].GetPopulation() >= minPopulation)
					++count;
			}
		}
	}//if cell is on right edge

	if (bl) {
		if (Row == (grid.size() - 1)) {
			bl = false;
			for (int n = -1; n <= 1; n++) {
				if (grid[Row - 1][Col + n].GetPopulation() >= minPopulation)
					++count;
				if (!(n == 0)) {
					if (grid[Row][Col + n].GetPopulation() >= minPopulation)
						++count;
				}
			}
		}
	}//if cell is on Bottom edge

	if (bl) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (!((i == 0) && (j == 0)))
					if (grid[Row + i][Col + j].GetPopulation() >= minPopulation)
						++count;
			}//Cell is not on the boundries of the grid
		}
	}
	if (count >= minCells) {
		AddPopulation();
		AddWorkers();
		AddAvailableWorkers();
	}
}
