#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <random>

#include "core.h"
#include "encoder.h"

using namespace std;

//INITIALIZATION FUNCTIONS - CONSTRUCTORS

ProcNode::ProcNode(int id, ProcCom& message)
{
	identifier = id;

	//cout << "Initialized Proccesor Node - " << id << endl;
}

ProcCol::ProcCol(int id, ProcCom& message)
{
	identifier = id;

	//Static casts are to perform float to int conversions
	int cAmount = static_cast<int>((message.input.resolution * message.input.resolution) / density_controller);
	int resolution = static_cast<int>(message.input.resolution);

	//Generate connections based on the resolution of the input SDR
	for (int x = 0; x < cAmount; x++)
	{
		random_device rd;
		mt19937 gen(rd());

		uniform_int_distribution<> prepLoc(0, ((resolution * resolution) - 1));
		uniform_int_distribution<> prepStrength(0, 100);
		float randLoc = prepLoc(gen);
		float randStrength = prepStrength(gen);

		vector<float> connection;
		connection.push_back(randLoc);
		connection.push_back(randStrength);

		connections.push_back(connection);
	}

	for (int x = 0; x < message.nodeAmount; x++)
	{
		nodes.push_back(ProcNode::ProcNode(x, message));
	}

	//cout << "Initialized Processor Column - " << id << endl;
}

ProcUnit::ProcUnit(int id, ProcCom& message)
{
	identifier = id;

	for (int x = 0; x < message.colAmount; x++)
	{
		columns.push_back(ProcCol::ProcCol(x, message));
	}

	cout << "Initialized Processor Unit - " << id << endl;
}

ProcNet::ProcNet(SDR input, int unitAmount, int colAmount, int nodeAmount)
{

	ProcCom message;

	message.unitAmount = unitAmount;
	message.colAmount = colAmount;
	message.nodeAmount = nodeAmount;
	message.input = input;

	ua = unitAmount;
	ca = colAmount;
	na = nodeAmount;

	for (int x = 0; x < unitAmount; x++)
	{
		units.push_back(ProcUnit::ProcUnit(x, message));
	}

	initialized = true;
	cout << "Initialized Processor Network"  << endl;
}