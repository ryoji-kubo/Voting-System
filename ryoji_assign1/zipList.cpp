#include "zipList.h"
#include "participant.h"
#include <cstdio>
#include<iostream>
#include<iomanip>
#include<cstring>

using namespace std;


VotedNode::VotedNode(Voter v){  //constructor
    char f[size];
    char l[size];
    strcpy(f, v.getFirst());
    strcpy(l, v.getLast());
    int r = v.getRIN();
    int z = v.getZIP();
    bool vStatus = v.getVote();

    this->VPtr = new Voter(f,l,r,z,vStatus);
}
VotedNode::~VotedNode(){        //destructor
    delete this->VPtr;
}
//====================================
VotedList::VotedList ()
{
	this->head = NULL;
	this->tail = NULL;
}
//====================================
VotedList::~VotedList () // destructor to clean up all nodes
{
	while(!empty())
		removeFront();
	this->head = NULL;
	this->tail = NULL;
}
//====================================
bool VotedList::empty() const // is list empty?
{
	return(this->head==NULL);
}
//====================================
const Voter& VotedList::front() const // get front element
{
	if(!empty())
		return *this->head->VPtr;       //dereference the pointer to the voter (return the Voter object)
	else
		throw runtime_error ("List is Empty");
}
//====================================
void VotedList::addBack(const Voter& v) // add to front of list
{
	VotedNode *newVotedNode = new VotedNode(v);
	
	if(empty())
		head=newVotedNode;
	else
		tail->next = newVotedNode;
	tail = newVotedNode;
}
//====================================
void VotedList::removeFront() // remove front item list
{
	if(!empty())
	{
		VotedNode *tmp = this->head;
		if(head == tail)	//if last element is going to be removed
			head=tail=NULL;

		else
			this->head = this->head->next;
		delete tmp;
	}

}
//====================================
void VotedList::displayAll() const      //display everything (name and all) for each node
{
    VotedNode *curr=head;
    while(curr!=NULL)
    {
        Voter v = *curr->VPtr;
        v.display();
        curr=curr->next;
    }
}

void VotedList::displayID() const       //display ID for each node
{
    VotedNode *curr=head;
    while(curr!=NULL)
    {
        Voter v = *curr->VPtr;
        v.displayID();
        curr=curr->next;
    }
}
int VotedList::count(){
    int counter=0;
    VotedNode *curr=head;
    while(curr!=NULL){
        counter++;
        curr=curr->next;
    }
    return counter;
}
void VotedList::deleteVoter(int r){
    VotedNode *curr = this -> head;               //this will be the current node
    while(curr!=NULL){                  //while we haven't seen through all the content
        if(curr->VPtr->getRIN() == r){            //if the RIN of the current node matches with the desired RIN
            if(curr == head && head == tail){       //case 1: current is on head and it is the last element
                head=tail=NULL;                     //head and tail point to NULL
            }
            else if(curr == head){                  //case 2: current is on head (but not the last element)
                this->head=this->head->next;        //head should be the next element
            }                                      
            else if(curr == tail){                  //case 3: current is on tail (but there are elements before)
                VotedNode *tmp = head;                //use tmp node to find the previous node (one before tail)
                while(tmp->next!=tail){             //while the tmp node is not the node before tail
                    tmp = tmp-> next;               //move the tmp node
                }
                tmp->next = NULL;                   //tmp node's next should point to NULL
                tail = tmp;                         //tail should be the tmp node
            }
            else{                                   //case 4: current is in the middle
                VotedNode *tmp = head;                //use tmp node to find the previous node
                while(tmp->next!=curr){             //while the tmp node is not the node before current
                    tmp = tmp->next;                //move the tmp node
                }
                tmp->next = curr->next;             //tmp's next should be curr's next
            }
            delete curr;            //delete curr
            break;               //break loop
        }
        curr = curr->next;  //move curr
    }
}


ZipNode::ZipNode(int z, const Voter v){
    this->elem = z;
    this->vListPtr = new VotedList;
    this->vListPtr->addBack(v);
}
//====================================
ZipNode::~ZipNode(){
    delete vListPtr;
}
//====================================
ZipList::ZipList ()
{
	this->head = NULL;
	this->tail = NULL;
}
//====================================
ZipList::~ZipList () // destructor to clean up all nodes
{
	while(!empty())
		removeFront();
	this->head = NULL;
	this->tail = NULL;
}
//====================================
bool ZipList::empty() const // is list empty?
{
	return(this->head==NULL);
}
//====================================
const int& ZipList::front() const // get front element
{
	if(!empty())
		return this->head->elem;
	else
		throw runtime_error ("List is Empty");
}
//====================================
void ZipList::addBack(const int& z, const Voter v) // add to back of list
{
	ZipNode *newZipNode = new ZipNode(z, v);
	
	if(empty())
		head=newZipNode;

	else
		tail->next = newZipNode;
	tail = newZipNode;
}
//====================================
void ZipList::removeFront() // remove front item list
{
	if(!empty())
	{
		ZipNode *tmp = this->head;
		if(head == tail)	//if last element is going to be removed
			head=tail=NULL;

		else
			this->head = this->head->next;
		delete tmp;
	}

}
//====================================
void ZipList::displayAll() const        //display All (name and everything)
{
		ZipNode *curr=head;
		while(curr!=NULL)
		{
            printf("<%d>\n", curr->elem);
            curr->vListPtr->displayAll();
			curr=curr->next;
		}
}
void ZipList::displayID() const         //display the ID
{
		ZipNode *curr=head;
		while(curr!=NULL)
		{
            printf("<%d>\n", curr->elem);
            curr->vListPtr->displayID();
			curr=curr->next;
		}
}
bool ZipList::existNode(int z){         //search through the list and see if specific ZIP exists
    ZipNode *curr = this -> head;               //this will be the current node
    while (curr!=NULL){
        if(curr->elem==z){             //if found
            return 1;
        }
        curr = curr->next;              //move current
    }
    return 0;
}


