/* Hayden Owens
 * 1/21/2022
 * Operating Systems - Project 1
 *
 * treecopy.c
 *
 * This program copies a file or a directory and all its contents from a 
 * source path to a destination path and outputs the number of directories, 
 * files, and bytes that were copied. If the source already exists the copy 
 * will not take place.
 *
 * Usage: treecopy <source> <destination>
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

//struct to store the total number of directories, files, and bytes copied
struct copyStats {
    int numDir;
    int numFile;
    int numBytes;
};

//copyFile takes a sourcepath string and a destpath string and copies the file
//at sourcepath to destpath provided that there is not already a file at destpath.
//copyFile will only copy regular files.
//Returns the number of bytes copied
int copyFile(const char *sourcepath, const char *destpath)
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
        fprintf(stderr, "treecopy: destination file already exists\n");
        exit(EXIT_FAILURE);
    }
    
    stat(sourcepath, &sourcestat);
    if(!(S_ISREG(sourcestat.st_mode)))
    {
        fprintf(stderr, "treecopy: source file is not a regular file\n");
        exit(EXIT_FAILURE);
    }

    //open the source file
    int fdr = open(sourcepath, O_RDONLY, 0);
    if(fdr < 0)
    {
        fprintf(stderr, "treecopy: unable to open %s: %s\n", sourcepath, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    //create the destination file
    int fdw = creat(destpath, O_WRONLY);
    if(fdw < 0)
    { 
        fprintf(stderr, "treecopy: unable to open %s: %s\n", destpath, strerror(errno));
        exit(EXIT_FAILURE);
    }
    //copy the permissions from the source file to the destination file
    err = chmod(destpath, sourcestat.st_mode);
    if(err < 0)
    {
        fprintf(stderr, "treecopy: unable to copy permissions: %s\n", strerror(errno));
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
                fprintf(stderr, "treecopy: unable to read from %s: %s\n", sourcepath, strerror(errno));
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
                fprintf(stderr, "treecopy: unable to write to %s: %s\n", destpath, strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        totalBytesCopied += numWrite;
    }


    //close both files
    err = close(fdr);
    if(err < 0)
    {
        fprintf(stderr, "treecopy: unable to close %s: %s\n", sourcepath, strerror(errno));
        exit(EXIT_FAILURE);
    }
    err = close(fdw);
    if(err < 0)
    { 
        fprintf(stderr, "treecopy: unable to close %s: %s\n", destpath, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return totalBytesCopied;
}

//copyDir copies the contents of sourcepath to destpath provided that destpath does
//not already exist. It also takes a pointer to a struct copyStat in order to keep
//track of the amount of directories, files, and bytes that were copied.
//If sourcepath is just a regular file, copyDir just calls copyFile. If it is a
//directory it reads the contents of the directory and recursively calls copyDir
//on every file in the directory
//The return values are stored in the struct copyStats.
void copyDir(const char *sourcepath, const char *destpath, struct copyStats *st)
{
    struct stat sourcestat;
    struct stat deststat;
    int err;

    //check if dest already exists
    if(stat(destpath, &deststat) != -1)
    {
        fprintf(stderr, "treecopy: destination path already exists\n");
        exit(EXIT_FAILURE);
    }

    //stat source
    stat(sourcepath, &sourcestat);
    //if the source is a file, call filecopy
    if((S_ISREG(sourcestat.st_mode)))
    {
        st->numBytes += copyFile(sourcepath, destpath);
        st->numFile++;
        printf("%s -> %s\n", sourcepath, destpath);
        return;
    }
    //if the source is not a directory and not a reg file, print error and exit
    else if(!(S_ISDIR(sourcestat.st_mode)))
    {
        fprintf(stderr, "treecopy: source path %s is not reg file or directory\n", sourcepath);
        exit(EXIT_FAILURE);
    }

    //open source directory
    DIR *dirStrm = opendir(sourcepath);
    if(dirStrm == NULL)
    {
        fprintf(stderr, "treecopy: source directory %s could not be opened: %s\n", sourcepath, strerror(errno));
        exit(EXIT_FAILURE);
    }
    //make destination directory
    err = mkdir(destpath, sourcestat.st_mode);
    if(err < 0)
    {
        fprintf(stderr, "treecopy: destination directory %s could not be created: %s\n", destpath, strerror(errno));
        exit(EXIT_FAILURE);
    }
    //output that a new directory has been created
    printf("%s -> %s\n", sourcepath, destpath);
    //increment numDir
    st->numDir++;
    
    
    struct dirent *nextEntry; 
    //set errno to 0 before readdir() to distinguish between EOF and an actual error
    //when readdir returns NULL
    errno = 0;
    //read directory entries until readdir returns NULL indicating either an error
    //or the end of the directory has been reached
    while((nextEntry = readdir(dirStrm)))
    {
        //exclude the '.' and '..' directories
        if(!(strcmp(nextEntry->d_name, ".")==0 || strcmp(nextEntry->d_name, "..")==0))
        {
            //create new source and destination paths by appending the current
            //file/directory to the previous paths
            char sourceNameBuf[1024];
            char destNameBuf[1024];
            sprintf(sourceNameBuf, "%s/%s", sourcepath, nextEntry->d_name);
            sprintf(destNameBuf, "%s/%s", destpath, nextEntry->d_name);
            //recursively call copyDir with the new destination and source to copy
            //all contents of the current directory
            copyDir(sourceNameBuf, destNameBuf, st);
            errno = 0;
        }
    }
    //The loop could have exited due to error so handle the error
    if(nextEntry == NULL && errno != 0)
    {
        fprintf(stderr, "treecopy: error reading destination directory %s: %s\n", destpath, strerror(errno));
        exit(EXIT_FAILURE);
    }


    //close source directory
    err = closedir(dirStrm);
    if(err < 0)
    {
        fprintf(stderr, "treecopy: unable to close %s: %s\n", sourcepath, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return;
}

int main(const int argc, const char* argv[])
{
    //check for correct number of args
    if(argc < 3)
    {
        fprintf(stderr, "treecopy: Too few arguments\n");
        fprintf(stderr, "usage: treecopy <sourcefile> <targetfile>\n");
        exit(EXIT_FAILURE);
    }
    else if(argc > 3)
    {
        fprintf(stderr, "treecopy: Too many arguments\n");
        fprintf(stderr, "usage: filecopy <sourcefile> <targetfile>\n");
        exit(EXIT_FAILURE);
    }
   
    //create a copyStats struct to store the data about what is copied and initialize all fields to 0
    struct copyStats st;
    st.numDir = 0;
    st.numFile = 0;
    st.numBytes = 0;
    copyDir(argv[1], argv[2], &st);
    printf("treecopy: copied %d directories, %d files, and %d bytes from %s to %s\n", st.numDir, st.numFile, st.numBytes, argv[1], argv[2]);
 
    exit(EXIT_SUCCESS);
}
