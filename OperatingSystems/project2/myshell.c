/* Hayden Owens
 * 2/2/2022
 * Operating Systems - Project 2
 *
 * myshell.c
 *
 * This program is a basic shell that runs within bash and supports a variety of
 * commands including process management.
 *
 * Commands:
 *              list
 *                  -lists info about contents of current working directory
 *
 *              chdir <path>
 *                  -changes current working directory to path
 *
 *              pwd
 *                  -prints the path of the current working directory
 *
 *              copy <sourcepath> <destinationpath>
 *                  -copies the file or directory at sourcepath to destinationpath
 *
 *              start <command> <arg1> <arg2> ...
 *                  -creates a new child process that executes command with the given
 *                   list of args
 *
 *              wait
 *                  -waits on any child process to complete and outputs the pid of
 *                   the finished process to the screen
 *
 *              waitfor <wpid>
 *                  -waits on a specific child process identified by wpid to complete
 *
 *              run <command> <arg1> <arg2> ...
 *                  -creates a new child process that executes command with the given
 *                   list of args and then waits on that process to finish
 *
 *              kill <kpid>
 *                  -sends a SIGKILL signal to the process identified by kpid
 *
 * Usage: 
 *          ./myshell
 *
 * Also supports the writing of scripts:
 *          ./myshell < myscript1
 */
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/wait.h>

//struct to store the total number of directories, files, and bytes copied
struct copyStats {
    int numDir;
    int numFile;
    int numBytes;
};

