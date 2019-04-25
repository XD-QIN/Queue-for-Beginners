#include "MM1PSFileSize.h"
#include <math.h>
#include <time.h>
#include <iomanip>
#include <fstream>

#define NumofSimPoints 1000
#define SampleFrequency 1
double Seed = 7;
double myrand();
double ExpRan(double);
int main(){ 
	 
	string filename;

	cout << "Enter the result file name: ";
	cin >> filename;
	

	ofstream ofile;
	ofile.open( filename.c_str() );
    
	cout << "lambda \tAvgDelay \tAvgQueueLength" << endl;
    ofile << "lambda \tAvgDelay \tAvgQueueLength" << endl;

	double TotalNumofSimPkts = 1e6;  // total number of simulated packets
	double CurNumofSimPkts=0;       // total number of packets which have been issued

	double TotalNumofCompletePkts = 0; // total number of packets which have been processed
	
	//double Lambda[NumofSimPoints] =        { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.93, 0.96, 0.99 };
	//double AvgTaskDelay[NumofSimPoints] =  {  0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,    0   };

	//double Lambda[NumofSimPoints] =       { 0.8, 0.9, 0.93, 0.96, 0.99 };
	//double AvgTaskDelay[NumofSimPoints] = {  0,    0,   0,    0,    0  };
	double lambda[NumofSimPoints] = { 1.5, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.95 };
	double AvgTaskDelay[NumofSimPoints] = { 0 }; 
	double AvgQueueLength[NumofSimPoints] = { 0 };

	double mu = 1.8;
	double serviceTime = 0;

	DLinkedList Queue;   // a single queue
	DNode* DepaturePkt;  // packet depature when depature event happen
	DNode* TempPktA;
	DNode* TempPktD;
	DNode* TempPktS;
	int i, j, SampleEventTimes;
	int next_event_type;
	double CurTime, min_time_next_event, TotalDelay, TotalQueueLength, tempSizeA, tempSizeD, EventIntervalTime;

	double time_next_event[3];   // time_next_event[0]: arrival event
	                             // time_next_event[1]: departure event
								 // time_next_event[2]: sampling event

	for (i = 0; i < NumofSimPoints; i++)     // number of arrival intensity
	{
		CurTime = 0;
		tempSizeD = 0;
		tempSizeA = 0;
		SampleEventTimes = 0;
		TotalDelay = 0;
		TotalQueueLength = 0;
		EventIntervalTime = 0;
		CurNumofSimPkts = 0;
		TotalNumofCompletePkts = 0;
		while (!Queue.empty()) Queue.removeFront();     // keep the queue empty
		time_next_event[0] = ExpRan(1.0 / lambda[i]);   // the time when the next arrival event occurs
		time_next_event[1] = 1e30;                      // the time when the next departure event occurs
		time_next_event[2] = SampleFrequency;                // the time when the next sampling event occurs

		while (CurNumofSimPkts <= TotalNumofSimPkts)   // simulation starts
		{
			/*** Determine the type of the next occuring event ***/
			min_time_next_event = 1e30;
			for (j = 0; j < 3; j++)
			{
				if (time_next_event[j] < min_time_next_event)
				{
					min_time_next_event = time_next_event[j];
					next_event_type = j;
				}
			}
			EventIntervalTime = min_time_next_event - CurTime; //time interval between two event
			CurTime = min_time_next_event;

			/*****************************************************/
			if (next_event_type == 0)
				/*** calls the arrival routine ***/
			{ 
				tempSizeA = ExpRan(1.0);
				if (Queue.empty() == 1)
				{
					time_next_event[1] = CurTime + 1.0 * tempSizeA / 1.0;   // if the queue is empty, set arrival process as next event
				}
				TempPktA = Queue.header->next;
				while (TempPktA != Queue.trailer) {
					TempPktA->fSize = TempPktA->fSize - (1.0 / Queue.GetQueueLength()) * EventIntervalTime;//update all the packetsize when arrival event happen
					TempPktA = TempPktA->next;
				}
				Queue.addBack(CurTime, tempSizeA);
				CurNumofSimPkts = CurNumofSimPkts + 1;             // Number of issued packets increases by 1
						
				time_next_event[0] = CurTime + ExpRan(1.0 / lambda[i]);  // set the time when the next arrival event happens	
				time_next_event[1] = CurTime + (1.0 * Queue.GetMiniFileSize()->fSize) / (1.0 / Queue.GetQueueLength());
			}
			else if (next_event_type == 1)
				/*** calls the departure routine ***/
			{	
				DepaturePkt = Queue.GetMiniFileSize();
				tempSizeD = DepaturePkt->fSize;
				TotalDelay = TotalDelay + CurTime - DepaturePkt->aTime;
				Queue.remove(DepaturePkt);
				TotalNumofCompletePkts = TotalNumofCompletePkts + 1;
				if (Queue.empty() == 1)
				{
					time_next_event[1] = 1e30;   // if the queue is empty, set arrival process as next event
				} 
				else                            
				{
					TempPktD = Queue.header->next;
					while (TempPktD != Queue.trailer) {
						TempPktD->fSize = TempPktD->fSize - tempSizeD;//update the file size when departure event happen
						TempPktD = TempPktD->next;
					}
					time_next_event[1] = CurTime + (1.0 * Queue.GetMiniFileSize()->fSize) / (1.0 / Queue.GetQueueLength());
				}
			}
			else
				/***calls the queue length sample event***/
			{
				TotalQueueLength = TotalQueueLength + Queue.GetQueueLength();
				SampleEventTimes = SampleEventTimes + 1;
				time_next_event[2] = CurTime + SampleFrequency;

				if (Queue.empty() == 1)
				{
					time_next_event[1] = 1e30;   // if the queue is empty, set arrival process as next event
				}
				else
				{
					TempPktS = Queue.header->next;
					while (TempPktS != Queue.trailer) {
						TempPktS->fSize = TempPktS->fSize - (1.0 / Queue.GetQueueLength()) * EventIntervalTime;//update the file size when departure event happen
						TempPktS = TempPktS->next;
					}
					time_next_event[1] = CurTime + (1.0 * Queue.GetMiniFileSize()->fSize) / (1.0 / Queue.GetQueueLength());
				}
			}		
		}
		
	    /******** Data Collection *******************/
	    
		AvgTaskDelay[i] = 1.0 * TotalDelay / TotalNumofCompletePkts;
		AvgQueueLength[i] = 1.0 * TotalQueueLength / (SampleEventTimes);
		cout  << lambda[i] << '\t' << setw(12) << setprecision(10) << AvgTaskDelay[i] << '\t' << setw(12) << setprecision(10) << AvgQueueLength[i] << endl;
		ofile << lambda[i] << '\t' << setw(12) << setprecision(10) << AvgTaskDelay[i] << '\t' << setw(12) << setprecision(10) << AvgQueueLength[i] << endl;
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
	p = -mean * log(u);
	return p;
}

