#include<cstdio>
#include<cstring>
#include "participant.h"

using namespace std;

Voter::Voter(const char f[], const char l[], int rin, int z, bool v){
    strcpy(first, f);
    strcpy(last, l);
    RIN = rin;
    zip = z;
    vote = v;
}
const char* Voter::getFirst(){
    return first;
}
const char* Voter::getLast(){
    return last;
}
int Voter::getRIN(){
    return RIN;
}

int Voter::getZIP(){
    return zip;
}

bool Voter::getVote(){
    return vote;
}

void Voter::setVote(){
    vote = 1;
}

void Voter::display(){
    if (vote)
        printf("Name: %s %s RIN: %d ZIP: %d Vote: Y\n" , first, last, RIN, zip);
    else
        printf("Name: %s %s RIN: %d ZIP: %d Vote: N\n" , first, last, RIN, zip);    
}

void Voter::displayID(){
    printf("RIN: %d\n", RIN);
}