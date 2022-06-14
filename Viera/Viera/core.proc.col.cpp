#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>

#include "core.h"
#include "encoder.h"

using namespace std;

bool check_location(int location, ProcCom& message)
{
	int counter = 0;
	for (int x = 0; x < message.input.resolution; x++)
	{
		for (int y = 0; y < message.input.resolution; y++)
		{
			if (counter == location)
			{
				//cout << "Checking location - " << location << " - " << x << " - " << y << " - ";
				if (message.input.content[x][y] == 1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				counter++;
			}
		}
	}
}

void ProcCol::adj_proximal(ProcCom& message)
{
	//Check if column identifier matches active column ids

	for (int x = 0; x < size(message.nodeActivations); x++)
	{
		if (message.nodeActivations[x][1] == identifier)
		{
			int cAmount = static_cast<int>((message.input.resolution * message.input.resolution) / density_controller);
			
			for (int y = 0; y < cAmount; y++)
			{
				// The reason we don't prune any connections if a match is found is because given the current configuration it is mathmatically impossible.

				float location = connections[x][0];
				float strength = connections[y][1];
				float adjustment = 30 - (sqrt(10*strength));

				if (check_location(location, message) == true)
				{
					//Boost match connections
					connections[y][1] = connections[y][1] + adjustment;
					//cout << strength;
					//cout << " - " << adjustment << endl;
				}
				else
				{
					//Inhibit nonmatch connections
					float negAdjustment = -1 * (adjustment)+30;
					//cout << strength;
					//cout << " - " << negAdjustment << endl;
					
					connections[y][1] = connections[y][1] - negAdjustment;
				}
			}

			for (int x = 0; x < size(connections); x++)
			{
				if (connections[x][1] <= termination_threshold)
				{
					//cout << "Pruning" << endl;
					connections.erase(connections.begin() + x);
				}
			}
		}
	}
}

void ProcCol::check_active(ProcCom& message)
{
	cout << "Getting active" << endl;

	//cout << "Checking active" << endl;
	int cAmount = static_cast<int>((message.input.resolution * message.input.resolution) / density_controller);
	vector<vector<int>> activationSet;

	for (int x = 0; x < cAmount; x++)
	{
		float location = connections[x][0];

		if (check_location(location, message) == true)
		{
			//cout << "FOUND MATCH" << endl;
			
			vector<int> activation;
			activation.push_back(location);
			activation.push_back(identifier);
			activation.push_back(message.parentIdentifier.back());

			activationSet.push_back(activation);
		}
		else
		{
			//cout << endl;
		}
	}
	
	//cout << size(activationSet) << " - ";
	//cout << size(message.connActivations) << " - ";
	//cout << identifier << " - ";
	//cout << message.parentIdentifier.back() << endl;

	message.connActivations.push_back(activationSet);
}




/*
ProcCom ProcCol::get_predictive(ProcCom activeState)
{

}

*/
