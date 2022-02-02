// closh.c - COSC 315, Winter 2020
// YOUR NAME HERE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) {
    cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
    int i = 0;
    cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
    while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
        cmdTokens[i] = strtok(NULL, " ");
    }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
    char c = getchar();
    while (getchar() != '\n');
    return c;
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings  //name of program
    int count; // number of times to execute command //number of copies of program
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    
    while (TRUE) { // main shell input loop
        
        // begin parsing code - do not modify
        printf("closh> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') continue;
        readCmdTokens(cmd, cmdTokens);
        do {
            printf("  count> ");
            count = readChar() - '0';
        } while (count <= 0 || count > 9);
        
        printf("  [p]arallel or [s]equential> ");
        parallel = (readChar() == 'p') ? TRUE : FALSE;
        do {
            printf("  timeout> ");
            timeout = readChar() - '0';
        } while (timeout < 0 || timeout > 9);
        // end parsing code

        



        
        ////////////////////////////////////////////////////////
        //                                                    //
        // TODO: use cmdTokens, count, parallel, and timeout  //
        // to implement the rest of closh                     //
        //                                                    //
        // /////////////////////////////////////////////////////
        

        //want to make child processes of current program
        // ie fork()

        //then want to make each child process execute execvp(cmdTokens[0], cmdTokens); which will run the new user command
        //have parallel or sequential processes 
        //probs have to have some waiting for each process to execute if sequential
        //parallelize if parallel

        //if processes take longer than timeout to run, then terminate process
        // printf("the parent process' id is: %d\n", getppid());
        

        //loop creates n amount of processes, but not n child processes from same root process
        for(int i = 0; i < count; i++){
            int pid_fork = fork();
            if(pid_fork != 0){ //if the id of the forked process(child) is not a child process (parent process) then 
                printf("Parent process is: %d with the child: %d\n",getppid(),getpid());
                execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program // which essentially runs the command/program given
                //exit(0); //use exit(0) if need to jump out of the for loop at this point
            }
        }
        
        // just executes the given command once - REPLACE THIS CODE WITH YOUR OWN
        // execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program
        // doesn't return unless the calling failed
        //printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
        exit(1);        
    }
}

