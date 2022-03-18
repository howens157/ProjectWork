//Hayden Owens
//CSE 20311
//project.c
//Tetris LITE!

//include libraries
#include "gfx2.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

//global constants for array variables
const int boardX = 10;
const int boardY = 22;
const int queuelen = 5;

//Square struct: every square on the board is a Square that has its type: what type of piece or empty, location,
//and state of rotation
typedef struct{
    char type;       //0: void, 1: I, 2: O, 3: T, 4: S, 5: Z, 6: J, 7: L
    int xloc;
    int yloc;
    int rotstate;   //state = 4: locked in
} Square;

//Color struct: stores the RGB values for a particular color in order to simplify changing of the draw color
typedef struct{
    int R;
    int G; 
    int B;
} Color;

//function prototypes
void initboard(Square board[][boardY+2]);
void initqueue(int queue[]);
void activeToBoard(Square active[], Square board[][boardY+2]);
void spawnNext(int queue[], Square board[][boardY+2], Square active[], bool *gotonext);
void clearLast(Square active[], Square board[][boardY+2]);
void initcolors(Color colors[]);
void setcolor(Color color);
void drawqueue(int queue[], Color colors[]);
void drawboard(Square board[][boardY+2], Color colors[]);
void movedown(Square board[][boardY+2], Square active[], bool *gotonext);
void drawblock(int x, int y, int size);
void moveleft(Square board[][boardY+2], Square active[]);
void moveright(Square board[][boardY+2], Square active[]);
void rotate(Square board[][boardY+2], Square active[]);
void fall(Square board[][boardY+2], Square active[], bool *gotonext);
int checkrows(Square board[][boardY+2], bool *gameover);
void clearrow(Square board[][boardY+2], int rownum);

int main()
{
    //initialize/declare variables
    Square board[boardX+2][boardY+2];
    int timer = 0;
    int queue[queuelen];
    bool gameover = false;
    bool userquit = false;
    bool gotonext = true;
    char c;
    Color colors[9];
    Square active[4];
    int score = 0;
    char scorebuffer[20];

    initcolors(colors);
    srand(time(NULL));
    initboard(board);
    initqueue(queue);
    gfx_open(500, 850, "Tetris LITE!");
    gfx_changefont("-sony-fixed-medium-r-normal--24-170-100-100-c-120-iso8859-1");
    
    while(!gameover && !userquit)   //the game will end when the user loses or quits
    {
        //all draws
        gfx_clear();
        setcolor(colors[8]);    //set to white
        gfx_rectangle(100, 180, 300, 600); //draw borders
        gfx_text(205, 25, "Queue:");    //and text
        sprintf(scorebuffer, "Score: %d", score);
        gfx_text(200, 825, scorebuffer);    //print current score
        gfx_rectangle(0, 27, 499, 68);
        drawqueue(queue, colors); 
        drawboard(board, colors);
        if(gotonext)    //checks if the last piece has been locked in place before the next piece can be spawned
            spawnNext(queue, board, active, &gotonext);
        if(timer%10 == 0)   //controls how quickly the piece will naturally fall
            movedown(board, active, &gotonext);
        score = score + checkrows(board, &gameover);
        gfx_flush();
        usleep(50000);
        timer++;
        if(gfx_event_waiting())
        {
            c = gfx_wait();
            switch(c)
            {
                case 'a':   //a will move the piece left
                    moveleft(board, active);
                    break;
                case 'd':   //d will move the piece right
                    moveright(board, active);
                    break;
                case 's':   //s will move the piece down
                    movedown(board, active, &gotonext);
                    break;
                case ' ':   //the spacebar will rotate the piece
                    rotate(board, active);
                    break;
                case 'z':   //z will cause the piece to instantly fall to the bottom
                    fall(board, active, &gotonext);
                    break;
                case 'q':   //q will exit the program
                    userquit = true;
                    break;
            }
        }
    }
    if(gameover)    //if the loop broke from the game ending and not the user quitting
    {               //then display a game over screen and the users score
        gfx_clear();
        setcolor(colors[8]);
        gfx_rectangle(100, 180, 300, 600);
        gfx_text(200, 825, scorebuffer);
        setcolor(colors[5]);
        gfx_text(190, 50, "GAME OVER");
        gfx_text(155, 100, "Press Q to Quit");
        drawboard(board, colors);
        while(1)    //and then wait for the user to quit
        {
            c = gfx_wait();
            if(c == 'q')
                return;
        }
    }
}

