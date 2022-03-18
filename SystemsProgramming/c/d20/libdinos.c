#include "libdinos.h"
#include <stdio.h>
#include <stdlib.h>

int readline(FILE *fp, char *buf, int len)
{
    char c = fgetc(fp);
    int i = 0;

    while((c != '\n') && (i < len))
    {
        buf[i] = c;

        c = fgetc(fp);
        i++;

        if (c == EOF)
        {
            i = -1;
            break;
        }
    }

    return i;
}

int split(char *buf, char **splits, char delim, int max, int len)
{
    int numsplits = 0;
    long unsigned int i, j;
    int start = 0;
    int end = 0;
    int currlength = 0;

    for(i = 0; i < len; i++){
        if(buf[i] == delim){
            end = i-1;
            currlength = end - start + 2;
            splits[numsplits] = malloc(currlength*sizeof(char));
            for(j = 0; j < currlength-1; j++){
                splits[numsplits][j] = buf[i-currlength+j+1];
            }
            splits[numsplits][currlength-1] = '\0';
            numsplits++;
            start = i+1;
            end = i+1;
        }
    }
    return numsplits;
}
