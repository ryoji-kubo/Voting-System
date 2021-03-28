#include "hash.h"
#include "participant.h"
#include <cstdio>
#include<iostream>
#include<iomanip>

using namespace std;



//====================================
MyLinkedList::MyLinkedList ()
{
	this->head = NULL;
	this->tail = NULL;
}
//====================================
MyLinkedList::~MyLinkedList () // destructor to clean up all nodes
{
	while(!empty())
		removeFront();
	this->head = NULL;
	this->tail = NULL;
}
//====================================
bool MyLinkedList::empty() const // is list empty?
{
	return(this->head==NULL);
}
//====================================
const Voter& MyLinkedList::front() const // get front element
{
	if(!empty())
		return this->head->elem;
	else
		throw runtime_error ("List is Empty");
}
//====================================
void MyLinkedList::addBack(const Voter& elem) // add to front of list
{
	Node *newNode = new Node(elem);
	
	if(empty())
		head=newNode;

	else
		tail->next = newNode;
	tail = newNode;
}
//====================================
void MyLinkedList::removeFront() // remove front item list
{
	if(!empty())
	{
		Node *tmp = this->head;
		if(head == tail)	//if last element is going to be removed
			head=tail=NULL;

		else
			this->head = this->head->next;
		delete tmp;
	}

}
//====================================
void MyLinkedList::displayAll() const       //display all the content
{

		Node *curr=head;
		while(curr!=NULL)
		{
			curr->elem.display();
			curr=curr->next;
		}
}
//====================================
bool MyLinkedList::existNode(int r){
    Node *curr = this -> head;               //this will be the current node
    while (curr!=NULL){
        if(curr->elem.getRIN()==r){             //if found
            return 1;
        }
        curr = curr->next;              //move current
    }
    return 0;
}
//====================================
void MyLinkedList::searchNode(int r){
    Node *curr = this -> head;               //this will be the current node
    while (curr!=NULL){
        if(curr->elem.getRIN()==r){             //if found
            curr->elem.display();               //display
            break;
        }
        curr = curr->next;              //move current
    }
}
//====================================
void MyLinkedList::vRegNode(int r, bool &changed){
    Node *curr = this -> head;               //this will be the current node
    while (curr!=NULL){
        if(curr->elem.getRIN()==r){             //if found
            if (curr->elem.getVote()){          //if already voted
                printf("Specified Registered ID Number already has Status Voted\n");
            }
            else{
                curr->elem.setVote();       //set the vote to Y
                changed = 1;                //flag it as having changed
            }
            break;
        }
        curr = curr->next;              //move current
    }
}
//====================================
void MyLinkedList::deleteNode(int r){    //search through the list if elem exists
    Node *curr = this -> head;               //this will be the current node
    while(curr!=NULL){                  //while we haven't seen through all the content
        if(curr->elem.getRIN() == r){            //if the RIN of the current node matches with the desired RIN
            if(curr == head && head == tail){       //case 1: current is on head and it is the last element
                head=tail=NULL;                     //head and tail point to NULL
            }
            else if(curr == head){                  //case 2: current is on head (but not the last element)
                this->head=this->head->next;        //head should be the next element
            }                                      
            else if(curr == tail){                  //case 3: current is on tail (but there are elements before)
                Node *tmp = head;                //use tmp node to find the previous node (one before tail)
                while(tmp->next!=tail){             //while the tmp node is not the node before tail
                    tmp = tmp-> next;               //move the tmp node
                }
                tmp->next = NULL;                   //tmp node's next should point to NULL
                tail = tmp;                         //tail should be the tmp node
            }
            else{                                   //case 4: current is in the middle
                Node *tmp = head;                //use tmp node to find the previous node
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
//====================================
const Voter& MyLinkedList::returnV(int r){
    Node *curr = this -> head;
    while (curr!=NULL){
        if (curr->elem.getRIN()==r){
            return curr->elem;
        }
        curr = curr->next;
    }
    throw runtime_error ("No Such Voter");
}
int MyLinkedList::count(){      //give total count of linked list
    int counter = 0;
    Node *curr = this -> head;
    while (curr!=NULL){
        counter++;
        curr = curr->next;
    }
    return counter;
}

Hash::Hash(int n){          //constructor of the hash table
    m = n;             //set the size of table to n
    TPtr = new MyLinkedList*[m];
    for (int i = 0; i<m; i++){
        TPtr[i]  = NULL;
    }
};

Hash::~Hash(){              //destructor to clean up the array of pointers
    for (int i=0; i<m; i++){
        delete TPtr[i];
    }
    delete[] TPtr;
};

bool Hash::empty() const{       //checks if the hash table is empty
    for (int i=0; i<m; i++){
        if (TPtr[i] != NULL){
            return 0;
        }
    }
    return 1;
};

void Hash::insert(Voter v){               //insert Voter in the hash table
    int key = v.getRIN();
    int index = hFunction(key);
    if (TPtr[index] == NULL){
        TPtr[index] = new MyLinkedList;
    }
    TPtr[index]->addBack(v);
};

int Hash::hFunction(int x){         //hash function simple!
    return x%m;
};

bool Hash::exist(int x){            //check if the specific rin exists
    int index = hFunction(x);
    if  (TPtr[index]!=NULL){
        bool found;
        found = TPtr[index]->existNode(x);
        if (found){
            return 1;  
        }
        else{
            return 0;
        }
    }
    else{
       return 0;
    }
}

void Hash::search(int x){           //look for the specific rin
    bool e = exist(x);
    if (e){
        int index = hFunction(x);
        TPtr[index]->searchNode(x);
    }
    else{
        printf("ERROR: No Such Registered ID Number\n");
    }
}

void Hash::vRegister(int x, bool &changed){     //register the rin and voted status = Y
    bool e = exist(x);
    if (e){
        int index = hFunction(x);
        TPtr[index]->vRegNode(x, changed);
    }
    else{
        printf("ERROR: No Such Registered ID Number\n");
    }
}

void Hash::remove(int x){       //remove specific RIN
    bool e = exist(x);
    if (e){
        int index = hFunction(x);
        TPtr[index]->deleteNode(x);
        free();
    }
    else{
        printf("ERROR: No Such Registered ID Number\n");
    }
};

void Hash::free(){          //to check if the linkedlist has been freed and to free the memory
    for (int i = 0; i<m; i++){
        if (TPtr[i] != NULL){
            bool empty;
            empty = TPtr[i]->empty();
            if (empty){
                MyLinkedList* tmp = TPtr[i];  
                TPtr[i] = NULL;
                delete tmp;
            }
        }
    }
}

void Hash::display(){       //display all the content of hash
    for (int i = 0; i<m; i++){
        if (TPtr[i] == NULL){
            printf("index %d: Empty\n", i);
        }
        else{
            printf("index %d\n", i);
            TPtr[i]->displayAll();
        }
    }
};

const Voter& Hash::returnV(int r){  //returns the element at specific RIN
    int index = hFunction(r);
    return TPtr[index]->returnV(r);
}

int Hash::totalCount(){        //give back the total count of the voter
    int counter = 0;
    for (int i=0; i<m; i++){
        if (TPtr[i] != NULL){
            counter += TPtr[i]->count();
        }
    }
    return counter;
};