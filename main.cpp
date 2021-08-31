#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include "baseCell.h"
#include "commercial.h"
#include "industrial.h"
#include "residential.h"
using namespace std;

//Global variables
int TimeLimit, RefreshRate;

//First function to read in file and populate 2D vector
vector<vector<BaseCell> > ReadInFile() {
	vector<vector<BaseCell> > vect;
	ifstream fin1, fin2;
	bool fileReading1 = true;
	bool fileReading2 = true;

	//Config file variables
	string configFile;
	string lines, csvName, temp;
	int timeLimit, refreshRate;

	while (fileReading1)
	{
		cout << "Enter name of the configuration file: ";
		getline(cin, configFile);

		fin1.open(configFile);

		if (fin1.fail())
		{
			cout << "Error in reading file." << endl;
			cout << "Please try again." << endl;
			cout << endl;
			fileReading1 = true;
		}
		else {
			cout << "Initializing..." << endl;
			cout << "Beginning simulation." << endl;

			bool reading1 = true, reading2 = true, reading3 = true;

			//Reading in and setting variables from initial config file
			while (!fin1.eof())
			{
				getline(fin1, lines);
				//Region layout csv file
				if (reading1 == true)
				{
					lines = lines.substr(14);
					csvName = lines;
					reading1 = false;
				}
				//Time Limit
				else if (reading2 == true)
				{
					lines = lines.substr(11);
					timeLimit = stoi(lines);
					TimeLimit = timeLimit;
					reading2 = false;
				}
				//Refresh Rate
				else if (reading3 == true)
				{
					lines = lines.substr(13);
					refreshRate = stoi(lines);
					RefreshRate = refreshRate;
					reading3 = false;
				}
			}
			fin1.close();
			fileReading1 = false;
		}
	}

	while (fileReading2)
	{
		fin2.open(csvName);
		//Test to check if .csv file from config actually gets read in
		if (fin2.fail())
		{
			cout << "Error in reading .csv file." << endl;
			fileReading2 = false;
			exit(1);
		}
		else
		{
			fileReading2 = false;
			int n = 0;
			char ch;
			vector<BaseCell> sVect;
			while (!fin2.eof())
			{
				fin2.get(ch);

				if ((ch != ',') && (ch != '\n')) {
					BaseCell bc;
					sVect.push_back(bc);
					sVect[n].ChangeType(ch);
					n++;
				}
				if (ch == ',') {
					fin2.get(ch);
					BaseCell bc;
					sVect.push_back(bc);
					sVect[n].ChangeType(ch);
					n++;
				}
				if (ch == '\n') {
					vect.push_back(sVect);
					sVect.clear();
					n = 0;
				}
			}
		}
	}
	fin2.close();
	return vect;
}

//Global Variable
vector<vector<BaseCell> > vect = ReadInFile();

//Print out the grid and display population if any
void Timestep()
{
	//Print out grid
	for (int i = 0; i < (vect[0].size() * 2) + 2; i++) {
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < vect.size(); i++) {
		cout << "|";
		for (int j = 0; j < vect[i].size(); j++) {
			if (vect[i][j].GetPopulation() >= 1) {
				cout << vect[i][j].GetPopulation() << " ";
			}
			else {
				cout << vect[i][j].GetType() << " ";
			}
		}
		cout << "|" << endl;
	}
	for (int i = 0; i < (vect[0].size() * 2) + 2; i++) {
		cout << "-";
	}
	cout << endl; cout << endl;
}

//Print out initial grid from file
void InitialGrid()
{
	//Output inital grid
	cout << "Initial Region State\n";
	for (int i = 0; i < (vect[0].size() * 2) + 2; i++) {
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < vect.size(); i++) {
		cout << "|";
		for (int j = 0; j < vect[i].size(); j++) {
			cout << vect[i][j].GetType() << " ";
		}
		cout << "|" << endl;
	}
	for (int i = 0; i < (vect[0].size() * 2) + 2; i++) {
		cout << "-";
	}
	cout << endl; cout << endl;
}