//initboard will initialize the Square structs in the booard
void initboard(Square board[][boardY+2])
{
    int i, j;
    for(i = 0; i < boardX+2; i++)       //loop through every Square in the board
    {
        for(j = 0; j < boardY+2; j++)
        {
            board[i][j].type = 0;   //set their type to 0 meaning it does not contain a tetris piece
            board[i][j].xloc = i;
            board[i][j].yloc = j;
            if(i == 0 || i == boardX+1 || j == 0 || j == boardY+1)  //if it is a border Square
                board[i][j].rotstate = 4;   //set its rotstate to 4 meaning the borders are solid and fixed
        }
    }
}

//initqueue will generate a queue of 5 random types of tetris pieces
void initqueue(int queue[])
{
    int i;
    for(i = 0; i < queuelen; i++)
    {
        queue[i] = rand()%7 + 1;    //generate a number between 1 and 7 to represent the next type of piece in the queue
    }
}

//activeToBoard will take the active[] of Squares controlled by the player and copy their values to the board
//at the appropriate location
void activeToBoard(Square active[], Square board[][boardY+2])
{
    int i;
    for(i = 0; i < 4; i++)
    {
        board[active[i].xloc][active[i].yloc].type = active[i].type;
        board[active[i].xloc][active[i].yloc].rotstate = active[i].rotstate;
    }
}

//clearlast will set the Squares in the board at the location of the active[] Squares back to being empty
//this is called in the movement functions in order to not duplicate the piece with each movement
void clearlast(Square active[], Square board[][boardY+2])
{
    int i;
    for(i = 0; i < 4; i++)
    {
        board[active[i].xloc][active[i].yloc].type = 0;
        board[active[i].xloc][active[i].yloc].rotstate = 0;
    }

}

//spawnNext will spawn a piece at the top of the board based on the next type in the queue, it will then
//shift the queue forward and generate a new piece at the back of the queue
void spawnNext(int queue[], Square board[][boardY+2], Square active[], bool *gotonext)
{
    int i;
    switch(queue[0])    //the Squares will be spawned in a different formation and locations based on the type of the piece
    {
        //each case statement will set the active squares to the next type in the queue and then set their locations
        //at the top of the board in the correct configuration and location
        case 1: //I piece
            for(i = 0; i < 4; i++)
            {
                active[i].type =  queue[0];
                active[i].rotstate = 0;
            }
            active[0].xloc = 4;   active[0].yloc = 2;
            active[1].xloc = 5;   active[1].yloc = 2;
            active[2].xloc = 6;   active[2].yloc = 2;
            active[3].xloc = 7;   active[3].yloc = 2;
            break;
        case 2: //O piece
            for(i = 0; i < 4; i++)
            {
                active[i].type =  queue[0];
                active[i].rotstate = 0;
            }
            active[0].xloc = 5;   active[0].yloc = 1;
            active[1].xloc = 5;   active[1].yloc = 2;
            active[2].xloc = 6;   active[2].yloc = 1;
            active[3].xloc = 6;   active[3].yloc = 2;
            break; 
        case 3: //T piece
            for(i = 0; i < 4; i++)
            {
                active[i].type =  queue[0];
                active[i].rotstate = 0;
            }
            active[0].xloc = 5;   active[0].yloc = 1;
            active[1].xloc = 4;   active[1].yloc = 2;
            active[2].xloc = 5;   active[2].yloc = 2;
            active[3].xloc = 6;   active[3].yloc = 2;
            break;
        case 4: //S piece
            for(i = 0; i < 4; i++)
            {
                active[i].type =  queue[0];
                active[i].rotstate = 0;
            }
            active[0].xloc = 5;   active[0].yloc = 1;
            active[1].xloc = 6;   active[1].yloc = 1;
            active[2].xloc = 4;   active[2].yloc = 2;
            active[3].xloc = 5;   active[3].yloc = 2;
            break;
        case 5: //Z piece
            for(i = 0; i < 4; i++)
            {
                active[i].type =  queue[0];
                active[i].rotstate = 0;
            }
            active[0].xloc = 4;   active[0].yloc = 1;
            active[1].xloc = 5;   active[1].yloc = 1;
            active[2].xloc = 5;   active[2].yloc = 2;
            active[3].xloc = 6;   active[3].yloc = 2;
            break;
        case 6: //L piece
            for(i = 0; i < 4; i++)
            {
                active[i].type =  queue[0];
                active[i].rotstate = 0;
            }
            active[0].xloc = 6;   active[0].yloc = 1;
            active[1].xloc = 4;   active[1].yloc = 2;
            active[2].xloc = 5;   active[2].yloc = 2;
            active[3].xloc = 6;   active[3].yloc = 2;
            break;
        case 7: //J piece
            for(i = 0; i < 4; i++)
            {
                active[i].type =  queue[0];
                active[i].rotstate = 0;
            }
            active[0].xloc = 4;   active[0].yloc = 1;
            active[1].xloc = 4;   active[1].yloc = 2;
            active[2].xloc = 5;   active[2].yloc = 2;
            active[3].xloc = 6;   active[3].yloc = 2;
            break;
    }
    activeToBoard(active, board);   //once the active[] Squares are correctly initialized, push them to the Board
    for(i = 0; i < queuelen-1; i++) //then update the queue
    {
        queue[i] = queue[i+1];
    }
    queue[queuelen-1] = 1 + rand()%7;
    *gotonext = false;  //and set gotonext back to false 
}

