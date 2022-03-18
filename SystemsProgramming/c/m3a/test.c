#include "libsimg.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
    char* filename = argv[1];
    
    simg_img image;
    simg_read(&image, filename);
    
    char testchar = image.data[0][0]->c;
    printf("%c\n", testchar);

    return 0;
}
