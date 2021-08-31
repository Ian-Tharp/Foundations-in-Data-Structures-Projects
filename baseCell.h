#pragma once
#include <iostream>
#include <vector>

class BaseCell
{
public:
	BaseCell();
	BaseCell(int population, int workers, int goods, int pollution, char type);

	void AddPopulation();
	void AddWorkers();
	void AddGoods();
	void AddPollution();
	void AddAvailableWorkers();

	void ChangeType(char type);

	//Sets
	void SetPopulation(int population);
	void SetWorkers(int workers);
	void SetGoods(int goods);
	void SetPollution(int pollution);
	//Gets
	int GetPopulation();
	int GetWorkers();
	int GetAvailableWorkers();
	int GetGoods();
	int GetPollution();
	char GetType();

	void takeAvailableWorkers(int workersToTake);

protected:
	int Population;
	int Workers;
	int AvailableWorkers;
	int Goods;
	int Pollution;
	char Type;
};