//initcolors will just initialize each of the 8 colors that will be used in the graphics of the program,
//note that a piece's color is in colors[] at the index of that pieces type. (Ex: Type 4 is an S piece which is green.
//colors[4] is green.)
void initcolors(Color colors[])
{
    //black
    colors[0].R = 0;
    colors[0].G = 0;
    colors[0].B = 0;
    //cyan
    colors[1].R = 0;
    colors[1].G = 255;
    colors[1].B = 255;
    //yellow
    colors[2].R = 255;
    colors[2].G = 255;
    colors[2].B = 0;
    //pink
    colors[3].R = 255;
    colors[3].G = 105;
    colors[3].B = 180;
    //green
    colors[4].R = 0;
    colors[4].G = 255;
    colors[4].B = 0;
    //red
    colors[5].R = 255;
    colors[5].G = 0;
    colors[5].B = 0;
    //blue
    colors[6].R = 0;
    colors[6].G = 0;
    colors[6].B = 255;
    //orange
    colors[7].R = 255;
    colors[7].G = 165;
    colors[7].B = 0;
    //white
    colors[8].R = 255;
    colors[8].B = 255;
    colors[8].G = 255;
}

//setcolor will set the draw color to whatever color was passed to it
void setcolor(Color color)
{
    gfx_color(color.R, color.G, color.B);
}

//drawqueue will draw the pieces in the queue at the top of the screen so the player can plan around what pieces are next
void drawqueue(int queue[], Color colors[])
{
    int x = 50;
    int y = 10;
    int i;
    for(i = 0; i < queuelen-1; i++) //for each piece
    {
        setcolor(colors[queue[i]]); //set the color according to the pieces type
        switch(queue[i])    //then draw the shape of the piece according to its type
        {
            //each piece consists of 4 squares that are drawn in different configurations, then the x location
            //at which to draw is updated based on the width of the piece that was just drawn
            case 1: //I
                drawblock(x, y+50, 25);
                drawblock(x+25, y+50, 25);
                drawblock(x+50, y+50, 25);
                drawblock(x+75, y+50, 25);
                x += 125;
                break;
            case 2: //O
                drawblock(x, y+25, 25);
                drawblock(x+25, y+25, 25);
                drawblock(x, y+50, 25);
                drawblock(x+25, y+50, 25);
                x += 75;
                break; 
            case 3: //T
                drawblock(x, y+50, 25);
                drawblock(x+25, y+50, 25);
                drawblock(x+50, y+50, 25);
                drawblock(x+25, y+25, 25);
                x += 100;
                break;
            case 4: //S
                drawblock(x, y+25, 25);
                drawblock(x+25, y+50, 25);
                drawblock(x+25, y+25, 25);
                drawblock(x+50, y+25, 25);
                x += 100;
                break;
            case 5: //Z
                drawblock(x, y+25, 25);
                drawblock(x+25, y+25, 25);
                drawblock(x+25, y+50, 25);
                drawblock(x+50, y+50, 25);
                x += 100;
                break;
            case 6: //L
                drawblock(x, y+50, 25);
                drawblock(x+25, y+50, 25);
                drawblock(x+50, y+50, 25);
                drawblock(x+50, y+25, 25);
                x += 100;
                break;
            case 7: //J
                drawblock(x, y+50, 25);
                drawblock(x+25, y+50, 25);
                drawblock(x+50, y+50, 25);
                drawblock(x, y+25, 25);
                x += 100;
        }
    }
}

