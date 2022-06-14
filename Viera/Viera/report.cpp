#include <iostream>
#include <fstream>
#include "report.h"

using namespace std;

void report::generate(ProcCom message)
{
	ofstream report ("C:\\Users\\12037\\Documents\\report.txt");

	cout << "Creating report" << endl;

	if (report)
	{
		//SDR VISUAL REPORT GRAPHIC
		report << "SDR VISUAL" << endl;
		for (int x = 0; x < message.input.resolution; x++)
		{
			for (int y = 0; y < message.input.resolution; y++)
			{

				report << message.input.content[x][y] << " ";

			}
			report << endl;
			

		}
		report << endl;



		//UNIT COLUMN ACTIVATIONS
	}
	else
	{
		cout << "Cannot write report" << endl;
	}



	// GENERATE SDR VISUAL


}