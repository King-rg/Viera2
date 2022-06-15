#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>

#include "core.h"
#include "encoder.h"

using namespace std;

// BACKEND PROCESS EXECUTION FUNCTIONS

void ProcNode::ProcExec(ProcCom& message)
{
	//Level 3
	if (message.execLevel.back() == 3)
	{
		cout << "Hooking ProxExec 3" << endl;

		if (message.command.back().compare("get_predictive") == 0)
		{
			check_predictive(message);
		}

		if (message.command.back().compare("adj_dist") == 0)
		{
			adj_distal(message);
		}
	}
}

void ProcCol::ProcExec(ProcCom& message)
{
	//Level 2
	if (message.execLevel.back() == 2)
	{
		cout << "Hooking ProxExec 2" << endl;

		if (message.command.back().compare("get_active") == 0)
		{
			check_active(message);
		}

		if (message.command.back().compare("adj_prox") == 0)
		{
			adj_proximal(message);
		}
	}
	else
	{
		for (int x = 0; x < message.nodeAmount; x++)
		{
			nodes[x].ProcExec(message);
		}

		if (message.execLevel.back() - 1 == 2)
		{
			message.execLevel.pop_back();
			message.command.pop_back();
		}
	}
}

void ProcUnit::ProcExec(ProcCom& message)
{
	//Level 1

	if (message.execLevel.back() == 1)
	{
		cout << "Hooking ProxExec 1" << endl;

		if (message.command.back().compare("cycle") == 0)
		{
			cycle(message);
		}

	}
	else
	{
		for (int x = 0; x < message.colAmount; x++)
		{
			columns[x].ProcExec(message);
		}

		if (message.execLevel.back() - 1 == 1)
		{
			message.execLevel.pop_back();
			message.command.pop_back();
		}
	}
}

void ProcNet::ProcExec(ProcCom& message)
{
	//Level 0

	if (message.execLevel.back() == 0)
	{
		cout << "Hooking ProxExec 0" << endl;

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