//drawboard will draw a block at any Square in the board that is occupied by a tetris piece
void drawboard(Square board[][boardY+2], Color colors[])
{
    int x = 100;
    int y = 120;
    int i, j;
    for(i = 1; i < boardX+1; i++)   //for every Square in board
    {
        for(j = 1; j < boardY+1; j++)
        {
            if(board[i][j].type != 0)   //if the Square is not empty
            {
                setcolor(colors[board[i][j].type]); //set the color according to its type
                drawblock(x+30*(i-1), y+30*(j-1), 30);  //and draw a block at its location
            }
        }
    }
}

//drawblock will draw a tetris block of a given size at a given location
//A tetris block is a square with two concentric circles in order to minimize the amount needed to be drawn
//while still making the blocks easy to see
void drawblock(int x, int y, int size)
{
    gfx_rectangle(x, y, size, size);
    gfx_circle(x+size/2, y+size/2, size/2);
    gfx_circle(x+size/2, y+size/2, size/4);
}

//movedown will shift the active[] Squares down by one block
void movedown(Square board[][boardY+2], Square active[], bool *gotonext)
{
    int i, j;
    for(i = 0; i < 4; i++)  //for each Square in active
    {
        if(board[active[i].xloc][active[i].yloc+1].rotstate == 4)   //check if the block beneath it is locked in place
        {
            for(j = 0; j < 4; j++)  //if so, then set all active[] Squares to be locked as well
            {
                active[j].rotstate = 4;
            }
            activeToBoard(active, board);   //push active[] to the board
            *gotonext = true;   //and set gotonext to true so that the spawnNext() will be called in main
            return; //then return without moving the active[] piece
        }  
    }
    //if the active[] piece as room to move down,
    clearlast(active, board);   //clear its previous location
    for(i = 0; i < 4; i++)
    {
        active[i].yloc = active[i].yloc + 1;    //move its location down by one
    }
    activeToBoard(active, board);   //and push it to the board
}

//moveleft moves the active piece to the left one square
void moveleft(Square board[][boardY+2], Square active[])
{
    int i, j;
    for(i = 0; i < 4; i++)
    {
        if(board[active[i].xloc-1][active[i].yloc].rotstate == 4)   //if the piece is trying to move into a locked Square
            return;  //the move fails
    }   
    //if the piece has room to move
    clearlast(active, board);
    for(i = 0; i < 4; i++)
    {
        active[i].xloc = active[i].xloc - 1;    //shift each square to the left
    }
    activeToBoard(active, board);
}

//moveright moves the active piece to the right one square
void moveright(Square board[][boardY+2], Square active[])
{
    //the code is identical to moveleft but in the other direction
    int i, j;
    for(i = 0; i < 4; i++)
    {
        if(board[active[i].xloc+1][active[i].yloc].rotstate == 4)
            return;
    }
    clearlast(active, board);
    Square activenext[4];
    for(i = 0; i < 4; i++)
    {
        active[i].xloc = active[i].xloc + 1;
    }
    activeToBoard(active, board);
}

