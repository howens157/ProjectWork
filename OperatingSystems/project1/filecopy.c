/* Hayden Owens
 * 1/21/2022
 * Operating Systems - Project 1
 *
 * treecopy.c
 *
 * This program copies a file from a source path to a destination path and 
 * outputs the number of bytes that were copied. If the source already exists
 * the copy will not take place.
 *
 * Usage: filecopy <source> <destination>
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

//copyFile takes a sourcepath string and a destpath string and copies the file
//at sourcepath to destpath provided that there is not already a file at destpath.
//copyFile will only copy regular files.
//Returns the number of bytes copied.
int copyfile(const char *sourcepath, const char *destpath)
{
    struct stat sourcestat;
    struct stat deststat;
    int err;
    int totalBytesCopied = 0;
    int numRead, numWrite;

    //stat both files and check return values to make sure that the source file
    //is a regular file and the destination file does not already exist
    if(stat(destpath, &deststat) != -1)
    {
        fprintf(stderr, "filecopy: destination file already exists\n");
        exit(EXIT_FAILURE);
    }
    
    stat(sourcepath, &sourcestat);
    if(!(S_ISREG(sourcestat.st_mode)))
    {
        fprintf(stderr, "filecopy: source file is not a regular file\n");
        exit(EXIT_FAILURE);
    }

    //open the source file
    int fdr = open(sourcepath, O_RDONLY, 0);
    if(fdr < 0)
    {
        fprintf(stderr, "filecopy: unable to open %s: %s\n", sourcepath, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    //create the destination file
    int fdw = creat(destpath, O_WRONLY);
    if(fdw < 0)
    { 
        fprintf(stderr, "filecopy: unable to open %s: %s\n", destpath, strerror(errno));
        exit(EXIT_FAILURE);
    }
    //copy the permissions from the source file to the destination file
    err = chmod(destpath, sourcestat.st_mode);
    if(err < 0)
    {
        fprintf(stderr, "filecopy: unable to copy permissions: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }


    //buffer to read to and write from
    char buffer[4096];

    numRead = 0;
    while(1)
    {
        //try to read a chunk of data from source
        numRead = read(fdr, &buffer, 4096);
        //if no data left, end loop
        if(numRead == 0)
            break;
        //if error, print error and exit
        else if(numRead < 0)
        {
            //if the OS was interrupted, do nothing, the write loop will be passed over
            //and the read will try again. If any other error, exit
            if(errno == EINTR){}
            else{
                fprintf(stderr, "filecopy: unable to read from %s: %s\n", sourcepath, strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        
        numWrite = 0;
        //keep writing until you have written all that you read
        while(numWrite < numRead)
        {
            //write remaining data from buffer to destination
            numWrite = numWrite + write(fdw, &buffer[numWrite], numRead-numWrite);
            //if error, print error and exit
            if(numRead < 0)
            {
                fprintf(stderr, "filecopy: unable to write to %s: %s\n", destpath, strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        totalBytesCopied += numWrite;
    }


    //close both files
    err = close(fdr);
    if(err < 0)
    {
        fprintf(stderr, "filecopy: unable to close %s: %s\n", sourcepath, strerror(errno));
        exit(EXIT_FAILURE);
    }
    err = close(fdw);
    if(err < 0)
    { 
        fprintf(stderr, "filecopy: unable to close %s: %s\n", destpath, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return totalBytesCopied;
}

int main(const int argc, const char* argv[])
{
    //check for correct number of args
    if(argc < 3)
    {
        fprintf(stderr, "filecopy: Too few arguments\n");
        fprintf(stderr, "usage: filecopy <sourcefile> <targetfile>\n");
        exit(EXIT_FAILURE);
    }
    else if(argc > 3)
    {
        fprintf(stderr, "filecopy: Too many arguments\n");
        fprintf(stderr, "usage: filecopy <sourcefile> <targetfile>\n");
        exit(EXIT_FAILURE);
    }
   
    int bytesCopied = copyfile(argv[1], argv[2]);
    printf("filecopy: copied %d bytes from %s to %s\n", bytesCopied, argv[1], argv[2]);
 
    exit(EXIT_SUCCESS);
}
