// Viera.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
//#include "Poco/Util/Units.h"

#include "encoder.h"
#include "core.h"


int main()
{
    encoder SDRE;
    float series[50] = { 0.0259317997843027,0.0208158008754253,0.0219314992427825,0.0214887000620365,0.0185391008853912,0.0209408998489379,0.0204771999269723,0.02211369946599,0.0215313006192445,0.0225195009261369,0.0262521002441644,0.0336409993469715,0.0324648991227149,0.0300485994666814,0.02894820086658,0.0272174999117851,0.026690699160099,0.0270319003611803,0.030629800632596,0.0284362006932497,0.0277287997305393,0.0254535991698503,0.0271927006542682,0.0275274999439716,0.027131799608469,0.0263817999511957,0.025866100564599,0.0286068990826606,0.0285829007625579,0.0304374992847442,0.0229861997067928,0.0213059000670909,0.0226281005889177,0.0220221001654863,0.0206349994987249,0.0218809992074966,0.0221947003155946,0.0251860003918409,0.0320529006421566,0.0271192006766796,0.027437100186944,0.0239770002663135,0.0258076004683971,0.0262301005423069,0.0264446008950471,0.0275800004601478,0.025772500783205,0.0263691004365682,0.0280844997614622,0.0295813009142875 };
    SDR ret = SDRE.TimeSeries(series);

    ProcNet alpha(ret,2,20,5);

    alpha.forward(ret);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
