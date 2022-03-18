//Hayden Owens
//CSE 20311
//lifefunc.h

//header file for playlife.c and lifefunc.c, contains function prototypes

void initBoard(bool board[][BOARDSIZE+2]);
void display(bool board[][BOARDSIZE+2]);
void addlive(bool board[][BOARDSIZE+2], int row, int col);
void kill(bool board[][BOARDSIZE+2], int row, int col);
void step(bool board[][BOARDSIZE+2], bool tempboard[][BOARDSIZE+2]);