int main()
{
	//1D vector declarations
	vector<ResidentialCell> rVect;
	vector<CommercialCell> cVect;
	vector<IndustrialCell> iVect;

	vector<vector<BaseCell> >::iterator it;
	it = vect.end();
	it--;

	vect.erase(it);

	//Variables for displaying time steps, workers, and goods
	int wtemp = 0;
	int availworkers = 0;
	int gtemp = 0;
	int availgoods = 0;
	int refreshtemp = 0;
	bool firstStep = true;

	//Output initial grid
	InitialGrid();

	//Initializes the arrays for the three types of cells,
	//Residential, Industrial, and Commercial
	for (int i = 0; i < vect.size(); i++) {
		for (int j = 0; j < vect[i].size(); j++) {
			if (vect[i][j].GetType() == 'R') {
				ResidentialCell RC('R', vect);
				RC.setRow(i);
				RC.setCol(j);
				rVect.push_back(RC);
			}
			if (vect[i][j].GetType() == 'I') {
				IndustrialCell IC('I', vect);
				IC.SetRow(i);
				IC.SetCol(j);
				iVect.push_back(IC);
			}
			if (vect[i][j].GetType() == 'C') {
				CommercialCell CC('C', vect);
				CC.SetRow(i);
				CC.SetCol(j);
				cVect.push_back(CC);
			}
		}
	}

	for (int i = 0; i < rVect.size(); i++) {
		vect[rVect[i].getRow()][rVect[i].getCol()] = rVect[i];
	}

	for (int i = 0; i < cVect.size(); i++) {
		vect[cVect[i].GetRow()][cVect[i].GetCol()] = cVect[i];
	}

	for (int i = 0; i < iVect.size(); i++) {
		vect[iVect[i].GetRow()][iVect[i].GetCol()] = iVect[i];
	}

	//--------------------------------------------------
	// MAIN SIMULATION LOOP
	for (int i = 0; i < TimeLimit; i++) {
		//Residential call
		for (int j = 0; j < rVect.size(); j++) {
			rVect[j].mainCall(vect);
		}
		//Commercial call
		for (int j = 0; j < cVect.size(); j++) {
			vect = cVect[j].TryToAddPopulation(vect);
		}
		//Industrial call
		for (int j = 0; j < iVect.size(); j++) {
			vect = iVect[j].step(vect);
		}
		for (int j = 0; j < iVect.size(); j++) {
			availgoods = iVect[j].CalcGoods(vect);
		}

		//Get workers
		for (int j = 0; j < rVect.size(); j++) {
			wtemp = rVect[j].GetAvailableWorkers();
			availworkers += wtemp;
			wtemp = 0;
		}

		for (int i = 0; i < rVect.size(); i++)
			vect[rVect[i].getRow()][rVect[i].getCol()] = rVect[i];

		for (int i = 0; i < cVect.size(); i++)
			vect[cVect[i].GetRow()][cVect[i].GetCol()] = cVect[i];

		for (int i = 0; i < iVect.size(); i++)
			vect[iVect[i].GetRow()][iVect[i].GetCol()] = iVect[i];

		//Info that is always printed for every time step
		cout << endl;
		cout << "Timestep: " << i + 1 << endl;
		cout << "Available Workers: " << availworkers << endl;
		cout << "Available Goods: " << availgoods << endl;

		availworkers = 0;
		availgoods = 0;

		//Check refresh rate for whether or not to print the grid
		if (firstStep == true) {
			Timestep();
			firstStep = false;
		}
		else {
			if (RefreshRate == 1) {
				Timestep();
			}
			else {
				++refreshtemp;
				if (refreshtemp == RefreshRate) {
					cout << endl;
					Timestep();
					refreshtemp = 0;
				}
			}
		}
	}
	//--------------------------------------------------
	//Display pollution
	//Pollution Call
	for (int j = 0; j < iVect.size(); j++) {
		vect = iVect[j].attemptAddPollution(vect);
	}

	for (int i = 0; i < (vect[0].size() * 2) + 2; i++) {
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < vect.size(); i++) {
		cout << "|";
		for (int j = 0; j < vect[i].size(); j++) {
			cout << vect[i][j].GetPollution() << " ";
		}
		cout << "|" << endl;
	}
	for (int i = 0; i < (vect[0].size() * 2) + 2; i++) {
		cout << "-";
	}
	cout << endl;

	//Total populations for each type (residential, commerical, industrial) and pollution
	cout << "The total populations for the region are:" << endl;
	int rpop = 0;
	int cpop = 0;
	int ipop = 0;
	int ppop = 0;
	//Total populations
	for (int i = 0; i < vect.size(); i++) {
		for (int j = 0; j < vect[i].size(); j++) {
			if (vect[i][j].GetType() == 'R') {
				rpop += vect[i][j].GetPopulation();
			}
			if (vect[i][j].GetType() == 'I') {
				ipop += vect[i][j].GetPopulation();
			}
			if (vect[i][j].GetType() == 'C') {
				cpop += vect[i][j].GetPopulation();
			}
			if (vect[i][j].GetType() == 'I') {
				ppop += vect[i][j].GetPollution();
			}
		}
	}
	cout << "Residential: " << rpop << endl;
	cout << "Industrial: " << ipop << endl;
	cout << "Commercial: " << cpop << endl;
	cout << "The total amount of pollution for the area is " << ppop << " units" << endl;

	//Returning total populations for each type within given area and pollution
	int xmin;
	int ymin;
	int xmax;
	int ymax;
	int popR = 0;
	int popI = 0;
	int popC = 0;
	int popP = 0;
	cout << "Please enter the minimum and maximum coordinates of the area you wish to have more information about.\n(Minimum X = 0, Minimum Y = 0, Maximum X = 3, Maximum Y = 3)" << endl;
	cout << "Minimum X = ";
	cin >> xmin;
	while ((xmin < 0) || (xmin > vect.size())) {

		cout << "Invalid Range\n" << "Minimum X = ";
		cin >> xmin;
	}

	cout << "Minimum Y = ";
	cin >> ymin;
	while ((ymin < 0) || (ymin > vect[0].size())) {

		cout << "Invalid Range\n" << "Minimum Y = ";
		cin >> ymin;

	}

	cout << "Maximum X = ";
	cin >> xmax;
	while ((xmax < 0) || (xmax > vect.size())) {

		cout << "Invalid Range\n" << "Maxium X = ";
		cin >> xmax;

	}

	cout << "Maximum Y = ";
	cin >> ymax;
	while ((ymax < 0) || (ymax > vect[0].size())) {

		cout << "Invalid Range\n" << "Maximum Y = ";
		cin >> ymax;
	}

	//Getting pollution of the area
	for (int i = ymin; i < ymax; i++)
	{
		for (int j = xmin; j < xmax + 1; j++)
		{
			if (vect[j][i].GetType() == 'R') {

				popR += vect[j][i].GetPopulation();
			}
			if (vect[j][i].GetType() == 'I') {

				popI += vect[j][i].GetPopulation();
			}
			if (vect[j][i].GetType() == 'C') {
				popC += vect[i][j].GetPopulation();
			}
			if (vect[j][i].GetType() == 'I') {
				popP += vect[j][i].GetPollution();
			}
		}
	}

	cout << "The total populations for the requested area are:" << endl;
	cout << "Residential: " << popR << endl;
	cout << "Industrial: " << popI << endl;
	cout << "Commercial: " << popC << endl;
	cout << "Pollution: " << popP << endl << endl;
	cout << "Simulation complete." << endl;
	return 0;
}
