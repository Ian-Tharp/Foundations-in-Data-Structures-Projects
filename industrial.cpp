#include <iostream>
#include "industrial.h"
using namespace std;
IndustrialCell::IndustrialCell() {
	Population = 0;
	Workers = 0;
	Goods = 0;
	Pollution = 0;
	Type = 'I';
	Row = 0;
	Col = 0;
}

IndustrialCell::IndustrialCell(char type, std::vector<std::vector<BaseCell> > coords)
{
	Type = type;
	Grid = coords;
}

//Sets
void IndustrialCell::SetRow(int row) { Row = row; }
void IndustrialCell::SetCol(int col) { Col = col; }
//Gets
int IndustrialCell::GetRow() { return Row; }
int IndustrialCell::GetCol() { return Col; }

bool IndustrialCell::isPowerlineAdj() {

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
	}//Cell is not on the boundry of the Grid
	return false;
}

bool IndustrialCell::TwoWorkersAvailable(std::vector<std::vector<BaseCell> > Grid) {
	int count = 0;
	int temp = 0;
	for (int i = 0; i < Grid.size(); i++) {
		for (int j = 0; j < Grid[i].size(); j++) {
			temp = Grid[i][j].GetAvailableWorkers();
			count += temp;
			temp = 0;
		}
	}
	if (count >= 2) {
		return true;
	}

	else return false;
}

bool IndustrialCell::PopulationIncrement(int minCells, int minPopulation) {
	//Population increases 1 if cell is adjacent to at least minCells with at least a pop of minPopulation
	int count = 0;
	bool bl = true;

	if ((Row == 0) && (Col == 0)) {
		bl = false;
		if (Grid[Row][Col + 1].GetPopulation() >= minPopulation) {
			++count;
		}
		if (Grid[Row + 1][Col].GetPopulation() >= minPopulation) {
			++count;
		}
		if (Grid[Row + 1][Col + 1].GetPopulation() >= minPopulation) {
			++count;
		}
	}//if cell is in the upper left hand corner


	if (bl) {
		if ((Row == (Grid.size() - 1)) && (Col == 0)) {
			bl = false;
			if (Grid[Row - 1][Col].GetPopulation() >= minPopulation) {
				++count;
			}
			if (Grid[Row - 1][Col + 1].GetPopulation() >= minPopulation) {
				++count;
			}
			if (Grid[Row][Col + 1].GetPopulation() >= minPopulation) {
				++count;
			}
		}
	}//if cell is the lower left hand corner 

	if (bl) {
		if ((Row == 0) && (Col == (Grid[Row].size() - 1))) {
			bl = false;
			if (Grid[Row][Col - 1].GetPopulation() >= minPopulation) {
				++count;
			}
			if (Grid[Row + 1][Col - 1].GetPopulation() >= minPopulation) {
				++count;
			}
			if (Grid[Row + 1][Col].GetPopulation() >= minPopulation) {
				++count;
			}
		}
	}//if cell is the upper right hand corner  

	if (bl) {
		if ((Row == (Grid.size() - 1)) && (Col == (Grid[Row].size() - 1))) {
			bl = false;
			if (Grid[Row - 1][Col - 1].GetPopulation() >= minPopulation) {
				++count;
			}
			if (Grid[Row - 1][Col].GetPopulation() >= minPopulation) {
				++count;
			}
			if (Grid[Row][Col - 1].GetPopulation() >= minPopulation) {
				++count;
			}
		}
	}//if cell is in the lower right hand corner

	if (bl) {
		if (Col == 0) {
			bl = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (Grid[Row + n][Col].GetPopulation() >= minPopulation)
						++count;
				}
				if (Grid[Row + n][Col + 1].GetPopulation() >= minPopulation)
					++count;
			}
		}
	}//if cell is on left edge

	if (bl) {
		if (Row == 0) {
			bl = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (Grid[Row][Col + n].GetPopulation() >= minPopulation)
						++count;
				}
				if (Grid[Row + 1][Col + n].GetPopulation() >= minPopulation)
					++count;
			}
		}
	}//if cell is on upper edge

	if (bl) {
		if (Col == (Grid[Row].size() - 1)) {
			bl = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (Grid[Row + n][Col].GetPopulation() >= minPopulation)
						++count;
				}
				if (Grid[Row + n][Col - 1].GetPopulation() >= minPopulation)
					++count;
			}
		}
	}//if cell is on right edge

	if (bl) {
		if (Row == (Grid.size() - 1)) {
			bl = false;
			for (int n = -1; n <= 1; n++) {
				if (Grid[Row - 1][Col + n].GetPopulation() >= minPopulation)
					++count;
				if (!(n == 0)) {
					if (Grid[Row][Col + n].GetPopulation() >= minPopulation)
						++count;
				}
			}
		}
	}//if cell is on Bottom edge

	if (bl) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (!((i == 0) && (j == 0)))
					if (Grid[Row + i][Col + j].GetPopulation() >= minPopulation)
						++count;
			}//Cell is not on the boundries of the Grid
		}
	}
	if (count >= minCells) {
		return true;
	}
	else return false;
}

