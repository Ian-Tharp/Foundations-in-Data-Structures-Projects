#include "commercial.h"
using namespace std;
//Default constructor
CommercialCell::CommercialCell() {
	Population = 0;
	Workers = Population;
	Goods = 0;
	Pollution = 0;
	Type = 'C';
	Row = 0;
	Col = 0;
}
//Parameterized constructor
CommercialCell::CommercialCell(char type, vector<vector<BaseCell> > coords) {
	Type = type;
	Grid = coords;
}

//Sets
void CommercialCell::SetRow(int row) { Row = row; }
void CommercialCell::SetCol(int col) { Col = col; }
void CommercialCell::SetGrid(vector<vector<BaseCell> > grid) { Grid = grid; }
//Gets
int CommercialCell::GetRow() { return Row; }
int CommercialCell::GetCol() { return Col; }

//Check if there are any powerlines adjacent to commercial cell
bool CommercialCell::isPowerlineAdj()
{
	if ((Row == 0) && (Col == 0)) {
		if ((Grid[Row][Col + 1].GetType() == 'T') || (Grid[Row][Col + 1].GetType() == '#')) {
			return true;
		}
		if ((Grid[Row + 1][Col].GetType() == 'T') || (Grid[Row + 1][Col].GetType() == '#')) {
			return true;
		}
		if ((Grid[Row + 1][Col + 1].GetType() == 'T') || (Grid[Row + 1][Col + 1].GetType() == '#')) {
			return true;
		}
		else { return false; }
	}
	//if cell is in the upper left hand corner
	if ((Row == (Grid.size() - 1)) && (Col == 0)) {
		if ((Grid[Row - 1][Col].GetType() == 'T') || (Grid[Row - 1][Col].GetType() == '#')) {
			return true;
		}
		if ((Grid[Row - 1][Col + 1].GetType() == 'T') || (Grid[Row - 1][Col + 1].GetType() == '#')) {
			return true;
		}
		if ((Grid[Row][Col + 1].GetType() == 'T') || (Grid[Row][Col + 1].GetType() == '#')) {
			return true;
		}
		else { return false; }
	}
	//if cell is the lower left hand corner 

	if ((Row == 0) && (Col == (Grid[Row].size() - 1))) {
		if ((Grid[Row][Col - 1].GetType() == 'T') || (Grid[Row][Col - 1].GetType() == '#')) {
			return true;
		}
		if ((Grid[Row + 1][Col - 1].GetType() == 'T') || (Grid[Row + 1][Col - 1].GetType() == '#')) {
			return true;
		}
		if ((Grid[Row + 1][Col].GetType() == 'T') || (Grid[Row + 1][Col].GetType() == '#')) {
			return true;
		}
		else { return false; }
	}
	//if cell is the upper right hand corner  

	if ((Row == (Grid.size() - 1)) && (Col == (Grid[Row].size() - 1))) {
		if ((Grid[Row - 1][Col - 1].GetType() == 'T') || (Grid[Row - 1][Col - 1].GetType() == '#')) {
			return true;
		}
		if ((Grid[Row - 1][Col].GetType() == 'T') || (Grid[Row - 1][Col].GetType() == '#')) {
			return true;
		}
		if ((Grid[Row][Col - 1].GetType() == 'T') || (Grid[Row][Col - 1].GetType() == '#')) {
			return true;
		}
		else { return false; }
	}
	//if cell is in thelower right hand corner

	if (Col == 0) {
		for (int n = -1; n <= 1; n++) {
			if (Grid[Row + n][Col].GetType() == 'T' || Grid[Row + n][Col].GetType() == '#')
				return true;
			if (Grid[Row + n][Col + 1].GetType() == 'T' || Grid[Row + n][Col + 1].GetType() == '#')
				return true;
		}
	}
	if (Col == 0) { return false; }
	//if cell is on left edge

	if (Row == 0) {
		for (int n = -1; n <= 1; n++) {
			if ((Grid[Row][Col + n].GetType() == 'T') || (Grid[Row][Col + n].GetType() == '#'))
				return true;
			if ((Grid[Row + 1][Col + n].GetType() == 'T') || (Grid[Row + 1][Col + n].GetType() == '#'))
				return true;
		}
	}
	if (Row == 0) { return false; }
	//if cell is on upper edge

	if (Col == (Grid[Row].size() - 1)) {
		for (int n = -1; n <= 1; n++) {
			if ((Grid[Row + n][Col].GetType() == 'T') || (Grid[Row + n][Col].GetType() == '#'))
				return true;
			if ((Grid[Row + n][Col - 1].GetType() == 'T') || (Grid[Row + n][Col - 1].GetType() == '#'))
				return true;
		}
	}
	if (Col == (Grid[Row].size() - 1)) { return false; }
	//if cell is on right edge

	if (Row == (Grid.size() - 1)) {
		for (int n = -1; n <= 1; n++) {
			if ((Grid[Row - 1][Col + n].GetType() == 'T') || (Grid[Row - 1][Col + n].GetType() == '#'))
				return true;
			if ((Grid[Row][Col + n].GetType() == 'T') || (Grid[Row][Col + n].GetType() == '#'))
				return true;
		}
	}
	if (Row == (Grid.size() - 1)) { return false; }
	//if cell is on Bottom edge

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((Grid[Row + i][Col + j].GetType() == 'T') || Grid[Row + i][Col + j].GetType() == '#')
				return true;
		}
	}//Cell is not on the boundry of the grid
	return false;
}

