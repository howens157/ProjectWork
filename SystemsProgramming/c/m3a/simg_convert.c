#include "libsimg.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Incorrect number of arguments\n");
        return 1;
    }
    int i, j;
    char* ifilename = argv[1];
    FILE *ifp = fopen(ifilename, "r");
    char readchars[100][100];
    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < 100; j++)
        {
            readchars[i][j] = ' ';
        }
    }

    int row = 0;
    int col = 0;
    int maxrow = row;
    int maxcol = col;
    char c = fgetc(ifp);
    while(c != EOF)
    {
        if(c == '\n')
        {
            row++;
            if(col > maxcol)
                maxcol = col;
            col = 0;
        }
        else
        {
            readchars[row][col] = c;
            col++;
        }
        c = fgetc(ifp);
    }
    maxrow = row;
    fclose(ifp);

    simg_img image;
    simg_create(&image, maxrow, maxcol, '#');

    for(i = 0; i < maxrow; i++)
    {
        for(j = 0; j < maxcol; j++)
        {
            simg_setpixel(&image, j, maxrow-1-i, 0, readchars[i][j]);
        }
    }

    char* ofilename = argv[2];
    simg_write(&image, ofilename);

    return 0;
}