std::vector<std::vector<BaseCell> > IndustrialCell::step(std::vector<std::vector<BaseCell> > coords) {
	Grid = coords;
	bool bl = true;
	int WorkersTaken = 0;;

	//1st bullet point
	if (bl) {
		if ((Population == 0) && (isPowerlineAdj()) && (TwoWorkersAvailable(Grid))) {
			bl = false;
			AddPopulation();
			AddGoods();
			for (int i = 0; i < Grid.size(); i++) {
				for (int j = 0; j < Grid[i].size(); j++) {
					if (Grid[i][j].GetType() == 'R') {
						if (Grid[i][j].GetAvailableWorkers() >= 1) {
							Grid[i][j].takeAvailableWorkers(1);
							++WorkersTaken;
							if (WorkersTaken == 2)
								break;
						}
					}
				}
			}
		}
	}

	//2nd bullet point
	if (bl) {
		if ((Population == 0) && (PopulationIncrement(1, 1)) && (TwoWorkersAvailable(Grid))) {
			bl = false;
			AddPopulation();
			AddGoods();
			for (int i = 0; i < Grid.size(); i++) {
				for (int j = 0; j < Grid[i].size(); j++) {
					if (Grid[i][j].GetType() == 'R') {
						if (Grid[i][j].GetAvailableWorkers() >= 1) {
							Grid[i][j].takeAvailableWorkers(1);
							++WorkersTaken;
							if (WorkersTaken == 2)
								break;
						}
					}
				}
			}
		}
	}

	//3rd bullet point
	if (bl) {
		if ((Population == 1) && (PopulationIncrement(2, 1)) && (TwoWorkersAvailable(Grid))) {
			bl = false;
			AddPopulation();
			AddGoods();
			for (int i = 0; i < Grid.size(); i++) {
				for (int j = 0; j < Grid[i].size(); j++) {
					if (Grid[i][j].GetType() == 'R') {
						if (Grid[i][j].GetAvailableWorkers() >= 1) {
							Grid[i][j].takeAvailableWorkers(1);
							++WorkersTaken;
							if (WorkersTaken == 2)
								break;
						}
					}
				}
			}
		}
	}

	//4th bullet point 
	if (bl) {
		if ((Population == 2) && (PopulationIncrement(4, 2)) && (TwoWorkersAvailable(Grid))) {
			bl = false;
			AddPopulation();
			AddGoods();
			for (int i = 0; i < Grid.size(); i++) {
				for (int j = 0; j < Grid[i].size(); j++) {
					if (Grid[i][j].GetType() == 'R') {
						if (Grid[i][j].GetAvailableWorkers() >= 1) {
							Grid[i][j].takeAvailableWorkers(1);
							++WorkersTaken;
							if (WorkersTaken == 2)
								break;
						}
					}
				}
			}
		}
	}

	return Grid;

}
int IndustrialCell::CalcGoods(std::vector<std::vector<BaseCell> > Grid) {
	int temp = 0;
	int goods = 0;
	for (int i = 0; i < Grid.size(); i++) {
		for (int j = 0; j < Grid[i].size(); j++) {
			temp = Grid[i][j].GetGoods();
			goods += temp;
			temp = 0;
		}
	}
	return goods;
}






