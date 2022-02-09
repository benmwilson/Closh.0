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

pid_t pid_fork;

int terminator(int inSignal) { // handler function for the alarm, aka the terminator
	
    printf("Alarm signal called, terminating child process %d. I'll be back...\n", pid_fork);
    kill(pid_fork, SIGKILL); // kill child process, rest in pep
    return pid_fork;
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings  //name of program
    int count; // number of times to execute command //number of copies of program
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)

    signal(SIGALRM, terminator);
    
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
        int pid_array[count];
        clock_t timep;
        pid_t pid_forkp;
        clock_t time_end;
        clock_t time;
        double time_elapsed;
        int status;
        pid_t current_pid; //rename
        int killed;

        //sequential section
        if(parallel == 0){ 
        for(int i = 0; i < count; i++){
            //printf("Parent is: %d \n",getpid()); //this should be the parent process
            pid_fork = fork();
            if(pid_fork == -1){printf("Fork failed");}

                
              //child process
            if(pid_fork == 0){ 
                printf("iteration number is %d Parent process is: %d with the child: %d\n",counter, getppid(),getpid());
                execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program // which essentially runs the command/program given
                printf("Child process %d failed execution\n", getpid());
                exit(1);
            }
            
            //parent process
             else if (pid_fork > 0){ 
            //wait for child process before continuing 
                current_pid = waitpid(pid_fork, &status, 0); 
                if(current_pid == pid_fork){
                    killed = alarm(timeout); // if the child process that is currently running exceeds the timeout then the alarm goes
                    if(killed != 0){
                    printf("iteration number is %d child process %d is finished \n",counter, getpid());
                    }
                }
            }
            //keep track of iteration order
            counter ++;
        }
        exit(1);
        //parallel section
        } else if(parallel == 1){
            for(int i = 0; i < count; i++){
            pid_forkp = fork();
            if(pid_forkp == -1){printf("Fork failed");}
            
            //child process
            if(pid_forkp == 0){ 
                printf("iteration number is %d Parent process is: %d with the child: %d\n",counter, getppid(),getpid());
                execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program // which essentially runs the command/program given
                printf("Child process %d failed execution\n", getpid());
                exit(1);

            }
            
            //parent process
            else if (pid_forkp > 0){ 
                current_pid = waitpid(pid_fork, &status, WNOHANG); 
                 if(current_pid == pid_fork){
                    killed = alarm(timeout); // if the child process that is currently running exceeds the timeout then the alarm goes
                    if(killed != 0){
                    printf("iteration number is %d child process %d is finished \n",counter, getpid());
                    }
                }

            }
            counter ++;
        }
        // //check the timeout for the child processes
        // for(int i =0; i < count; i++){
        //      alarm(timeout); // if the child process that is currently running exceeds the timeout then the alarm goes
        //         }
        }
        exit(1);
    }
        
        exit(1);        
}


