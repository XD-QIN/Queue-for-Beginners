#include "MM1.h"
#include <math.h>
#include <time.h>
#include <iomanip>
#include <fstream>


double Seed = 7;
double myrand();
double ExpRan(double);

#define NumofSimPoints 10

int main(){ 
	 
	string filename;

	cout << "Enter the result file name: ";
	cin >> filename;
	

	ofstream ofile;
	ofile.open( filename.c_str() );
    
	cout << "Lambda \tAvgTaskDelay" << endl;
    ofile << "Lambda \tAvgTaskDelay" << endl;

	double TotalNumofSimPkts = 1e6;  // total number of simulated packets
	double CurNumofSimPkts=0;       // total number of packets which have been issued

	double TotalNumofCompletePkts = 0; // total number of packets which have been processed
	
	//double Lambda[NumofSimPoints] =        { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.93, 0.96, 0.99 };
	//double AvgTaskDelay[NumofSimPoints] =  {  0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,    0   };

	//double Lambda[NumofSimPoints] =       { 0.8, 0.9, 0.93, 0.96, 0.99 };
	//double AvgTaskDelay[NumofSimPoints] = {  0,    0,   0,    0,    0  };

	double Lambda[NumofSimPoints] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.95 };
	double AvgTaskDelay[NumofSimPoints] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	DLinkedList Queue;   // a single queue

	int i, j;
	int next_event_type;
	double CurTime, min_time_next_event, TotalDelay;

	double time_next_event[2];   // time_next_event[0]: arrival event
	                             // time_next_event[1]: departure event

	for (i = 0; i < NumofSimPoints; i++)     // number of arrival intensity
	{
		CurTime = 0;
		TotalDelay = 0;
		CurNumofSimPkts = 0;
		TotalNumofCompletePkts = 0;
		while (!Queue.empty()) Queue.removeFront();     // keep the queue empty
		time_next_event[0] = ExpRan(1.0 / Lambda[i]);   // the time when the next arrival event occurs
		time_next_event[1] = 1e30;                      // the time when the next departure event occurs

		while (CurNumofSimPkts <= TotalNumofSimPkts)   // simulation starts
		{
			/*** Determine the type of the next occuring event ***/
			min_time_next_event = 1e30;
			for (j = 0; j < 2; j++)
			{
				if (time_next_event[j] < min_time_next_event)
				{
					min_time_next_event = time_next_event[j];
					next_event_type = j;
				}
			}
			CurTime = min_time_next_event;
			/*****************************************************/

			if (next_event_type == 0)
				/*** calls the arrival routine ***/
			{
				if (Queue.empty() == 1)
				{
					time_next_event[1] = CurTime + ExpRan(1.0);   // set the time when the next departure event happens
				}

				Queue.addBack(CurTime);                           // insert the packet into the queue
				CurNumofSimPkts = CurNumofSimPkts + 1;             // Number of issued packets increases by 1
				time_next_event[0] = CurTime + ExpRan(1.0 / Lambda[i]);  // set the time when the next arrival event happens
			}
			else
				/*** calls the departure routine ***/
			{
				TotalDelay = TotalDelay + CurTime - Queue.header->next->aTime;
				TotalNumofCompletePkts = TotalNumofCompletePkts + 1;
				Queue.removeFront();
				if (Queue.empty() == 1)
				{
					time_next_event[1] = 1e30;   // if the queue is empty, set arrival process as next event
				}
				else                            
				{
					time_next_event[1] = CurTime + ExpRan(1.0);      // set the time when the next departure event happens
				}
			}
		}
		
	    /******** Data Collection *******************/
	    
		AvgTaskDelay[i] = TotalDelay / TotalNumofCompletePkts;

		cout << setw(12) << setprecision(10) << Lambda[i] << '\t' << setw(12) << setprecision(10) << AvgTaskDelay[i] << endl;
		ofile << setw(12) << setprecision(10) << Lambda[i] << '\t' << setw(12) << setprecision(10) << AvgTaskDelay[i] << endl;
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

double ExpRan(double mean)
{
	double u, p;
	u = myrand();
	p = -mean*log(u);
	return p;
}