#pragma once
#include "baseCell.h"
using namespace std;

class ResidentialCell : public BaseCell {
public:
	vector<vector<BaseCell> > grid;
	ResidentialCell();
	ResidentialCell(char type, vector<vector<BaseCell> > vect);
	bool isPowerlineAdj();
	void PopulationZeroC1();
	void PopulationIncrement(int minCells, int minPopulation);
	void PopulationZeroC2();
	void PopulationOne();
	void PopulationTwo();
	void PopulationThree();
	void PopulationFour();
	int getRow();
	int getCol();
	void mainCall(vector<vector<BaseCell> > vect);
	void setRow(int row);
	void setCol(int col);

protected:
	int Row;
	int Col;
};
