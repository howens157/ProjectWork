//statesfunc.h
//Hayden Owens
//CSE 20311
//statesfunc.h contains function prototypes and the defintion for the struct State

typedef struct {    //define a struct State that holds three strings and an int
    char abbrev[3];
    char name[30];
    char cap[30];
    int year;
} State;

//function prototypes
int readUser(State states[]);
int readFile(char filename[], State states[]);
int compare(char str1[], char str2[]);
int prompt();
void display(State states[], int numStates);
void abbrevinfo(State states[], int numStates);
void putcap(State states[], int numStates);
void joinedyear(State states[], int numStates);
void listletter(State states[], int numStates);
