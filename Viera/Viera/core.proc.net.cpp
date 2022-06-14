#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>

#include "core.h"
#include "encoder.h"

using namespace std;

ProcCom ProcNet::consolidator(ProcCom& message)
{
	cout << "Consolidating" << endl;

	return message;
}

ProcCom ProcNet::predict(SDR input)
{
	cout << "Predicting" << endl;

	ProcCom cycle;
	cycle.input = input;
	cycle.unitAmount = ua;
	cycle.colAmount = ca;
	cycle.nodeAmount = na;
	cycle.execLevel.push_back(1);
	cycle.command.push_back("cycle");

	ProcExec(cycle);

	ProcCom ret = consolidator(cycle);

	//cout << cycle.activations[3] << endl;

	return ret;
}