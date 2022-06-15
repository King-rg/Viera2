#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <algorithm>

#include "core.h"
#include "encoder.h"
#include "report.h"

using namespace std;

vector<vector<int>> sort_overlaps(vector<vector<int>> unsortedOverlaps)
{
	//Create a vector of overlap scores

	vector<int> overlapScores;
	vector<vector<int>> sortedOverlaps;

	for (int x = 0; x < size(unsortedOverlaps); x++)
	{
		overlapScores.push_back(unsortedOverlaps[x][0]);
	}

	//Sort overlap scores

	sort(overlapScores.begin(), overlapScores.end(), greater<int>());

	// Run through every overlap and move it to the location of a sorted overlap score

	while (size(unsortedOverlaps) != 0)
	{
		// Get first current overlap score of sorted vector
		for (int x = 0; x < size(overlapScores); x++)
		{
			// Find location of overlap with matching overlap score

			if (overlapScores[0] == unsortedOverlaps[x][0])
			{
				// Append overlap to sorted vector
				sortedOverlaps.push_back(unsortedOverlaps[x]);

				// Pop both the first overlap score and matching vector in unsorted.
				overlapScores.erase(overlapScores.begin());
				unsortedOverlaps.erase(unsortedOverlaps.begin()+x);
				
				break;
			}
		}
	}

	return sortedOverlaps;
}

void ProcUnit::cycle(ProcCom& message)
{
	cout << "Cycling" << endl;
	
	//GET ALL ACTIVE CONNECTIONS BASED ON INPUT SDR

	message.execLevel.push_back(2);
	message.command.push_back("get_active");
	cout << "Pushing identifier " << identifier << endl;
	message.parentIdentifier.push_back(identifier);
	ProcExec(message);

	//CONVERT ALL ACTIVE CONNECTIONS TO ACTIVE COLUMNS IN ORDER OF OVERLAP
	
	vector<vector<int>> overlapsUnsorted;

	for (int x = 0; x < size(message.connActivations); x++)
	{
		vector<int> overlap;

		//Calculate overlap
		int overlapScore = size(message.connActivations[x]);
		//Place overlap scores with id and parent id into unsorted vector
		int id = message.connActivations[x][0][1];
		int parentid = message.connActivations[x][0][2];
		overlap.push_back(overlapScore);
		overlap.push_back(id);
		overlap.push_back(parentid);
		overlapsUnsorted.push_back(overlap);
	}

	//Sort vector by overlap score
		
	vector<vector<int>> overlapsSorted = sort_overlaps(overlapsUnsorted);

	//Push active columns to nodeActivations based on an activation threshold

	for (int x = 0; x < activation_threshold; x++)
	{
		message.nodeActivations.push_back(overlapsSorted[x]);
	}

	//BEGIN PROXIMAL TRAINING HANDLING

	message.execLevel.push_back(2);
	message.command.push_back("adj_prox");
	message.parentIdentifier.push_back(identifier);
	ProcExec(message);

	

	//BEGIN DISTAL TRAINING HANDLING

	/*
	
	CONN_PROX:
	[0]: location (SDR)
	[1]: strength

	NODE_ACTIVATION:
	[0]: overlapScore
	[1]: id
	[2]: parentid

	NODE_PREDICTION:
	[0]: activationScore
	[1]: id
	[2]: parentid

	CONN_DIST: 
	[0]: location_id
	[1]: strength



	*/

	//Check if predictive nodes were activated

	

	for (int x = 0; x < size(message.nodePredictions); x++)
	{
		bool found = false;
		for (int y = 0; y < size(message.nodeActivations); y++)
		{
			if (message.nodePredictions[x][0] == message.nodeActivations[x][1])
			{
				found = true;
			}
		}

		message.predictionAccuracy.push_back(found);
	}

	

	//Adjust distal connections

	message.execLevel.push_back(3);
	message.command.push_back("adjust_dist");
	message.parentIdentifier.push_back(identifier);
	ProcExec(message);
	
	

	// If a new column was activated in the sequence, create a distal connection in the node with no connections or least distal connections to ensure nodes aren't overloaded.



	//Save the current activations for next cycle

	nodeActivations = message.nodeActivations;

	//Calculate and save current predictive nodes

	message.execLevel.push_back(3);
	message.command.push_back("get_predictive");
	message.parentIdentifier.push_back(identifier);
	ProcExec(message);

	vector<vector<int>> nodepred;
	
	for (int x = 0; x < size(message.connPredictions); x++)
	{
		vector<int> pred;

		//Calculate overlap
		int activationScore = size(message.connPredictions[x]);
		//Place overlap scores with id and parent id into unsorted vector
		cout << "DEBUG FLAG" << endl;
		int id = message.connPredictions[x][0][1];
		int parentid = message.connPredictions[x][0][2];

		if (activationScore > activation_threshold)
		{
			pred.push_back(activationScore);
			pred.push_back(id);
			pred.push_back(parentid);
			nodepred.push_back(pred);
		}
	}

	nodePredictions = nodepred;

	//REPORTING
	report r;
	r.generate(message);

	//PERFORM CLEANUP AND STORAGE OPERATIONS FOR NEXT UNIT

	

	message.connActivations.clear();
	message.nodeActivations.clear();
	

}