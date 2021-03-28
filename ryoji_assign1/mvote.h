#ifndef MVOTE
#define MVOTE

void look(int r, Hash& hTable);     //look up specified RIN
void insert(int r, const char l[], const char f[], int z, Hash& hTable);    //insert new voter
void del(int r, Hash&hTable, ZipList& zList);       //delete voter
void registerVoter(int r, Hash& hTable, ZipList& zList);        //register voter and change voteStatus to Y
void numVoters(ZipList& zList);                 //print the total number of votes
void percentage(Hash& hTable, ZipList& zList);      //print the percentage of voted ratio
void printVoted(int z, ZipList& zList);         //print the RIN of Voted ppl of a specific ZipCode
void output(ZipList& zList);            //print the number of votes in each zip code in a decsending order
void display(Hash& hTable, ZipList& zList);         //display the hash table and the zip code linked list
void read(const char filename[], Hash& hTable);       //reads the file
void bulkVote(const char filename[], Hash& hTable, ZipList& zList);     //bulkVote option

#endif