//rotate will rotate the active piece clockwise by 90 degrees
void rotate(Square board[][boardY+2], Square active[])
{
    clearlast(active, board);
    Square activenext[4];   //array to hold the potential next location of the piece
    int i;
    for(i = 0; i < 4; i++)  //copy active[] to activenext[]
        activenext[i] = active[i];

    //every piece has its own method of rotation and each piece rotates differently depending on what rotstate
    //it is currently in. Nested switch statements are used to first identify what type of piece is being rotated,
    //then what state of rotation it is currently in
    switch(active[0].type)
    {
        case 1: //I
            for(i = 0; i < 4; i++)  //due the the length of the I piece, it could potentiall rotate out of bounds,
                                    //to address this, the rotation fails if the I piece is too close to a border
            {
                if(active[i].xloc < 2 || active[i].xloc > boardX - 2 || active[i].yloc < 2 || active[i].yloc > boardY - 2)
                    return;
            }
            switch(active[0].rotstate)
            {
                case 0:
                    activenext[0].xloc = active[0].xloc+1;  activenext[0].yloc = active[0].yloc-2;
                    activenext[1].xloc = active[1].xloc+0;  activenext[1].yloc = active[1].yloc-1;
                    activenext[2].xloc = active[2].xloc-1;  activenext[2].yloc = active[2].yloc+0;
                    activenext[3].xloc = active[3].xloc-2;  activenext[3].yloc = active[3].yloc+1;
                    break; 
                case 1:
                    activenext[0].xloc = active[0].xloc+2;  activenext[0].yloc = active[0].yloc+1;
                    activenext[1].xloc = active[1].xloc+1;  activenext[1].yloc = active[1].yloc+0;
                    activenext[2].xloc = active[2].xloc-0;  activenext[2].yloc = active[2].yloc-1;
                    activenext[3].xloc = active[3].xloc-1;  activenext[3].yloc = active[3].yloc-2;
                    break;  
                case 2:
                    activenext[0].xloc = active[0].xloc-1;  activenext[0].yloc = active[0].yloc+2;
                    activenext[1].xloc = active[1].xloc-0;  activenext[1].yloc = active[1].yloc+1;
                    activenext[2].xloc = active[2].xloc+1;  activenext[2].yloc = active[2].yloc-0;
                    activenext[3].xloc = active[3].xloc+2;  activenext[3].yloc = active[3].yloc-1;
                    break;
                case 3:
                    activenext[0].xloc = active[0].xloc-2;  activenext[0].yloc = active[0].yloc-1;
                    activenext[1].xloc = active[1].xloc-1;  activenext[1].yloc = active[1].yloc-0;
                    activenext[2].xloc = active[2].xloc+0;  activenext[2].yloc = active[2].yloc+1;
                    activenext[3].xloc = active[3].xloc+1;  activenext[3].yloc = active[3].yloc+2;
                    break;
            }
            break;
        case 2: //O pieces do not rotate
            break;
        case 3: //T
            switch(active[0].rotstate)
            {
                case 0:
                    activenext[0].xloc = active[0].xloc+1;  activenext[0].yloc = active[0].yloc+1;
                    activenext[1].xloc = active[1].xloc+1;  activenext[1].yloc = active[1].yloc-1;
                    activenext[3].xloc = active[3].xloc-1;  activenext[3].yloc = active[3].yloc+1;
                    break;
                case 1:
                    activenext[0].xloc = active[0].xloc-1;  activenext[0].yloc = active[0].yloc+1;
                    activenext[1].xloc = active[1].xloc+1;  activenext[1].yloc = active[1].yloc+1;
                    activenext[3].xloc = active[3].xloc-1;  activenext[3].yloc = active[3].yloc-1;
                    break;   
                case 2:
                    activenext[0].xloc = active[0].xloc-1;  activenext[0].yloc = active[0].yloc-1;
                    activenext[1].xloc = active[1].xloc-1;  activenext[1].yloc = active[1].yloc+1;
                    activenext[3].xloc = active[3].xloc+1;  activenext[3].yloc = active[3].yloc-1;
                    break;
                case 3:
                    activenext[0].xloc = active[0].xloc+1;  activenext[0].yloc = active[0].yloc-1;
                    activenext[1].xloc = active[1].xloc-1;  activenext[1].yloc = active[1].yloc-1;
                    activenext[3].xloc = active[3].xloc+1;  activenext[3].yloc = active[3].yloc+1;
                    break;
            }
            break;
        case 4: //S
            switch(active[0].rotstate)
            {
                case 0:
                    activenext[0].xloc = active[0].xloc+1;  activenext[0].yloc = active[0].yloc+1;
                    activenext[1].xloc = active[1].xloc+0;  activenext[1].yloc = active[1].yloc+2;
                    activenext[2].xloc = active[2].xloc+1;  activenext[2].yloc = active[2].yloc-1;
                    break;
                case 1:
                    activenext[0].xloc = active[0].xloc-1;  activenext[0].yloc = active[0].yloc+1;
                    activenext[1].xloc = active[1].xloc-2;  activenext[1].yloc = active[1].yloc+0;
                    activenext[2].xloc = active[2].xloc+1;  activenext[2].yloc = active[2].yloc+1; 
                    break;  
                case 2:
                    activenext[0].xloc = active[0].xloc-1;  activenext[0].yloc = active[0].yloc-1;
                    activenext[1].xloc = active[1].xloc+0;  activenext[1].yloc = active[1].yloc-2;
                    activenext[2].xloc = active[2].xloc-1;  activenext[2].yloc = active[2].yloc+1;
                    break;
                case 3:
                    activenext[0].xloc = active[0].xloc+1;  activenext[0].yloc = active[0].yloc-1;
                    activenext[1].xloc = active[1].xloc+2;  activenext[1].yloc = active[1].yloc+0;
                    activenext[2].xloc = active[2].xloc-1;  activenext[2].yloc = active[2].yloc-1;
                    break;
            }
            break;
        case 5: //Z
            switch(active[0].rotstate)
            {
                case 0:
                    activenext[0].xloc = active[0].xloc+2;  activenext[0].yloc = active[0].yloc+0;
                    activenext[1].xloc = active[1].xloc+1;  activenext[1].yloc = active[1].yloc+1;
                    activenext[3].xloc = active[3].xloc-1;  activenext[3].yloc = active[3].yloc+1;
                    break;
                case 1:
                    activenext[0].xloc = active[0].xloc+0;  activenext[0].yloc = active[0].yloc+2;
                    activenext[1].xloc = active[1].xloc-1;  activenext[1].yloc = active[1].yloc+1;
                    activenext[3].xloc = active[3].xloc-1;  activenext[3].yloc = active[3].yloc-1;
                    break;   
                case 2:
                    activenext[0].xloc = active[0].xloc-2;  activenext[0].yloc = active[0].yloc+0;
                    activenext[1].xloc = active[1].xloc-1;  activenext[1].yloc = active[1].yloc-1;
                    activenext[3].xloc = active[3].xloc+1;  activenext[3].yloc = active[3].yloc-1;
                    break;
                case 3:
                    activenext[0].xloc = active[0].xloc+0;  activenext[0].yloc = active[0].yloc-2;
                    activenext[1].xloc = active[1].xloc+1;  activenext[1].yloc = active[1].yloc-1;
                    activenext[3].xloc = active[3].xloc+1;  activenext[3].yloc = active[3].yloc+1;
                    break;
            }
            break;
        case 6: //L
            switch(active[0].rotstate)
            {
                case 0:
                    activenext[0].xloc = active[0].xloc+0;  activenext[0].yloc = active[0].yloc+2;
                    activenext[1].xloc = active[1].xloc+1;  activenext[1].yloc = active[1].yloc-1;
                    activenext[3].xloc = active[3].xloc-1;  activenext[3].yloc = active[3].yloc+1;
                    break;
                case 1:
                    activenext[0].xloc = active[0].xloc-2;  activenext[0].yloc = active[0].yloc+0;
                    activenext[1].xloc = active[1].xloc+1;  activenext[1].yloc = active[1].yloc+1;
                    activenext[3].xloc = active[3].xloc-1;  activenext[3].yloc = active[3].yloc-1;
                    break;   
                case 2:
                    activenext[0].xloc = active[0].xloc+0;  activenext[0].yloc = active[0].yloc-2;
                    activenext[1].xloc = active[1].xloc-1;  activenext[1].yloc = active[1].yloc+1;
                    activenext[3].xloc = active[3].xloc+1;  activenext[3].yloc = active[3].yloc-1;
                    break;
                case 3:
                    activenext[0].xloc = active[0].xloc+2;  activenext[0].yloc = active[0].yloc+0;
                    activenext[1].xloc = active[1].xloc-1;  activenext[1].yloc = active[1].yloc-1;
                    activenext[3].xloc = active[3].xloc+1;  activenext[3].yloc = active[3].yloc+1;
                    break;
            }
            break;
        case 7: //J
            switch(active[0].rotstate)
            {
                case 0:
                    activenext[0].xloc = active[0].xloc+2;  activenext[0].yloc = active[0].yloc+0;
                    activenext[1].xloc = active[1].xloc+1;  activenext[1].yloc = active[1].yloc-1;
                    activenext[3].xloc = active[3].xloc-1;  activenext[3].yloc = active[3].yloc+1;
                    break;
                case 1:
                    activenext[0].xloc = active[0].xloc+0;  activenext[0].yloc = active[0].yloc+2;
                    activenext[1].xloc = active[1].xloc+1;  activenext[1].yloc = active[1].yloc+1;
                    activenext[3].xloc = active[3].xloc-1;  activenext[3].yloc = active[3].yloc-1;
                    break;   
                case 2:
                    activenext[0].xloc = active[0].xloc-2;  activenext[0].yloc = active[0].yloc+0;
                    activenext[1].xloc = active[1].xloc-1;  activenext[1].yloc = active[1].yloc+1;
                    activenext[3].xloc = active[3].xloc+1;  activenext[3].yloc = active[3].yloc-1;
                    break;
                case 3:
                    activenext[0].xloc = active[0].xloc+0;  activenext[0].yloc = active[0].yloc-2;
                    activenext[1].xloc = active[1].xloc-1;  activenext[1].yloc = active[1].yloc-1;
                    activenext[3].xloc = active[3].xloc+1;  activenext[3].yloc = active[3].yloc+1;
                    break;
            }
            break;
    }
    for(i = 0; i < 4; i++)  //check if the rotated state would cause any squares to move into locked squares on board
    {
        if(board[activenext[i].xloc][activenext[i].yloc].rotstate == 4)
            return; //if so, the rotation fails
    }
    for(i = 0; i < 4; i++)  //otherwise, the rotation succeeds, copy activenext[] to active[]
    {
        active[i] = activenext[i];
        if(active[i].rotstate == 3) //update rotstate   0 -> 1
            active[i].rotstate = 0;                   //1 -> 2
        else                                          //2 -> 3  
            active[i].rotstate++;                     //3 -> 0  
    }
    activeToBoard(active, board);   //and push the active piece to the board in its new location
}

