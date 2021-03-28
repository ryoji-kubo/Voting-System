#include "participant.h"
//LINKED LIST STRUCUTURE TAKEN FROM:
//============================================================================
// Name         : lab6.2.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 04-11-2019
// Date Modified: 15-03-2020 
// Copyright    : All rights are reserved
// Description  : Linked-List implementation of Queue
//============================================================================

#ifndef ZIPLIST
#define ZIPLIST
class VotedNode
{
	private:
		Voter* VPtr; //pointer to Voter object in Hash
		VotedNode* next; //Link (pointer) to the next Node
		
	public:
		VotedNode(const Voter v); // constructor
        ~VotedNode();		//destructor
		friend class VotedList;

};
//============================================
class VotedList
{
	private:
		VotedNode * head; // pointer to the head of list
		VotedNode * tail; // pointer to the tail of the list
	public:
		VotedList (); // empty list constructor
		~VotedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const Voter& front() const; // get front element
		void addBack(const Voter& v); // add element to back of list
		void removeFront(); // remove front item list
		void displayAll() const;
		void displayID() const;
        int count();    //count the number of voters in each VotedList
        void deleteVoter(int r);        //delete specific voter with RIN
};

class ZipNode
{
	private:
		int elem; //data element (type int in this case)
		ZipNode* next; //Link (pointer) to the next Node
        VotedList* vListPtr;    //Pointer to the list of Voted participants

		
	public:
		ZipNode(int z, const Voter v); //constructor
        ~ZipNode();  //destructor
		friend class ZipList;

};
//============================================
class ZipList
{
	private:
		ZipNode * head; // pointer to the head of list
		ZipNode * tail; // pointer to the tail of the list
	public:
		ZipList (); // empty list constructor
		~ZipList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const int& front() const; // get front element
		void addBack(const int& z, const Voter v); // add element to back of list
		void removeFront(); // remove front item list
		void displayAll() const;
		void displayID() const;
        bool existNode(int r);      //search through the list and see if specific ZIP exists
        void insert(const Voter v);     //inserts the Voter object to the ZipList
        void printVoters(int z);    //print the voters at a specific zip code
        int nodeCount();         //counts how many nodes there are
        int totalCount();        //counts the total number of Voters who have voted
        void output();       //produce an output list of zipcode along with the number of voters marked as YES is displayed per line
        void deleteNode(const Voter v);    //search through the list and remove specific Voter
};

#endif