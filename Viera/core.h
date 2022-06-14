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
		int connections = 0;

		SDR input;
		SDR input2;

		int execLevel = 0;
		string command;
		
		class returning
		{
			public:
				int i = 0;
				string s;
				SDR sdr;
		};
};

class ProcNode
{
	public:
		int identifier;
		vector<vector<float>> connections;
		
<<<<<<< HEAD
		ProcNode(SDR input, int id);
=======
		class routines
		{
			public:

		};

		ProcCom ProcExec(ProcCom message);
		ProcNode(int id, ProcCom message);
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
};

class ProcCol
{
	public:
		int identifier;
		vector<ProcNode> nodes;
		
<<<<<<< HEAD
		ProcCol(SDR input, int id, int nodeAmount);
=======
		class routines
		{
			public:

		};

		ProcCom ProcExec(ProcCom message);
		ProcCol(int id, ProcCom message);
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31

};

class ProcUnit
{
	public:
		int identifier;
		vector<ProcCol> columns;
		
<<<<<<< HEAD
		ProcUnit(SDR input, int id, int colAmount, int nodeAmount);
=======
		class routines
		{
			public:
				

		};
		
		ProcCom ProcExec(ProcCom message);
		ProcUnit(int id, ProcCom message);
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
};

class ProcNet
{
	public:
<<<<<<< HEAD
		vector<ProcUnit> units;
		
=======
		bool initialized = false;
		vector<ProcUnit> units;
		
		class routines
		{
			public:

		};

		ProcCom predict(SDR input);

		ProcCom ProcExec(ProcCom message);
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
		ProcNet(SDR input, int unitAmount, int colAmount, int nodeAmount);
};

