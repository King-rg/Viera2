#include <vector>

using namespace std;

#pragma once

class SDR
{
	public:
		float resolution;
		float scaling; 
		vector<vector<int>> content;
};

class encoder
{
	public:
		float resolution = 40;
		float scaling = 100;
		SDR TimeSeries(float data[50]);
};

