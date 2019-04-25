#include <iostream>
#include <string>
using namespace std;

typedef double ArrivalTime;        // arrival time

class DNode {                      // doubly linked list node
public:                 
	ArrivalTime aTime;             // node element value
	DNode* prev;                   // previous node in list
	DNode* next;                   // next node in list
	friend class DLinkedList;      // allow DLinkedList access
};

class DLinkedList {             // doubly linked list
public:
	DLinkedList();              // constructor
	~DLinkedList();             // destructor
	bool empty() const;             // is list empty?
	const ArrivalTime& front() const;          // get front element
	//const Elem& back() const;           // get back element
	//const WaitingTime& front() const;     
	void addFront(const ArrivalTime& arrival);        // add to front of list
	void addBack(const ArrivalTime& arrival);         // add to back of list
	void removeFront();             // remove from front
	void removeBack();              // remove from back
	double getQueueLength();       // get queue-length
	//void displayViaAge();
	//void displayViaName();
public:                  // local type definitions
	DNode* header;              // list sentinels
	DNode* trailer;
protected:                    // local utilities
	void add(DNode* v, const ArrivalTime& arrival);       // insert new node before v
	void remove(DNode* v);          // remove node v
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
void DLinkedList::add(DNode* v, const ArrivalTime& arrival) {
	DNode* u = new DNode;       // create a new node
	u->aTime = arrival;       
	u->next = v;                // link u in between v
	u->prev = v->prev;              // ...and v->prev
	v->prev->next = u;
	v->prev = u;
	//v->prev->next = v->prev = u;
}

void DLinkedList::addFront(const ArrivalTime& arrival)  // add to front of list
{
	add(header->next, arrival);
}

void DLinkedList::addBack(const ArrivalTime& arrival)   // add to back of list
{
	add(trailer, arrival);
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

double DLinkedList::getQueueLength()        // get queue-length
{
	double n = 0;
	DNode* tempNodeD = header->next;
	while (tempNodeD != trailer)
	{
		n = n + 1;
		tempNodeD = tempNodeD->next;
	}
	return n;
}

const ArrivalTime& DLinkedList::front() const    // get front element
{
	return header->next->aTime;
}



/*const Elem& DLinkedList::back() const     // get back element
{
	return trailer->prev->elem;
}*/

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
