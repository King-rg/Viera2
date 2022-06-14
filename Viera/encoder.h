#include <vector>

using namespace std;

#pragma once

class SDR
{
<<<<<<< HEAD
	public: 
		float resolution; 
		float scaling; 
		vector<vector<int>> content; 
=======
	public:
		float resolution;
		float scaling; 
		vector<vector<int>> content;
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
};

class encoder
{
<<<<<<< HEAD
	public: 
		float resolution = 20; 
		float scaling = 100; 
		SDR TimeSeries(float data[50]); 
=======
	public:
		float resolution = 20;
		float scaling = 100;
		SDR TimeSeries(float data[50]);
>>>>>>> 9f11864816877688df77455afe1c681a03c4cf31
};