//Check if there are any cells with a given population adjacent to commercial cell
bool CommercialCell::isPopulationAdj(int minCells, vector<vector<BaseCell> > coords)
{
	int count = 0;
	bool temp = true;

	if ((Row == 0) && (Col == 0)) {
		temp = false;
		if (coords[Row][Col + 1].GetPopulation() == 1) {
			++count;
		}
		if (coords[Row + 1][Col].GetPopulation() == 1) {
			++count;
		}
		if (coords[Row + 1][Col + 1].GetPopulation() == 1) {
			++count;
		}
	}//if cell is in the upper left hand corner

	if (temp) {
		if ((Row == (coords.size() - 1)) && (Col == 0)) {
			temp = false;
			if (coords[Row - 1][Col].GetPopulation() == 1) {
				++count;
			}
			if (coords[Row - 1][Col + 1].GetPopulation() == 1) {
				++count;
			}
			if (coords[Row][Col + 1].GetPopulation() == 1) {
				++count;
			}
		}
	}//if cell is the lower left hand corner 

	if (temp) {
		if ((Row == 0) && (Col == (coords[Row].size() - 1))) {
			temp = false;
			if (coords[Row][Col - 1].GetPopulation() == 1) {
				++count;
			}
			if (coords[Row + 1][Col - 1].GetPopulation() == 1) {
				++count;
			}
			if (coords[Row + 1][Col].GetPopulation() == 1) {
				++count;
			}
		}
	}//if cell is the upper right hand corner  

	if (temp) {
		if ((Row == (coords.size() - 1)) && (Col == (coords[Row].size() - 1))) {
			temp = false;
			if (coords[Row - 1][Col - 1].GetPopulation() == 1) {
				++count;
			}
			if (coords[Row - 1][Col].GetPopulation() == 1) {
				++count;
			}
			if (coords[Row][Col - 1].GetPopulation() == 1) {
				++count;
			}
		}
	}//if cell is in the lower right hand corner

	if (temp) {
		if (Col == 0) {
			temp = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (coords[Row + n][Col].GetPopulation() == 1)
						++count;
				}
				if (coords[Row + n][Col + 1].GetPopulation() == 1)
					++count;
			}
		}
	}//if cell is on left edge

	if (temp) {
		if (Row == 0) {
			temp = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (coords[Row][Col + n].GetPopulation() == 1)
						++count;
				}
				if (coords[Row + 1][Col + n].GetPopulation() == 1)
					++count;
			}
		}
	}//if cell is on upper edge

	if (temp) {
		if (Col == (coords[Row].size() - 1)) {
			temp = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (coords[Row + n][Col].GetPopulation() == 1)
						++count;
				}
				if (coords[Row + n][Col - 1].GetPopulation() == 1)
					++count;
			}
		}
	}//if cell is on right edge

	if (temp) {
		if (Row == (coords.size() - 1)) {
			temp = false;
			for (int n = -1; n <= 1; n++) {
				if (coords[Row - 1][Col + n].GetPopulation() == 1)
					++count;
				if (!(n == 0)) {
					if (coords[Row][Col + n].GetPopulation() == 1)
						++count;
				}
			}
		}
	}//if cell is on bottom edge

	if (temp) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (!((i == 0) && (j == 0)))
					if (coords[Row + i][Col + j].GetPopulation() == 1)
						++count;
			}//Cell is not on the boundries of the grid
		}
	}
	if (count >= minCells) {
		return true;
	}
	else {
		return false;
	}
}

