//pathfunc.h
//Hayden Owens
//CSE 20311
//pathfunc.h contains function prototypes and the defintion for the struct Point
//
typedef struct {    //define a struct Point that holds two floats for the x and y coordinates of a Point
    float x;
    float y;
} Point;

//function prototypes
int readUser(Point points[]);
int readFile(char filename[], Point points[]);
float findDistance(Point points[], int numPoints);
void display(Point points[], int numPoints, float distance);
