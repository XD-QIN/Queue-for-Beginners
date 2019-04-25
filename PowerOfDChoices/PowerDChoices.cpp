#include "PowerDChoices.h"
#include <math.h>
#include <time.h>
#include <iomanip>
#include <fstream>


double Seed = 7;
double myrand();
double ExpRan(double);
long long GenInteger(long long);


/* random number controlled by a seed*/
unsigned long long randomX;
long long RandSeed();
double genUniformSeed(void);

int GenIntegerSeed(int);
/************************************/

#define NumofSimPoints 14
#define NumofServers   1000
#define NumofFiles     1e7


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
	double TotalNumofCompletePkts = 0;  // total number of packets which have been processed
	
	double Lambda[NumofSimPoints] =        { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.92, 0.94, 0.96, 0.98, 0.99};
	double AvgTaskDelay[NumofSimPoints] =  {  0,   0,   0,   0,   0,   0,   0,   0,   0,    0 };

	DLinkedList Queue[NumofServers];   // create queues

	int i, j, n;
	int next_event_type;                // 0:   departure event occurs at queue 0
	                                    // 1:   departure event occurs at queue 1
	                                    // .....
	                                    // N-1: departure event occurs at queue N-1
	                                    // N:   arrival event occurs

	double FileType, CurTime, min_time_next_event, TotalDelay;
	int SIndex[2], ArrivalID;    // indecies for sampled servers
	double minSampleQ, tempQ;

	double time_arrival_event;                  // time for arrival event
	double time_departure_event[NumofServers];  // time for departure event
	srand(time(NULL));
	long long temp;


	for (i = 0; i < NumofSimPoints; i++)     // number of arrival intensity
	{
		CurTime = 0;
		TotalDelay = 0;
		CurNumofSimPkts = 0;
		TotalNumofCompletePkts = 0;

		for (n = 0; n < NumofServers; n++)
		{
			while (!Queue[n].empty()) Queue[n].removeFront();     // keep the queue empty
			time_departure_event[n] = 1e30;                       // the time when the next departure event occurs
		}

		time_arrival_event = ExpRan(1.0 / (NumofServers*Lambda[i]));      // the time when the next arrival event occurs

		while (CurNumofSimPkts <= TotalNumofSimPkts)   // simulation starts
		{
			/*** Determine the type of the next occuring event ***/
			min_time_next_event = time_arrival_event;
			next_event_type = NumofServers;        // arrival event
			for (n = 0; n < NumofServers; n++)
			{
				if (time_departure_event[n]< min_time_next_event)
				{
					min_time_next_event = time_departure_event[n];
					next_event_type = n;
				}
			}
			CurTime = min_time_next_event;
			/*****************************************************/

			if (next_event_type == NumofServers)
				/*** calls the arrival routine ***/
			{
				/*************************** Power of 2 Choices ************************************
				
				/******** Sample 2 servers *******/
				SIndex[0] = GenIntegerSeed(NumofServers);    // generate an integer between 0 and N-1
				do {
					SIndex[1] = GenIntegerSeed(NumofServers);
				} while (SIndex[0] == SIndex[1]);

				ArrivalID = SIndex[0];
				minSampleQ = Queue[ArrivalID].getQueueLength();

				/***Join the least-loaded server ***/
				for (j = 1; j < 2; j++)
				{
					tempQ = Queue[SIndex[j]].getQueueLength();
					if (tempQ < minSampleQ)
					{
						minSampleQ = tempQ;
						ArrivalID = SIndex[j];
					}
				}

				/*******************************************************************************/

				if (Queue[ArrivalID].empty() == 1)
				{
					time_departure_event[ArrivalID] = CurTime + ExpRan(1.0);   // set the time when the next departure event happens
				}

				Queue[ArrivalID].addBack(CurTime);                       // insert the packet into the queue
				CurNumofSimPkts = CurNumofSimPkts + 1;                   // Number of issued packets increases by 1
				time_arrival_event = CurTime + ExpRan(1.0 / (NumofServers*Lambda[i]));  // set the time when the next arrival event happens
			}
			else
				/*** calls the departure routine ***/
			{
				TotalDelay = TotalDelay + CurTime - Queue[next_event_type].header->next->aTime;
				TotalNumofCompletePkts = TotalNumofCompletePkts + 1;
				Queue[next_event_type].removeFront();
				if (Queue[next_event_type].empty() == 1)
				{
					time_departure_event[next_event_type] = 1e30;   // if the queue is empty, set arrival process as next event
				}
				else                            
				{
					time_departure_event[next_event_type] = CurTime + ExpRan(1.0);      // set the time when the next departure event happens
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

long long GenInteger(long long z)
{
	double u;
	long long p;
	u = myrand();
	p = (long long)(z*u);
	return p;
}

long long RandSeed(){   
	static const unsigned long long a = 1664525;
	static const unsigned long long c = 1013904223;
	static const unsigned long long m = 0xFFFFFFFF;

	return randomX = (randomX * a + c) & m;
}

double genUniformSeed(void){
	const unsigned long long max = 0xFFFFFFFF;
	return (double)RandSeed() / (double)(max + 1);
}

int GenIntegerSeed(int z)
{
	double u;
	int p;
	u = genUniformSeed();
	p = (int)(z*u);
	return p;
}