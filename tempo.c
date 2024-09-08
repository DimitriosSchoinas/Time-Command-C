#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/time.h>


void waitloop( int pid){

int p;
do{
p = wait(NULL);
if (p==-1) perror("wait");
}while (p!=pid);
}

void getElapsedTime(struct timeval start, struct timeval end){

double executionTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("\nElapsed time = %.6f s\n", executionTime);
}


int main(int argc, char *argv[]) {
    
    struct timeval start, end;
    
    gettimeofday(&start, NULL);
    
    int bg = 0;
    int last = 0;
    
    if (argv[last] != NULL) {
        while (argv[last] != NULL)
            last++;
        if (strcmp(argv[last - 1], "&") == 0) {
            argv[last - 1] = NULL;
            bg = 1;
        }
    }

    pid_t pid = fork();
    switch (pid) {
        case -1:
            perror("fork");
            break;
        case 0:{
  
           char *outputFile = NULL;

    
        if (argv[argc - 1][0] == '=') {
            outputFile = argv[argc - 1] + 1; 
            argv[argc - 1] = NULL; 
        }

        if (outputFile) {
                int fd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (fd == -1) {
                    perror(outputFile);
                    exit(1);
                }
             
                if (dup2(fd, STDOUT_FILENO) == -1) {
                    perror("dup2");
                    close(fd);
                    exit(1);
                }
                close(fd);
            }
           
            execvp(argv[1], &argv[1]);
            perror(argv[1]);
            exit(1);
            }
        default:
            if (!bg) {
                waitloop(pid);
            }
            gettimeofday(&end, NULL);
            getElapsedTime(start,end);
    }
    
    return 0;
}


