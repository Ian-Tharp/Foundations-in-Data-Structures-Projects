#pragma once
#include "baseCell.h"
using namespace std;
class IndustrialCell : public BaseCell {
public:
	std::vector<std::vector<BaseCell> > Grid;

	IndustrialCell();
	IndustrialCell(char type, std::vector<std::vector<BaseCell> > coords);
	std::vector<std::vector<BaseCell> > step(std::vector<std::vector<BaseCell> > Grid);
	int CalcGoods(std::vector<std::vector<BaseCell> > Grid);
	//Pollution
	bool isIndustrialAdj();
	bool isPopulationAdj(int mincells, std::vector<std::vector<BaseCell> > coords);
	bool isPollutionAdj(int minPolcells, std::vector<std::vector<BaseCell> > coords);
	vector<vector<BaseCell> > attemptAddPollution(vector<vector<BaseCell> > coords);

	//Grid operators
	int GetRow();
	int GetCol();
	void SetRow(int row);
	void SetCol(int col);
	bool isPowerlineAdj();
	bool TwoWorkersAvailable(std::vector<std::vector<BaseCell> > Grid);
	bool PopulationIncrement(int minCells, int minPopulation);

protected:
	int Row;
	int Col;


};