// Pollution



//Check where industrial cells are
bool IndustrialCell::isIndustrialAdj()
{
	if ((Row == 0) && (Col == 0)) {
		if (Grid[Row][Col + 1].GetType() == 'I') {
			return true;
		}
		if (Grid[Row + 1][Col].GetType() == 'I') {
			return true;
		}
		if (Grid[Row + 1][Col + 1].GetType() == 'I') {
			return true;
		}
		else { return false; }
	}
	//if cell is in the upper left hand corner
	if ((Row == (Grid.size() - 1)) && (Col == 0)) {
		if (Grid[Row - 1][Col].GetType() == 'I') {
			return true;
		}
		if (Grid[Row - 1][Col + 1].GetType() == 'I') {
			return true;
		}
		if (Grid[Row][Col + 1].GetType() == 'I') {
			return true;
		}
		else { return false; }
	}
	//if cell is the lower left hand corner 

	if ((Row == 0) && (Col == (Grid[Row].size() - 1))) {
		if (Grid[Row][Col - 1].GetType() == 'I') {
			return true;
		}
		if (Grid[Row + 1][Col - 1].GetType() == 'I') {
			return true;
		}
		if (Grid[Row + 1][Col].GetType() == 'I') {
			return true;
		}
		else { return false; }
	}
	//if cell is the upper right hand corner  

	if ((Row == (Grid.size() - 1)) && (Col == (Grid[Row].size() - 1))) {
		if (Grid[Row - 1][Col - 1].GetType() == 'I') {
			return true;
		}
		if (Grid[Row - 1][Col].GetType() == 'I') {
			return true;
		}
		if (Grid[Row][Col - 1].GetType() == 'I') {
			return true;
		}
		else { return false; }
	}
	//if cell is in thelower right hand corner

	if (Col == 0) {
		for (int n = -1; n <= 1; n++) {
			if (Grid[Row + n][Col].GetType() == 'I')
				return true;
			if (Grid[Row + n][Col + 1].GetType() == 'I')
				return true;
		}
	}
	if (Col == 0) { return false; }
	//if cell is on left edge

	if (Row == 0) {
		for (int n = -1; n <= 1; n++) {
			if (Grid[Row][Col + n].GetType() == 'I')
				return true;
			if (Grid[Row + 1][Col + n].GetType() == 'I')
				return true;
		}
	}
	if (Row == 0) { return false; }
	//if cell is on upper edge

	if (Col == (Grid[Row].size() - 1)) {
		for (int n = -1; n <= 1; n++) {
			if (Grid[Row + n][Col].GetType() == 'I')
				return true;
			if (Grid[Row + n][Col - 1].GetType() == 'I')
				return true;
		}
	}
	if (Col == (Grid[Row].size() - 1)) { return false; }
	//if cell is on right edge

	if (Row == (Grid.size() - 1)) {
		for (int n = -1; n <= 1; n++) {
			if (Grid[Row - 1][Col + n].GetType() == 'I')
				return true;
			if (Grid[Row][Col + n].GetType() == 'I')
				return true;
		}
	}
	if (Row == (Grid.size() - 1)) { return false; }
	//if cell is on Bottom edge

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (Grid[Row + i][Col + j].GetType() == 'I')
				return true;
		}
	}//Cell does not exist on the grid
	return false;
}



