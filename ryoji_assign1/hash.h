#ifndef HASH
#define HASH

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

//============================================
class Node
{
	private:
		Voter elem; //data element (Generic type E in this case)
		Node* next; //Link (pointer) to the next Node
		
	public:
		Node(Voter elem) : elem(elem)
		{}
		friend class MyLinkedList;

};
//============================================
class MyLinkedList
{
	private:
		Node * head; // pointer to the head of list
		Node * tail; // pointer to the tail of the list
	public:
		MyLinkedList (); // empty list constructor
		~MyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const Voter& front() const; // get front element
		void addBack(const Voter& elem); // add element to back of list
		void removeFront(); // remove front item list
		void displayAll() const;
        bool existNode(int r);      //search through the list and see if specific RIN exists
        void searchNode(int r);     //search through the list and display specific RIN
        void vRegNode(int r, bool& changed);       //search throuh the list and change the voting status of specific RIN
        void deleteNode(int r);    //search through the list and remove specific RIN
        const Voter& returnV(int r);    //returns the element at specific RIN
        int count();    //counts the number of voters in the linkedlist
};

//============================================
class Hash{
    private:
        int m;       //size of the hash table
        MyLinkedList **TPtr;    //pointer to an array of pointers to the linkedList

    public:
        Hash(int n);         //constructor
        ~Hash();                //destructor
        bool empty() const;     //checks if the Hash Table is empty
        void insert(Voter v);    //insert a Voter to Hash
        void remove(int x);   //remove at a specific RIN
        void free();        //frees the pointer (checks if the linkedList has become empty and deletes it)
        int hFunction(int x);   //calculate the key using the hash function
        bool exist(int x); //search if specific RIN exists
        void search(int x); //search for the record of a specific RIN
        void vRegister(int x, bool& changed); //register the voter at a specific RIN as having voted 
        void display();         //displays the content of the hash table
        const Voter& returnV(int r); //returns the element at specific RIN
        int totalCount();       //count the total number of votes
};

#endif