//list() will print info about all the contents of the current working directory to the
//screen in a table format
int list() {
    //open current directory
    DIR *dirStrm = opendir(".");
    if(dirStrm == NULL)
    {
        fprintf(stderr, "list: current directory could not be opened: %s\n", strerror(errno));
        return -1;
    }    
    
    printf("Type\tName\t\t\tSize\n");

    struct dirent *nextEntry; 
    //set errno to 0 before readdir() to distinguish between EOF and an actual error
    //when readdir returns NULL
    errno = 0;
    //read directory entries until readdir returns NULL indicating either an error
    //or the end of the directory has been reached
    while((nextEntry = readdir(dirStrm)))
    {
        //stat every entry in the directory and print out the type, name, and size
        struct stat dirStat;
        if(stat(nextEntry->d_name, &dirStat) != 0)
        {
            fprintf(stderr, "list: error listing file %s: %s\n", nextEntry->d_name, strerror(errno));
            return -1;
        }
        if(S_ISREG(dirStat.st_mode))
        {
            printf("F\t");
        }
        else if(S_ISDIR(dirStat.st_mode))
        {
            printf("D\t");
        }
        printf("%-20s\t%d\n", nextEntry->d_name, (int)dirStat.st_size);
        
        errno = 0;
    }
    //The loop could have exited due to error so handle the error
    if(nextEntry == NULL && errno != 0)
    {
        fprintf(stderr, "list: error reading directory: %s\n", strerror(errno));
        return -1;
    }


    //close current directory
    if(closedir(dirStrm) != 0)
    {
        fprintf(stderr, "list: unable to close current directory: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

//pwd will print the path of the current working directory to the screen
int pwd()
{
    //get the name of the current path
    char* dirName = get_current_dir_name();
    //output error if get_current_dir_name failed
    if(dirName == NULL)
    {
        fprintf(stderr, "pwd: could not get path of current working directory: %s\n", strerror(errno));
        return -1;
    }
    //print current path and free the memory allocated by get_current_dir_name
    printf("%s\n", dirName);
    free(dirName);
    return 0;
}

//myChdir will change the current working directory of myshell to the path specified
//by newPath
int myChdir(char *newPath)
{
    //attempt to change the directory and print error if it failed
    if(chdir(newPath) < 0)
    {
        fprintf(stderr, "chdir: could not change current working directory to %s: %s\n", newPath, strerror(errno));
        return -1;
    }
    return 0;
}

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
        fprintf(stderr, "copy: destination file already exists\n");
        return -1;
    }
    
    if(stat(sourcepath, &sourcestat) == -1)
    {
        fprintf(stderr, "copy: source file does not exist\n");
        return -1;
    }
    if(!(S_ISREG(sourcestat.st_mode)))
    {
        fprintf(stderr, "copy: source file is not a regular file\n");
        return -1;
    }

    //open the source file
    int fdr = open(sourcepath, O_RDONLY, 0);
    if(fdr < 0)
    {
        fprintf(stderr, "copy: unable to open %s: %s\n", sourcepath, strerror(errno));
        return -1;
    }
    
    //create the destination file
    int fdw = creat(destpath, O_WRONLY);
    if(fdw < 0)
    { 
        fprintf(stderr, "copy: unable to open %s: %s\n", destpath, strerror(errno));
        return -1;
    }
    //copy the permissions from the source file to the destination file
    err = chmod(destpath, sourcestat.st_mode);
    if(err < 0)
    {
        fprintf(stderr, "copy: unable to copy permissions: %s\n", strerror(errno));
        return -1;
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
                fprintf(stderr, "copy: unable to read from %s: %s\n", sourcepath, strerror(errno));
                return -1;
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
                fprintf(stderr, "copy: unable to write to %s: %s\n", destpath, strerror(errno));
                return -1;
            }
        }
        totalBytesCopied += numWrite;
    }


    //close both files
    err = close(fdr);
    if(err < 0)
    {
        fprintf(stderr, "copy: unable to close %s: %s\n", sourcepath, strerror(errno));
        return -1;
    }
    err = close(fdw);
    if(err < 0)
    { 
        fprintf(stderr, "copy: unable to close %s: %s\n", destpath, strerror(errno));
        return -1;
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
int copyDir(const char *sourcepath, const char *destpath, struct copyStats *st)
{
    struct stat sourcestat;
    struct stat deststat;
    int err;

    //check if dest already exists
    if(stat(destpath, &deststat) != -1)
    {
        fprintf(stderr, "copy: destination path already exists\n");
        return -1;
    }

    //check if source does not exist
    if(stat(sourcepath, &sourcestat) != 0)
    {
        fprintf(stderr, "copy: source path does not exist\n");
        return -1;
    }

    //if the source is a file, call filecopy
    if((S_ISREG(sourcestat.st_mode)))
    {
        st->numBytes += copyFile(sourcepath, destpath);
        st->numFile++;
        printf("%s -> %s\n", sourcepath, destpath);
        return 0;
    }
    //if the source is not a directory and not a reg file, print error and exit
    else if(!(S_ISDIR(sourcestat.st_mode)))
    {
        fprintf(stderr, "copy: source path %s is not reg file or directory\n", sourcepath);
        return -1;
    }

    //open source directory
    DIR *dirStrm = opendir(sourcepath);
    if(dirStrm == NULL)
    {
        fprintf(stderr, "copy: source directory %s could not be opened: %s\n", sourcepath, strerror(errno));
        return -1;
    }
    //make destination directory
    err = mkdir(destpath, sourcestat.st_mode);
    if(err < 0)
    {
        fprintf(stderr, "copy: destination directory %s could not be created: %s\n", destpath, strerror(errno));
        return -1;
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
        fprintf(stderr, "copy: error reading destination directory %s: %s\n", destpath, strerror(errno));
        return -1;
    }


    //close source directory
    err = closedir(dirStrm);
    if(err < 0)
    {
        fprintf(stderr, "copy: unable to close %s: %s\n", sourcepath, strerror(errno));
        return -1;
    }

    return 0;
}

//start will fork to create a new process and then the child process will exec the
//executable fileToExec with the arguments args. 
int start(char *fileToExec, char *args[])
{
    //fork
    int cpid = fork();
    //if fork fails
    if(cpid < 0) 
    {
        fprintf(stderr, "start: fork failed: %s\n", strerror(errno));
        return -1;
    }
    //in the child
    else if(cpid == 0) 
    {
        int err = execvp(fileToExec, args);
        //don't really need to check because if we get here then execvp failed. But
        //if execvp failed, print an error and exit the child
        if(err == -1)
        {
            fprintf(stderr,"start: could not exec %s: %s\n", fileToExec, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    //in the parent print the pid of the child process that has been started
    else
    {
        printf("start: process %d started\n", cpid);
        return cpid;
    }
    
    //should never get here, so return -1 to indicate error if so
    return -1;
}

//myWait: if wpid = -1, will wait on any child process to finish
//        otherwise, will wait on the child process specified by wpid
int myWait(int wpid)
{
    //if the user is trying to wait on a specific process
    if(wpid > 0)
    {
        //first check if that process exists
        if(kill(wpid, 0) != 0)
        {
            fprintf(stderr, "wait: could not wait: %s\n", strerror(errno));
            return -1;
        }
    }
    //wait on the specified process (if wpid = -1, will wait on any process)
    int wstatus;
    int waitedOn = waitpid(wpid, &wstatus, 0);
    if(waitedOn < 0)
    {
        fprintf(stderr, "wait: could not wait: %s\n", strerror(errno));
        return -1;
    }
    else
    {
        //if the process exited normally by calling exit() or reaching the end of main
        if(WIFEXITED(wstatus))
        {
            //output a normal exit and the given status
            int status = WEXITSTATUS(wstatus);
            printf("wait: process %d exited normally with exit status %d\n", waitedOn, status);
            return 0;
        }
        //if the process exited due to a signal
        else if(WIFSIGNALED(wstatus))
        {
            //output an abnormal exit and the given signal
            int termSig = WTERMSIG(wstatus);
            printf("wait: process %d exited abnormally with signal %d: %s\n", waitedOn, termSig, strsignal(termSig));
            return 0;
        } 
    }

    //should never get here, so return -1 to indicate error if so
    return -1;
}

//myKill will send a SIGKILL signal to the child process identified by kpid
int myKill(int kpid)
{
    //attempt to kill the process and check if it fails
    if(kill(kpid, SIGKILL) < 0)
    {
        fprintf(stderr, "kill: could not kill process %d: %s\n", kpid, strerror(errno));
        return -1;
    }
    //otherwise it succeeded
    else
    {
        printf("kill: process %d killed\n", kpid);
        return 0;
    }
}

int main(const int argc, const char* argv[])
{
    //check for correct number of args
    if(argc != 1)
    {
        fprintf(stderr, "myshell usage: ./myshell\n");
        exit(EXIT_FAILURE);
    }

    //set up buffers and vars to store user commands
    char inputBuf[1024];
    char *args[100];
    int numArgs = 0;
    memset(inputBuf, 0, sizeof(inputBuf));

    
    printf("myshell> ");
    fflush(stdout);
    //fgets could return NULL because EOF was reached or because of an error
    //so we set errno to 0 before every call of fgets so that if it does
    //return NULL we can check if it was due to an error or just because EOF
    //was reached
    errno = 0;
    while(fgets(inputBuf, sizeof(inputBuf), stdin) != NULL)
    { 
        //if the user entered any input split the args and store them in args[]
        if((args[numArgs] = strtok(inputBuf, " \t\n")))
        {
            numArgs++;
            while((args[numArgs] = strtok(NULL, " \t\n")))
            {
                numArgs++;
            }
            args[numArgs] = 0;

            //if-else-if chain checking for all know commands
            //list
            if(!strcmp(args[0], "list")) {
                if(numArgs > 1)
                {
                    fprintf(stderr, "list: unknown arguments\n");
                }
                else if(list() != 0) 
                    fprintf(stderr, "list failed\n");
            }
            //chdir <newpath>
            else if(!strcmp(args[0], "chdir")) {
                if(numArgs == 1)
                {
                    fprintf(stderr, "chdir: please include a path\n");
                }
                else if(numArgs > 2)
                {
                    fprintf(stderr, "chdir: too many arguments\n");
                }
                else if(myChdir(args[1]) != 0) 
                    fprintf(stderr, "chdir failed\n");
            }
            //pwd
            else if(!strcmp(args[0], "pwd")) {
                if(numArgs > 1)
                {
                    fprintf(stderr, "pwd: unknown arguments\n");
                }
                else if(pwd() != 0) 
                    fprintf(stderr, "pwd failed\n");
            }
            //copy <sourcepath> <destinationpath>
            else if(!strcmp(args[0], "copy")) {
                struct copyStats st;
                if(numArgs != 3)
                {
                    fprintf(stderr, "copy: copy <sourcepath> <destinationpath>\n");
                }
                else if(copyDir(args[1], args[2], &st) != 0)
                {
                    fprintf(stderr, "copy: could not copy from %s to %s\n", args[1], args[2]);
                }
                else
                {
                    //stat the source file to see if it was a directory or a file
                    struct stat sourcestat;
                    if(stat(args[1], &sourcestat) != 0)
                    {
                        fprintf(stderr, "copy: error checking stat of file %s: %s\n", args[1], strerror(errno));
                        return -1;
                    }
                    //format output according to whether a directory or a file was copied
                    if(S_ISREG(sourcestat.st_mode))
                    {
                        printf("copy: copied %d bytes from %s to %s\n", st.numBytes, args[1], args[2]);
                    }
                    else if(S_ISDIR(sourcestat.st_mode))
                    {
                        printf("copy: copied %d directories, %d files, and %d bytes from %s to %s\n", st.numDir, st.numFile, st.numBytes, args[1], args[2]);
                    }
                }
            }
            //start <command> <arg1> <arg2> ...
            else if(!strcmp(args[0], "start")) {
                if(start(args[1], &args[1]) < 0)
                {
                    fprintf(stderr, "start failed\n");
                }
            }
            //wait
            else if(!strcmp(args[0], "wait")) {
                if(numArgs != 1)
                {
                    fprintf(stderr, "wait: unknown arguments\n");
                }
                else if(myWait(-1) != 0)
                {
                    fprintf(stderr, "wait failed\n");
                }
            }
            //waitfor <pid>
            else if(!strcmp(args[0], "waitfor")) {
                if(numArgs == 1)
                {
                    fprintf(stderr, "waitfor: please include a child pid to wait for\n");
                }
                else if(numArgs > 2)
                {
                    fprintf(stderr, "waitfor: unknown arguments\n");
                }
                else if(myWait(atoi(args[1])) != 0)
                {
                    fprintf(stderr, "waitfor failed\n");
                }
            }
            //run <command> <arg1> <arg2> ...
            else if(!strcmp(args[0], "run")) {
                int cpid;
                if((cpid = start(args[1], &args[1])) < 0)
                {
                    fprintf(stderr, "start failed\n");
                }
                else if(myWait(cpid) != 0)
                {
                    fprintf(stderr, "waitfor failed\n");
                }
            }
            //kill <pid>
            else if(!strcmp(args[0], "kill")) {
                if(numArgs < 2)
                {
                    fprintf(stderr, "kill: please include a pid to signal to\n");
                }
                else if(numArgs > 2)
                {
                    fprintf(stderr, "kill: unknown arguments\n");
                }
                else if(myKill(atoi(args[1])) != 0)
                {
                    fprintf(stderr, "kill failed");
                }
            }
            //exit
            //quit
            else if(!strcmp(args[0], "exit") || !strcmp(args[0], "quit")) {
                exit(EXIT_SUCCESS);
            }
            else{
                printf("myshell: unknown command: %s\n", args[0]);
            }
        }

        //reprompt user and reset buffers
        printf("myshell> ");
        fflush(stdout);
        memset(inputBuf, 0, sizeof(inputBuf));
        numArgs = 0;
        errno = 0;
    }
    //check if fgets returned NULL because of EOF or error
    if(errno != 0)
    {
        fprintf(stderr, "myshell: error reading input: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } 
}
