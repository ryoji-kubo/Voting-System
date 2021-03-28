#include "participant.h"
#include "hash.h"
#include "zipList.h"
#include "mvote.h"
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cstring>

using namespace std;

int main(int argc, char *argv[]){

    char filename[100];
    strcpy(filename, argv[2]);      //get filename

    char* num = argv[4];
    int m = atoi(num);          //get the size for the hash table
    
    Hash hTable(m);             //hash table
    ZipList zList;              //singly linked list for zip code

    read(filename, hTable);        //read the file

    while(1){           //while running
        char input[15000];          //buffer for input
        char i1[100], i2[100], i3[100], i4[100], i5[100];           //buffer for each argument
        int option;                 //to check the option
        fgets(input, 15000, stdin);     //get the input from prompt
        option = sscanf(input, "%s %s %s %s %s", i1, i2, i3, i4, i5);       //scan and see how many input you got (matches)
        if (option == 1){           //if 1 match
            if (strcmp(i1, "v")==0){        //show the total number of voted people
                numVoters(zList);      
            }
            else if (strcmp(i1, "perc")==0){    //show the percentage
                percentage(hTable, zList);
            }
            else if (strcmp(i1,"exit")==0){     //exit the loop
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(i1,"display")==0){      //display all the content
                display(hTable,zList);
            }
            else if (strcmp(i1, "o")==0){       //output the voted ppl
                output(zList);
            }
        }
        else if (option == 2){  //if 2 matches
            if (strcmp(i1, "l")==0){    //lookup rin
                char* n = i2;
                int r = atoi(n);
                look(r, hTable);
            }
            else if (strcmp(i1, "d")==0){       //delete rin
                char* n = i2;
                int r = atoi(n);
                del(r, hTable, zList);
            }
            else if (strcmp(i1, "r")==0){       //register voted status = Y
                char* n = i2;
                int r = atoi(n);
                registerVoter(r, hTable, zList);
            }
            else if (strcmp(i1, "bv")==0){          //NEEDS WORK BULK CHANGE
                char* fileName = i2;
                bulkVote(fileName,hTable,zList);        
            }
            else if (strcmp(i1, "z")==0){   //print the number of all participants at the specific zip
                char* n = i2;
                int z = atoi(n);
                printVoted(z, zList);    
            }
        }
        else if (option == 5){          //if 5 matches
            if (strcmp(i1, "i")==0){        //insert another voter
                char* n = i2;
                int r = atoi(n);
                char* num = i5;
                int z = atoi(num);
                insert(r, i3, i4, z, hTable);
            }
        }
        else{
            printf("INVALID INPUT\n");
        }
    }
    return 0;
};

void look(int r, Hash& hTable){
    hTable.search(r);
}
void insert(int r, const char l[], const char f[], int z, Hash& hTable){
    Voter v(f, l, r, z);
    hTable.insert(v);
}
void del(int r, Hash&hTable, ZipList& zList){
    if (hTable.exist(r)){
        Voter v = hTable.returnV(r);
        hTable.remove(r);
        if (v.getVote()){
            zList.deleteNode(v);
        }
    }
    else{
        printf("ERROR: No Such Registered ID Number\n");
    }
}
void registerVoter(int r, Hash& hTable, ZipList& zList){
    bool changed = 0;               //flag as vote status not having changed
    hTable.vRegister(r,changed);        //register vote, if status changes then flag changes
    if (changed){                       //if vote status changes
        Voter v = hTable.returnV(r);        //get voter object
        zList.insert(v);            //insert into zList
    }
}
void numVoters(ZipList& zList){
    printf("Total # of Votes: %d\n", zList.totalCount());
}
void percentage(Hash& hTable, ZipList& zList){
    int numVoted = zList.totalCount();      //get total # voted
    int numVoter = hTable.totalCount();     //get total # voters
    if (numVoter != 0){             //safe guard to avoid division by 0
        double percent = numVoted/(double)numVoter * 100;
        printf("Percentage: %.2f%%\n", percent);
    }
    else{
        printf("No one is Registered\n");
    }
}
void printVoted(int z, ZipList& zList){     
    if (zList.existNode(z)){            //see if voted record exists on that zip code
        zList.printVoters(z);           //print
    }
    else{
        printf("No Record on Specified ZIP CODE\n");
    }
}
void output(ZipList& zList){
    if (!zList.empty()){            //see if voted record exists
        zList.output();           //print
    }
    else{
        printf("No VOTED Record\n");
    }
}

void display(Hash& hTable, ZipList& zList){     //display everything
    printf("=========HASH TABLE=========\n");
    hTable.display();
    printf("============================\n");
    printf("\n");
    printf("=========ZIP LIST=========\n");
    zList.displayAll();
    printf("============================\n");
    printf("\n");
}

void read(const char filename[], Hash& hTable){     //reading the file - https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm, https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
    int rin, zip;
    char first[100], last[100];             //buffer to get the content

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(filename, "r");              //open to read
    if (fp == NULL)                         //if no content
        exit(EXIT_FAILURE);             

    while ((read = getline(&line, &len, fp)) != -1) {       //read every line
        fscanf(fp, "%d %s %s %d", &rin, last, first, &zip);     //get the content
        insert(rin, last, first, zip, hTable);          //insert into hash table
    }
    fclose(fp);
    if (line)
        free(line);             //free the memory used for line
}

void bulkVote(const char filename[], Hash& hTable, ZipList& zList){     //bulkVoting - https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm, https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
    int rin;            //input container

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(filename, "r");          //open file reading mode
    if (fp == NULL)                 //if no content
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {           //read every line
        fscanf(fp, "%d", &rin);                         //get the content
        registerVoter(rin, hTable, zList);              //register the voted status to Y
    }
    fclose(fp);
    if (line)
        free(line);                 //free the memory
}