// closh.c - COSC 315, Winter 2020
// YOUR NAME HERE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

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

        int counter = 0;
        //sequential section
        if(parallel == 0){ 
        for(int i = 0; i < count; i++){
            //printf("Parent is: %d \n",getpid()); //this should be the parent process
            pid_t pid_fork = fork();
            if(pid_fork == -1){printf("Fork failed");}
            
            //start timer
            clock_t time;
            time = clock();
            //child process
            if(pid_fork == 0){ 
                printf("%d\n", counter);
                // if(counter == 2){
                //     sleep(5);
                //      printf("Parent process is: %d with the child: %d\n",getppid(),getpid());
                // execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program // which essentially runs the command/program given
                // } else{
                printf("Parent process is: %d with the child: %d\n",getppid(),getpid());
                execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program // which essentially runs the command/program given
               // }
            }
            
            //parent process
            else if (pid_fork > 0){ //this is the parent process
                time = clock() - time;
                double time_elapsed = ((double)time)/CLOCKS_PER_SEC;
                waitpid(pid_fork, NULL, 0);
                if(time_elapsed > timeout && timeout > 0){
                    kill(pid_fork, SIGKILL);
                }

            }
            counter ++;
        }
        exit(1);
        //parallel section
        } else if(parallel == 1){

        }
        
        // just executes the given command once - REPLACE THIS CODE WITH YOUR OWN
        // execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program
        // doesn't return unless the calling failed
        //printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
        exit(1);        
    }
}

