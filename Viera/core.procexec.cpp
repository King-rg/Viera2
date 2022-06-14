#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>

#include "core.h"
#include "encoder.h"

using namespace std;

// BACKEND PROCESS EXECUTION FUNCTIONS

ProcCom ProcNode::ProcExec(ProcCom message)
{
	//Level 3
	if (message.execLevel == 3)
	{

		return message;
	}
}

ProcCom ProcCol::ProcExec(ProcCom message)
{
	//Level 2
	if (message.execLevel == 2)
	{
		return message;
	}
	else
	{
		for (int x = 0; x < message.nodeAmount; x++)
		{
			nodes[x].ProcExec(message);
		}
	}
}

ProcCom ProcUnit::ProcExec(ProcCom message)
{
	//Level 1
	if (message.execLevel == 1)
	{
		return message;
	}
	else
	{
		for (int x = 0; x < message.colAmount; x++)
		{
			columns[x].ProcExec(message);
		}
	}
}

ProcCom ProcNet::ProcExec(ProcCom message)
{
	//Level 0

	if (message.execLevel == 0)
	{
		return message;
	}
	else
	{
		if (initialized == true)
		{
			for (int x = 0; x < message.unitAmount; x++)
			{
				units[x].ProcExec(message);
			}
		}
	}
}