// Check for population adjacent to industrial cells
bool IndustrialCell::isPopulationAdj(int minCells, vector<vector<BaseCell> > coords)
{
	int count = 0;
	bool temp = true;

	if ((Row == 0) && (Col == 0)) {
		temp = false;
		if (Grid[Row][Col + 1].GetPopulation() == 1) {
			++count;
		}
		if (Grid[Row + 1][Col].GetPopulation() == 1) {
			++count;
		}
		if (Grid[Row + 1][Col + 1].GetPopulation() == 1) {
			++count;
		}
	}//if cell is in the upper left hand corner

	if (temp) {
		if ((Row == (Grid.size() - 1)) && (Col == 0)) {
			temp = false;
			if (Grid[Row - 1][Col].GetPopulation() == 1) {
				++count;
			}
			if (Grid[Row - 1][Col + 1].GetPopulation() == 1) {
				++count;
			}
			if (Grid[Row][Col + 1].GetPopulation() == 1) {
				++count;
			}
		}
	}//if cell is the lower left hand corner 

	if (temp) {
		if ((Row == 0) && (Col == (Grid[Row].size() - 1))) {
			temp = false;
			if (Grid[Row][Col - 1].GetPopulation() == 1) {
				++count;
			}
			if (Grid[Row + 1][Col - 1].GetPopulation() == 1) {
				++count;
			}
			if (Grid[Row + 1][Col].GetPopulation() == 1) {
				++count;
			}
		}
	}//if cell is the upper right hand corner  

	if (temp) {
		if ((Row == (Grid.size() - 1)) && (Col == (Grid[Row].size() - 1))) {
			temp = false;
			if (Grid[Row - 1][Col - 1].GetPopulation() == 1) {
				++count;
			}
			if (Grid[Row - 1][Col].GetPopulation() == 1) {
				++count;
			}
			if (Grid[Row][Col - 1].GetPopulation() == 1) {
				++count;
			}
		}
	}//if cell is in the lower right hand corner

	if (temp) {
		if (Col == 0) {
			temp = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (Grid[Row + n][Col].GetPopulation() == 1)
						++count;
				}
				if (Grid[Row + n][Col + 1].GetPopulation() == 1)
					++count;
			}
		}
	}//if cell is on left edge

	if (temp) {
		if (Row == 0) {
			temp = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (Grid[Row][Col + n].GetPopulation() == 1)
						++count;
				}
				if (Grid[Row + 1][Col + n].GetPopulation() == 1)
					++count;
			}
		}
	}//if cell is on upper edge

	if (temp) {
		if (Col == (Grid[Row].size() - 1)) {
			temp = false;
			for (int n = -1; n <= 1; n++) {
				if (!(n == 0)) {
					if (Grid[Row + n][Col].GetPopulation() == 1)
						++count;
				}
				if (Grid[Row + n][Col - 1].GetPopulation() == 1)
					++count;
			}
		}
	}//if cell is on right edge

	if (temp) {
		if (Row == (Grid.size() - 1)) {
			temp = false;
			for (int n = -1; n <= 1; n++) {
				if (Grid[Row - 1][Col + n].GetPopulation() == 1)
					++count;
				if (!(n == 0)) {
					if (Grid[Row][Col + n].GetPopulation() == 1)
						++count;
				}
			}
		}
	}//if cell is on bottom edge

	if (temp) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (!((i == 0) && (j == 0)))
					if (Grid[Row + i][Col + j].GetPopulation() == 1)
						++count;
			}//Cell is not on the boundries of the grid
		}
	}
	if (count >= minCells) {
		cout << "Count True" << endl;
		++Pollution;
		return true;
	}
	else {
		//cout << "Count False" << endl;
		return false;
	}
}



