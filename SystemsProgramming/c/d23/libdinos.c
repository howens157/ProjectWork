#include "libdinos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int readdinos(char *fn, dino **dinos)
{
    FILE *fp = fopen("dinosaur.dat", "r");
    char delim = '\t';
    int len = 2048;
    char *buf = malloc(len*sizeof(char));

    readline(fp, buf, len);

    int max = 50;
    char *splits[max];
    int num_heads = split(buf, splits, delim, max, len);

    int currsplits;
    int numdinos = 0;
    int i;
    char *p;
    while(1)
    {
        char *buf = malloc(len*sizeof(char));
        char *splits[max];
        if(readline(fp, buf, len) == -1)
            break;
        currsplits = split(buf, splits, delim, max, len);
        if(currsplits == num_heads)
        {
            dinos[numdinos] = malloc(sizeof(dino));
            dinos[numdinos]->lat = strtod(splits[19], &p);
            dinos[numdinos]->lng = strtod(splits[18], &p);
            dinos[numdinos]->maxma = strtod(splits[15], &p);
            dinos[numdinos]->minma = strtod(splits[16], &p);
            dinos[numdinos]->namelen = strlen(splits[5]);
            dinos[numdinos]->name = malloc(dinos[numdinos]->namelen * sizeof(char));
            for(i = 0; i < dinos[numdinos]->namelen; i++)
            {
                dinos[numdinos]->name[i] = splits[5][i];
            }
            numdinos++;
        }
    }
    fclose(fp);
    return numdinos;
}

double nearest_dino(dino *d0, dino *d1, dino **dinos, int numdinos, double (*dist_fcn)(dino *dA, dino *dB))
{
    int iter;
    
    double curr_min_dist = (double)INT_MAX;
    double min_dist = curr_min_dist;
    for(iter = 0; iter < numdinos; iter++)
    {
        curr_min_dist = (*dist_fcn)(d0, dinos[iter]);
        //printf("%lf %lf\n",min_dist, curr_min_dist);
        if(curr_min_dist < min_dist && d0 != dinos[iter] && curr_min_dist != 0.0)
        {
            //printf("Old Dist: %lf\tNew Dist: %lf\n", min_dist, curr_min_dist);
            min_dist = curr_min_dist;
            memcpy(d1, dinos[iter], sizeof(dino));
        }
        if(min_dist == 0.0)
            break;
        //printf("%lf\n",min_dist);
    }
    return min_dist;
}
