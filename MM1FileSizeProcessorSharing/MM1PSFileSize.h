#include <iostream>
#include <string>
using namespace std;

typedef double ArrivalTime;        // arrival time
typedef double FileSize;       //file size



class DNode {                      // doubly linked list node
public:                 
	ArrivalTime aTime;             // node element value
	FileSize fSize;
	DNode* prev;                   // previous node in list
	DNode* next;                   // next node in list
	friend class DLinkedList;      // allow DLinkedList access
};

class DLinkedList {             // doubly linked list
public:
	DLinkedList();              // constructor
	~DLinkedList();             // destructor
	bool empty() const;             // is list empty?
	//const ArrivalTime& front() const;          // get front element
	//const DepatureTime& back() const;   		// get back element
	const long long& GetQueueLength() const;          
	//const WaitingTime& front() const;     
	void addFront(const ArrivalTime& arrival, const FileSize& filesize);        // add to front of list
	void addBack(const ArrivalTime& arrival, const FileSize& filesize);         // add to back of list
	void removeFront();             // remove from front
	void removeBack();              // remove from back
	DNode* GetMiniFileSize();
	void remove(DNode* v);          // remove node v
	//void RefreshDepatureTime(double service, double QueueLength);
	//void displayViaAge();
	//void displayViaName();
public:                  // local type definitions
	DNode* header;              // list sentinels
	DNode* trailer;
protected:                    // local utilities
	void add(DNode* v, const ArrivalTime& arrival, const FileSize& filesize);       // insert new node before v
};

DLinkedList::DLinkedList() {          // constructor
	header = new DNode;               // create sentinels
	trailer = new DNode;
	header->next = trailer;           // have them point to each other
	trailer->prev = header;
}

DLinkedList::~DLinkedList() {           // destructor
	while (!empty()) removeFront();     // remove all but sentinels
	delete header;                      // remove the sentinels
	delete trailer;
}
// insert new node before v
void DLinkedList::add(DNode* v, const ArrivalTime& arrival, const FileSize& filesize) {
	DNode* u = new DNode;       // create a new node
	u->aTime = arrival;   
	u->fSize = filesize;
	u->next = v;                // link u in between v
	u->prev = v->prev;              // ...and v->prev
	v->prev->next = u;
	v->prev = u;
	//v->prev->next = v->prev = u;
}

void DLinkedList::addFront(const ArrivalTime& arrival, const FileSize& filesize)  // add to front of list
{
	add(header->next, arrival, filesize);
}

void DLinkedList::addBack(const ArrivalTime& arrival, const FileSize& filesize)   // add to back of list
{
	add(trailer, arrival, filesize);
}

void DLinkedList::remove(DNode* v) {     // remove node v
	DNode* u = v->prev;                  // predecessor
	DNode* w = v->next;                  // successor
	u->next = w;                         // unlink v from list
	w->prev = u;
	delete v;
}

void DLinkedList::removeFront()       // remove from font
{
	remove(header->next);
}

void DLinkedList::removeBack()        // remove from back
{
	remove(trailer->prev);
} 


bool DLinkedList::empty() const        // is list empty?
{
	return (header->next == trailer);
}

/*
const ArrivalTime& DLinkedList::front() const    // get front element
{
	return header->next->aTime;
}

const DepatureTime& DLinkedList::back() const     // get back element
{
	return trailer->prev->dTime;
}*/

const long long& DLinkedList::GetQueueLength() const 
{
	DNode* u = header->next;
	long long count = 0;
	while (u != trailer)
	{
		count = count + 1;
		u = u->next;
	}
	return count;
}

DNode* DLinkedList::GetMiniFileSize()
{
	DNode* u = header->next;
	DNode* v = u;
	long long minfSize = 1e30;
	while (u != trailer)
	{
		if (minfSize > u->fSize)
		{
			minfSize = u->fSize ;
			v = u;
		}
		u = u->next;
	}
	return v;
}



/*void DLinkedList::displayViaAge() {                     //Displays person via age

	DNode*temp = header;

	while (temp != trailer)
	{

		//if(howold = age)
		cout << temp->elem << endl;
		temp = temp->next;
	}

	cout << temp->elem << endl;
}*/

