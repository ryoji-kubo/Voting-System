#ifndef PARTICIPANT
#define PARTICIPANT

const int size = 100;  //declaring the max length of first and last name as 100.
//using namespace std;

class Voter
{
private:
    char first[size];   //first name
    char last[size];    //last name
    int RIN;        //Residential Identification Number
    int zip;        
    bool vote;
public:
    Voter(const char f[], const char l[], int rin, int z, bool v = 0); //constructor -- reason for the const char* - https://stackoverflow.com/questions/1524356/c-deprecated-conversion-from-string-constant-to-char
    const char* getFirst();
    const char* getLast();
    int getRIN();   //gets the RIN
    int getZIP();   //gets the ZIP
    bool getVote(); //gets the Vote
    void setVote(); //sets the Vote
    void display(); //displays the content of the voter in a line 
    void displayID(); //displays the RIN of the voter     
};

#endif