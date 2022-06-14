#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>

#include "core.h"
#include "encoder.h"

using namespace std;

//INITIALIZATION FUNCTIONS - CONSTRUCTORS

<<<<<<< HEAD
ProcNode::ProcNode(SDR input, int id)
{
	identifier = id;
	int cAmount = round(input.resolution/4);
	int resolution = input.resolution;
=======
ProcNode::ProcNode(int id, ProcCom message)
{
	identifier = id;
	//Static casts are to perform float to int conversions
	int cAmount = static_cast<int>(message.input.resolution/4);
	int resolution = static_cast<int>(message.input.resolution);
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31

	//Generate connections based on the resolution of the input SDR
	for (int x = 0; x < cAmount; x++)
	{
		float randLoc = rand() % resolution;
		float randStrength = 1 + (rand() % 100);

		vector<float> connection;
		connection.push_back(randLoc);
		connection.push_back(randStrength);

<<<<<<< HEAD
		/*
		cout << randLoc << endl;
		cout << randStrength << endl;
		cout << "----" << endl;
		*/


=======
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
		connections.push_back(connection);

	}
}

<<<<<<< HEAD
ProcCol::ProcCol(SDR input, int id, int nodeAmount)
=======
ProcCol::ProcCol(int id, ProcCom message)
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
{
	identifier = id;

	for (int x = 0; x < message.nodeAmount; x++)
	{
<<<<<<< HEAD
		nodes.push_back(ProcNode::ProcNode(input, x));
	}
}

ProcUnit::ProcUnit(SDR input, int id, int colAmount, int nodeAmount)
=======
		nodes.push_back(ProcNode::ProcNode(x, message));
	}

	cout << "Initialized Processor Column - " << id << endl;
}

ProcUnit::ProcUnit(int id, ProcCom message)
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
{
	identifier = id;

	for (int x = 0; x < message.colAmount; x++)
	{
<<<<<<< HEAD
		columns.push_back(ProcCol::ProcCol(input, x, nodeAmount));
=======
		columns.push_back(ProcCol::ProcCol(x, message));
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
	}

	cout << "Initialized Processor Unit - " << id << endl;
}

ProcNet::ProcNet(SDR input, int unitAmount, int colAmount, int nodeAmount)
{

	ProcCom message;

	message.unitAmount = unitAmount;
	message.colAmount = colAmount;
	message.nodeAmount = nodeAmount;

	for (int x = 0; x < unitAmount; x++)
	{
<<<<<<< HEAD
		units.push_back(ProcUnit::ProcUnit(input, x, colAmount, nodeAmount));
=======
		units.push_back(ProcUnit::ProcUnit(x, message));
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
	}

	initialized = true;
	cout << "Initialized Processor Network"  << endl;
}