// Check if pollution is > 1, if so spread the pollution
bool IndustrialCell::isPollutionAdj(int minPolCells, vector<vector<BaseCell> > coords)
{
	int counter = 0;


	if ((Row == 0) && (Col == 0)) {
		if (Grid[Row][Col + 1].GetPollution() >= 2) {
			++counter;
		}
		if (Grid[Row + 1][Col].GetPollution() >= 2) {
			++counter;
		}
		if (Grid[Row + 1][Col + 1].GetPollution() >= 2) {
			++counter;
		}
	}//if cell is in the upper left hand corner

	if ((Row == (Grid.size() - 1)) && (Col == 0)) {
		if (Grid[Row - 1][Col].GetPollution() >= 2) {
			++counter;
		}
		if (Grid[Row - 1][Col + 1].GetPollution() >= 2) {
			++counter;
		}
		if (Grid[Row][Col + 1].GetPollution() >= 2) {
			++counter;
		}
	}//if cell is the lower left hand corner

	if ((Row == 0) && (Col == (Grid[Row].size() - 1))) {
		if (Grid[Row][Col - 1].GetPollution() >= 2) {
			++counter;
		}
		if (Grid[Row + 1][Col - 1].GetPollution() >= 2) {
			++counter;
		}
		if (Grid[Row + 1][Col].GetPollution() >= 2) {
			++counter;
		}
	}//if cell is the upper right hand corner

	if ((Row == (Grid.size() - 1)) && (Col == (Grid[Row].size() - 1))) {
		if (Grid[Row - 1][Col - 1].GetPollution() >= 2) {
			++counter;
		}
		if (Grid[Row - 1][Col].GetPollution() >= 2) {
			++counter;
		}
		if (Grid[Row][Col - 1].GetPollution() >= 2) {
			++counter;
		}
	}//if cell is in the lower right hand corner

	if (Col == 0) {
		for (int n = -1; n <= 1; n++) {
			if (!(n == 0)) {
				if (Grid[Row + n][Col].GetPollution() >= 2)
					++counter;
			}
			if (Grid[Row + n][Col + 1].GetPollution() >= 2)
				++counter;
		}
	}//if cell is on left edge

	if (Row == 0) {
		for (int n = -1; n <= 1; n++) {
			if (!(n == 0)) {
				if (Grid[Row][Col + n].GetPollution() >= 2)
					++counter;
			}
			if (Grid[Row + 1][Col + n].GetPollution() >= 2)
				++counter;
		}
	}//if cell is on upper edge

	if (Col == (Grid[Row].size() - 1)) {
		for (int n = -1; n <= 1; n++) {
			if (!(n == 0)) {
				if (Grid[Row + n][Col].GetPollution() >= 2)
					++counter;
			}
			if (Grid[Row + n][Col - 1].GetPollution() >= 2)
				++counter;
		}
	}//if cell is on right edge

	if (Row == (Grid.size() - 1)) {
		for (int n = -1; n <= 1; n++) {
			if (Grid[Row - 1][Col + n].GetPollution() >= 2)
				++counter;
			if (!(n == 0)) {
				if (Grid[Row][Col + n].GetPollution() >= 2)
					++counter;
			}
		}
	}//if cell is on bottom edge

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!((i == 0) && (j == 0)))
				if (Grid[Row + i][Col + j].GetPollution() >= 2)
					++counter;
		}//Cell is not on the boundries of the grid
	}
	if (counter >= minPolCells) {
		return true;
	}
	else {
		return false;
	}
}





// Step Function
vector<vector<BaseCell> > IndustrialCell::attemptAddPollution(vector<vector<BaseCell> > coords)
{
	int population = IndustrialCell::GetPopulation();
	int pollution = 0;
	int counter = 0;
	int temp = 0;


	for (int i = 0; i < coords.size(); i++) {
		for (int j = 0; j < coords[i].size(); j++) {
			temp = coords[i][j].GetPopulation();
			pollution += temp;
			temp = 0;
		}
	}

	bool IndustryAdj = isIndustrialAdj();
	bool PopulationAdj = PopulationIncrement(1, 1);
	bool PollutionAdj = isPollutionAdj(1, coords);
	bool running = true;
	bool running2 = true;


	// Adds pollution to the vector when the pollution is equal to 1.
	if (running) {
		if (PopulationIncrement(1, 1) == true) {
			for (int i = 0; i < coords.size(); i++) {
				for (int j = 0; j < coords.size(); j++) {
					if (coords[i][j].GetType() == 'I') {
						if (coords[i][j].GetPopulation() >= 1) {
							coords[i][j].AddPollution();
						}
					}
				}
			}
			AddPollution();
			--pollution;
			running = false;
		}
	}

	// When pollution is greater than 1 it will spread.
	if (running2) {
		if (PopulationIncrement(1, 1) == true) {
			if (isPollutionAdj(1, coords) == true) {
				for (int i = 0; i < coords.size(); i++) {
					for (int j = 0; j < coords.size(); j++) {
						if (coords[i][j].GetType() == 'I') {
							if (coords[i][j].GetPopulation() >= 2) {
								coords[i][j].AddPollution();
							}
						}
					}
				}
				AddPollution();
				--pollution;
				running2 = false;
			}
		}
	}

	return coords;
}