void ZipList::insert(Voter v){          //insert voter 
    int z = v.getZIP();                  //desired zip code
    bool exist = existNode(z);            //see if the zip code already exists                
    if (exist){                 //if exists
        ZipNode *curr = this-> head;        
        while(curr->elem != z){
            curr = curr->next;                  //move until the node where zip code matches
        }
        curr->vListPtr->addBack(v);              //add the voter object to the back of the list;
    }
    else {                       //if it doesnt exist
        this->addBack(z, v);          //add new node to ZipList
    }
}

void ZipList::printVoters(int z){       //printing the ID in rin
    ZipNode *curr = this-> head;
    while(curr->elem != z){
        curr = curr->next;                  //move until the node where zip code matches
    }
    printf("ZIPCODE: %d - # Votes: %d\n",z, curr->vListPtr->count());
    curr->vListPtr->displayID();
}

int ZipList::nodeCount(){       //count how many nodes
    int counter = 0;
    ZipNode *curr = this->head;
    while(curr!=NULL){
        counter++;
        curr = curr->next;
    }
    return counter;
}

int ZipList::totalCount(){      //give the total count
    int counter = 0;
    ZipNode *curr = this->head;
    while(curr!=NULL){
        counter += curr->vListPtr->count();
        curr = curr->next;
    }
    return counter;
}

void ZipList::output(){
    int arraySize = nodeCount();        //count how many nodes there are, make it the array size
    int zipArray[arraySize];    //an array to keep the zip code of the nodes
    int countArray[arraySize];  //an array to keep the count of the voters of the nodes
    ZipNode *curr = this->head;
    for (int i=0; i<arraySize; i++){
        zipArray[i]=curr->elem;
        countArray[i]=curr->vListPtr->count();
        curr = curr->next;
    }
    //SORTING ALGORITHM (Selection Sort) - reference:https://www.tutorialspoint.com/cplusplus-program-to-implement-sorted-array#:~:text=output&text=In%20the%20above%20program%2C%20selectionSort,the%20element%20currently%20at%20i.
    int i, j, max, tmp1, tmp2;
    for (i=0; i<arraySize-1; i++){
        max = i;
        for (j = i + 1; j < arraySize; j++){
            if (countArray[j] > countArray[max]){
                max = j;
            }
            tmp1 = countArray[i];
            countArray[i] = countArray[max];
            countArray[max] = tmp1;

            tmp2 = zipArray[i];
            zipArray[i]=zipArray[max];
            zipArray[max]=tmp2;
        }
    }
    for (int i = 0; i<arraySize;i++){       //printing the array
        printf("ZIPCODE: %d - # Votes: %d\n", zipArray[i],countArray[i]);
    }
}

void ZipList::deleteNode(Voter v){
    int z = v.getZIP();         //get the zip of target
    int r = v.getRIN();         //get the rin of target
    ZipNode *curr = this->head;
    while(curr->elem != z){     //move through ziplist until target zip is reached
        curr = curr-> next;
    }
    curr->vListPtr->deleteVoter(r); //invoke deletion of Voter by passing the RIN;
    if(curr->vListPtr->empty()){    //if deletion led to emptying the VoterList
        if(curr == head && head == tail){       //case 1: current is on head and it is the last element
            head=tail=NULL;                     //head and tail point to NULL
        }
        else if(curr == head){                  //case 2: current is on head (but not the last element)
            this->head=this->head->next;        //head should be the next element
        }                                   
        else if(curr == tail){                  //case 3: current is on tail (but there are elements before)
            ZipNode *tmp = head;                //use tmp node to find the previous node (one before tail)
            while(tmp->next!=tail){             //while the tmp node is not the node before tail
                tmp = tmp-> next;               //move the tmp node
            }
            tmp->next = NULL;                   //tmp node's next should point to NULL
            tail = tmp;                         //tail should be the tmp node
        }
        else{                                   //case 4: current is in the middle
            ZipNode *tmp = head;                //use tmp node to find the previous node
            while(tmp->next!=curr){             //while the tmp node is not the node before current
                tmp = tmp->next;                //move the tmp node
            }
            tmp->next = curr->next;             //tmp's next should be curr's next
        }
        delete curr;            //delete curr
    }
}