//fall will slam the active piece as far down on the board as it will go instanty
void fall(Square board[][boardY+2], Square active[], bool *gotonext)
{
    while(!*gotonext)   //calls movedown until movedown sets gotonext to true meaning the piece has gone as far as it can
        movedown(board, active, gotonext);
}

//checkrows will check every row onthe board to check if it is full and should be cleared. It also checks if any pieces
//have exited the playing field from the top indicating that the game is over
int checkrows(Square board[][boardY+2], bool *gameover)
{
    int score = 0;
    int numrowscleared = 0;
    int i, j;
    for(i = 1; i < boardX+1; i++)   //check if any squares above the board have pieces
    {
        if(board[i][2].rotstate == 4)
        {
            *gameover = true;   //if so, set gameover to true and return
            return;
        }
    }

    bool fullrow;
    for(j = 3; j < boardY+1; j++)   //check the rows in the playing field
    {
        fullrow = true;
        for(i = 1; i < boardX+1; i++)       //fullrow will only make it through as true if every Square in the row is
        {                                   //filled
            if(board[i][j].rotstate != 4)
                fullrow = false;
        }
        if(fullrow) //if so,
        {
            clearrow(board, j); //clear that row
            numrowscleared++;
        }
    }
    score = numrowscleared*numrowscleared;  //return how many points should be added to the score
    return score;
}

//clearrow will clear a specified row by shifting all the squares above that row down by one
void clearrow(Square board[][boardY+2], int rownum)
{
    int i, j;
    for(i = 1; i < boardX+1; i++)
    {
        for(j = rownum; j > 3; j--)
        {
            board[i][j] = board[i][j-1];
        }
    }
}
