#include <stdio.h>
#include <stdlib.h>
#define LINESIZE 1024




int main(int argc, char *argv[]){
 
 char line[LINESIZE];
 char *argv[ARGVMAX]; // Array to hold arguments

    while (1) {
        
        if (fgets(line, LINESIZE, stdin) == NULL) break;  // EOF

        line[strlen(line) - 1] = '\0';
        if (strcmp(line, "exit") == 0) break; // Termina

        // Use makeargv to split the line into arguments
        int argc = makeargv(line, argv);
        if (argc > 0) {
            runcmd(argv);
        }
    }
    return 0;
}
