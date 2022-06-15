#include <vector> 

#include "encoder.h"

using namespace std;

#pragma once

class ProcCom
{
	public:
		int unitAmount = 0;
		int colAmount = 0;
		int nodeAmount = 0;

		SDR input;
		
		vector<vector<vector<int>>> connActivations;
		vector<vector<int>> nodeActivations;
		vector<vector<vector<int>>> connPredictions;
		vector<vector<int>> nodePredictions;
		vector<bool> predictionAccuracy;
		
		vector<int> parentIdentifier;

		vector<int> execLevel;
		vector<string> command;
		
};

class ProcNode
{
	public:
		int identifier;
		vector<vector<float>> connections;
		int termination_threshold = 10;

		void adj_distal(ProcCom& message);
		void check_predictive(ProcCom& message);
		
		void ProcExec(ProcCom& message);
		ProcNode(int id, ProcCom& message);
};

class ProcCol
{
	public:
		int identifier;
		vector<ProcNode> nodes;
		int density_controller = 2;
		int adjustment_controller = 10;
		int termination_threshold = 10;
		vector<vector<float>> connections;
		

		void adj_distal(ProcCom& message);
		void adj_proximal(ProcCom& message);
		void check_active(ProcCom& message);
		

		void ProcExec(ProcCom& message);
		ProcCol(int id, ProcCom& message);

};

class ProcUnit
{
	public:
		int identifier;
		vector<ProcCol> columns;
		int activation_threshold = 5;
		int prediction_threshold = 10;
		vector<vector<int>> nodeActivations;
		vector<vector<int>> nodePredictions;
		
		void distal_handler(ProcCom& message);
		void proximal_handler(ProcCom& message);
		void cycle(ProcCom& message);

		void ProcExec(ProcCom& message);
		ProcUnit(int id, ProcCom& message);
};

class ProcNet
{
	public:
		bool initialized = false;
		vector<ProcUnit> units;
		int ua = 0;
		int ca = 0;
		int na = 0;

		ProcCom consolidator(ProcCom& message);
		ProcCom forward(SDR input);

		void ProcExec(ProcCom& message);
		ProcNet(SDR input, int unitAmount, int colAmount, int nodeAmount);
};

