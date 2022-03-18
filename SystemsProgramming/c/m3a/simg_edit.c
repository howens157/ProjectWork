#include "libsimg.h"
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios default_settings;

void printscreen(simg_img img, simg_cursor curs)
{
    system("clear");
    simg_print(&img, &curs);
    return;
}

void disableraw()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_settings);
}

void enableraw()
{
    tcgetattr(STDIN_FILENO, &default_settings);
    atexit(disableraw);
    struct termios raw = default_settings;
    raw.c_iflag &= ~(ICRNL | IXON);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Incorrect number of arguments\n");
        return 1;
    }
    
    simg_img image;
    simg_cursor cursor = {0, 0, 'X', 1};
    char* filename = argv[1];
    FILE *ifp = fopen(filename, "r");
    if(ifp == NULL)
    {
        fclose(ifp);
        simg_create(&image, 20, 20, 'X');
    }
    else
    {
        fclose(ifp);
        simg_read(&image, filename);
    }

    enableraw();

    char c;
    printscreen(image, cursor);
    c = '\0';
    while(c != 'q')
    {
        read(STDIN_FILENO, &c, 1);
        if(c == 27)
        {
            read(STDIN_FILENO, &c, 1);
            if(c == '[')
            {
                read(STDIN_FILENO, &c, 1);
                if(c == 'A')
                {
                    if(cursor.cy != image.height-1)
                        cursor.cy++;
                }
                else if(c == 'B')
                {
                    if(cursor.cy != 0)
                        cursor.cy--;
                }
                else if(c == 'C')
                { 
                    if(cursor.cx != image.width-1)
                        cursor.cx++;
                }
                else if(c == 'D')
                {
                    if(cursor.cx != 0)
                        cursor.cx--;
                }
            }
            
        }
        else if(c == 'c')
        {
            read(STDIN_FILENO, &c, 1);
            cursor.c = c;
            c = '\0';
        }
        else if(c == 'r')
        {
            read(STDIN_FILENO, &c, 1);
            if(c >= '0' && c <= '6')
                cursor.r = (int)(c - '0');
        }
        else if(c == 'p')
            simg_setpixel(&image, cursor.cx, cursor.cy, cursor.r, cursor.c);
        else if(c == 's')
            simg_write(&image, filename);
        else if(c == 'l')
            simg_read(&image, filename);
        printscreen(image, cursor);
    }

    return 0;
}
