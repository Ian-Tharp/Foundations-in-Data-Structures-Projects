#include "baseCell.h"
using namespace std;

//Default constructor
BaseCell::BaseCell()
{
	Population = 0;
	Workers = 0;
	AvailableWorkers = 0;
	Goods = 0;
	Pollution = 0;
	Type = 'X';
}
//Parameterized constructor
BaseCell::BaseCell(int population, int workers, int goods, int pollution, char type)
{
	Population = population;
	Workers = workers;
	Goods = goods;
	Pollution = pollution;
	Type = type;

}

void BaseCell::AddPopulation() { ++Population; }
void BaseCell::AddWorkers() { ++Workers; }
void BaseCell::AddGoods() { ++Goods; }
void BaseCell::AddPollution() { ++Pollution; }
void BaseCell::AddAvailableWorkers() { ++AvailableWorkers; }

void BaseCell::ChangeType(char type)
{
	Type = type;
}

//Sets
void BaseCell::SetPopulation(int population) { Population = population; }
void BaseCell::SetWorkers(int workers) { Workers = workers; }
void BaseCell::SetGoods(int goods) { Goods = goods; }
void BaseCell::SetPollution(int pollution) { Pollution = pollution; }
//Gets
int BaseCell::GetPopulation() { return Population; }
int BaseCell::GetWorkers() { return Workers; }
int BaseCell::GetAvailableWorkers() { return AvailableWorkers; }
int BaseCell::GetGoods() { return Goods; }
int BaseCell::GetPollution() { return Pollution; }
char BaseCell::GetType() { return Type; }

void BaseCell::takeAvailableWorkers(int workersToTake) {
	AvailableWorkers -= workersToTake;
	if (AvailableWorkers < 0) {
		cout << "error: Employed too many workers from a single cell" << endl;
	}
}
