#pragma once
#include "baseCell.h"
using namespace std;

class CommercialCell : public BaseCell {
public:
	//Public grid variable
	vector<vector<BaseCell> > Grid;
	//Constructors
	CommercialCell();
	CommercialCell(char type, vector<vector<BaseCell> > coords);
	//Check to see if a cell is a powerline and adjacent to the cell
	bool isPowerlineAdj();
	//Check to see if a cell is population adjacent to the cell
	bool isPopulationAdj(int minCells, vector<vector<BaseCell> > coords);

	//Timestep function
	vector<vector<BaseCell> > TryToAddPopulation(vector<vector<BaseCell> > coords);

	//Grid operators
	void SetGrid(vector<vector<BaseCell> > coords);
	int GetRow();
	int GetCol();
	void SetRow(int row);
	void SetCol(int col);

protected:
	int Row;
	int Col;
};
