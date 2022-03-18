#include <stdio.h>

typedef struct
{
    double lat;
    double lng;
    
    double maxma;
    double minma;
    
    int namelen;
    char *name;
} dino;

int split(char *buf, char **splits, char delim, int max, int len);
int readline(FILE *fp, char *buf, int len);
int readdinos(char *fn, dino **dinos);
