#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>

#include "core.h"
#include "encoder.h"

using namespace std;

void ProcNode::adj_distal(ProcCom& message)
{
	for (int x = 0; x < size(message.nodePredictions); x++)
	{
		float strength = connections[x][1];
		float adjustment = 30 - (sqrt(10 * strength));

		if (message.predictionAccuracy[x] == true)
		{
			//If predictive became active increase the connection strengths
			connections[message.nodePredictions[x][1]][1] = connections[message.nodePredictions[x][1]][1] + adjustment;
		}
		else
		{
			// If predictive did not become active decrease the connection strength.
			float negAdjustment = -1 * (adjustment)+30;
			connections[message.nodePredictions[x][1]][1] = connections[message.nodePredictions[x][1]][1] - negAdjustment;
		}
	}

	// Prune all distal connections below termination_threshold
	for (int x = 0; x < size(message.nodePredictions); x++)
	{
		if (connections[message.nodePredictions[x][1]][1] <= termination_threshold)
		{
			connections.erase(connections.begin() + x);
		}
	}
}

void ProcNode::check_predictive(ProcCom& message)
{
	//Iterate through every distal connection and check if connected node is active

	vector<vector<int>> nodepredcache;

	for (int x = 0; x < size(connections); x++)
	{
		vector<int> nodepred;

		

		for (int y = 0; y < size(message.nodeActivations); y++)
		{
			int location = connections[x][0];
			int strength = connections[x][1];

			if (connections[x][0] == message.nodeActivations[y][1])
			{
				nodepred.push_back(location);
				nodepred.push_back(strength);
				nodepred.push_back(message.parentIdentifier.back());
				
				nodepredcache.push_back(nodepred);
				
				break;
			}
		}
	}
	message.connPredictions.push_back(nodepredcache);
}
