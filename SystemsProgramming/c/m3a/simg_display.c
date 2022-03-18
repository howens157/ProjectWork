#include "libsimg.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
    char* filename = argv[1];
    
    simg_img image;
    simg_read(&image, filename);
    simg_print(&image, NULL);

    return 0;
}