//Function to be run at every time step
vector<vector<BaseCell> > CommercialCell::TryToAddPopulation(vector<vector<BaseCell> > coords)
{
	int population = CommercialCell::GetPopulation();
	int workers = 0;
	int temp = 0;
	int goods = 0;
	int count = 0;
	bool running = true;
	bool running2 = true;

	//Check entire grid for available workers
	for (int i = 0; i < coords.size(); i++) {
		for (int j = 0; j < coords[i].size(); j++) {
			temp = coords[i][j].GetAvailableWorkers();
			workers += temp;
			temp = 0;
		}
	}
	//Check entire grid for available goods
	for (int i = 0; i < coords.size(); i++) {
		for (int j = 0; j < coords[i].size(); j++) {
			temp = coords[i][j].GetGoods();
			goods += temp;
			temp = 0;
		}
	}

	//First & second bullet points check if pop is 0
	if (running) {
		if (CommercialCell::GetPopulation() == 0) {
			if (isPowerlineAdj() == true || isPopulationAdj(1, coords) == true) {
				if (workers >= 1 && goods >= 1) {
					for (int i = 0; i < coords.size(); i++) {
						for (int j = 0; j < coords[i].size(); j++) {
							if (coords[i][j].GetType() == 'R') {
								if (coords[i][j].GetAvailableWorkers() >= 1) {
									coords[i][j].takeAvailableWorkers(1);
								}
							}
						}
					}
					AddPopulation();
					--goods;
					running = false;
				}
				else if (isPopulationAdj(1, coords) == true) {
					if (workers >= 1 && goods >= 1) {
						for (int i = 0; i < coords.size(); i++) {
							for (int j = 0; j < coords[i].size(); j++) {
								if (coords[i][j].GetAvailableWorkers() >= 1) {
									coords[i][j].takeAvailableWorkers(1);
								}
							}
						}
						AddPopulation();
						--goods;
						running = false;
					}
				}
			}
		}
	}
	//Separate if statement to reduce repitition in population
	if (running2) {
		//Third bullet point check if population is 1
		if (CommercialCell::GetPopulation() == 1) {
			if (isPopulationAdj(2, coords)) {
				if (workers >= 1 && goods >= 1) {
					for (int i = 0; i < coords.size(); i++) {
						for (int j = 0; j < coords[i].size(); j++) {
							if (coords[i][j].GetType() == 'R') {
								if (coords[i][j].GetAvailableWorkers() >= 1) {
									coords[i][j].takeAvailableWorkers(1);
								}
							}
						}
					}
					AddPopulation();
					--goods;
					running2 = false;
				}
			}
		}
	}
	return coords;
}
