#include "libsimg.h"
#include <stdio.h>
#include <stdlib.h>

const char *simg_colors[7];

int simg_create(simg_img *img, int height, int width, char bg)
{
    int i, j;
    //printf("start create\n");
    img->height = height;
    img->width = width;
    img->data = malloc(height * sizeof(simg_img**));
    for(i = 0; i < height; i++)
    {
        img->data[i] = malloc(width * sizeof(simg_img*));
        for(j = 0; j < width; j++)
        {
            img->data[i][j] = malloc(sizeof(simg_pixel));
        }
    }
    int r = 0;;
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            img->data[i][j]->c = bg;
            img->data[i][j]->r = r;
        }
    }
    //printf("end create\n");
    return 0;
}

int simg_setpixel(simg_img *img, int x, int y, int color, char c)
{
    //printf("start set %d %d %c ", x, y, c);
    img->data[y][x]->c = c;
    img->data[y][x]->r = color;
    //printf("end set\n");
    return 0;
}

int simg_write(simg_img *img, char *fn)
{
    //printf("start write\n");
    int i, j;
    FILE *ofp = fopen(fn, "wb");
    fwrite(&(img->height), sizeof(int), 1, ofp);
    fwrite(&(img->width), sizeof(int), 1, ofp);
    for(i = 0; i < img->height; i++)
    {
        for(j = 0; j < img->width; j++)
        {
            fwrite(&(img->data[i][j]->c), sizeof(char), 1, ofp);
            fwrite(&(img->data[i][j]->r), sizeof(int), 1, ofp);
        }
    }
    fclose(ofp);
    //printf("end write\n");
    return 0;
}
int simg_read(simg_img *img, char *fn)
{
    //printf("start read\n");
    int i, j;
    FILE *ifp = fopen(fn, "rb");
    fread(&(img->height), sizeof(int), 1, ifp);
    fread(&(img->width), sizeof(int), 1, ifp);
    img->data = malloc(img->height * sizeof(simg_img**));
    for(i = 0; i < img->height; i++)
    {
        img->data[i] = malloc(img->width * sizeof(simg_img*));
        for(j = 0; j < img->width; j++)
        {
            img->data[i][j] = malloc(sizeof(simg_pixel));
        }
    }
    char c;
    int r;
    for(i = 0; i < img->height; i++)
    {
        for(j = 0; j < img->width; j++)
        {
            fread(&c, sizeof(char), 1, ifp);
            fread(&r, sizeof(int), 1, ifp);
            img->data[i][j]->c = c;
            img->data[i][j]->r = r;
        }
    }
    fclose(ifp);
    return 0;
}

int simg_print(simg_img *img, simg_cursor *cur)
{
    simg_colors[SIMG_RESET] = "[0m";
    simg_colors[SIMG_RED] = "[0;31m";
    simg_colors[SIMG_GREEN] = "[0;32m";
    simg_colors[SIMG_YELLOW] = "[0;33m";
    simg_colors[SIMG_BLUE] = "[0;34m";
    simg_colors[SIMG_MAGENTA] = "[0;35m";
    simg_colors[SIMG_CYAN] = "[0;36m";
    
    int i, j, r;
    for(i = img->height-1; i >= 0; i--)
    {
        for(j = 0; j < img->width; j++)
        {
            if(cur != NULL && cur->cx == j && cur->cy == i)
            {
                printf("\033%s", simg_colors[cur->r]);
                printf("%c", cur->c);
                printf("\033%s", simg_colors[SIMG_RESET]);
            }
            else
            {
                printf("\033%s", simg_colors[img->data[i][j]->r]);
                printf("%c", img->data[i][j]->c);
                printf("\033%s", simg_colors[SIMG_RESET]);
            }
            if(j == img->width-1)
                printf("\n");
        }
    }
    return 0;
}
