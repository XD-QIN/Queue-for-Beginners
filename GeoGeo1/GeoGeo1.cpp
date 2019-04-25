#include <math.h>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

double Seed = 7;
double myrand();

#define NumofSimPoints 12
#define SimTime 1e7

int main(){ 
	 
	string filename;

	cout << "Enter the result file name: ";
	cin >> filename;
	

	ofstream ofile;
	ofile.open( filename.c_str() );
    
	cout << "Lambda \tAvgTaskDelay" << endl;
    ofile << "Lambda \tAvgTaskDelay" << endl;

	//double epsilon[NumofSimPoints] = { 0.1, 0.08, 0.05, 0.03, 0.01, 0.008, 0.007, 0.006, 0.005, 0.0045, 0.004 };
	double lambda[NumofSimPoints] = {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.42, 0.44, 0.46, 0.48, 0.49 };

	double mu = 0.5;  // service rate
	double meanQ[NumofSimPoints] = { 0 };

	int i;
	long long t;
	double A, S, Q_next, Q_cur;
	
	long double totalQ;

	for (i = 0; i < NumofSimPoints; i++)     // number of arrival intensity
	{
		totalQ = 0;
		Q_cur = 0;

		for (t = 0; t < SimTime; t++)   // simulation starts
		{
			
			/*****************************************************/
			if (myrand() < lambda[i])   /*** generating arrivals***/
			{
				A = 1;
			}
			else
			{
				A = 0;
			}

			if (myrand() < 0.1)  
			{
				S = 5;
			}
			else
			{
				S = 0;
			}

			totalQ = totalQ + Q_cur;

			Q_next = Q_cur + A - S;
			if (Q_next < 0)
			{
				Q_next = 0;
			}
			Q_cur = Q_next;
			
		}
		
	    /******** Data Collection *******************/
	    
		meanQ[i] = totalQ / SimTime;

		cout <<  lambda[i] << '\t' << setw(12) << setprecision(10) << meanQ[i] << endl;
		ofile <<  lambda[i] << '\t' << setw(12) << setprecision(10) << meanQ[i] << endl;
	}

	return 0;
}

double myrand()
{
	double p;
	p = fmod(3125.0*Seed, 34359738337.0);
	Seed = p;
	p = p / 34359738337.0;
	return p;
}