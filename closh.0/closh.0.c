// closh.0.c - COSC 315, Winter 2021 
// Ben Wilson 35835933

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
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

pid_t childPid = -1; // create first child pid

static void timeout_kill(int signo) { // handler for the alarm, runs a fade on the calling process
	
    printf("ALARM: Alarm signal called, 360 no scoping the child process: %d out of existence...\n", childPid);
    kill(childPid, SIGKILL);
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    
    int parallel; // whether to run in parallel or sequentially
    
    
    while (TRUE) { // main shell input loop
        
        // begin parsing code - do not modify --- har har har i modified it /bw
        printf("closh.0> ");
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
        
        if (parallel == 0) { // sequential execution
			
            int i;
			
			for (i = 0; i < count; i++) {
				
                if ((childPid = fork()) < 0) { // quick error catching, display error msg 
					
                    fprintf(stderr, "ERROR: Something went wrong when forking (don't ask us), please try again.");
					exit(1);
				}

				else if (childPid == 0) { // have child process do its work and then immediately exit
					
                    printf("CHILD PROCESS: %d forked with PARENT PROCESS ID: %d\n", getpid(), getppid());
					execvp(cmdTokens[0], cmdTokens); // swaps out the current process with the program given from user
					printf("CHILD PROCESS: %d can not execute %s\n",getpid(), cmdTokens[0]); // only executes if the process fails :(
					exit(1);

				} else { // wait for child process to wrap up
					
                    alarm(timeout); // if the child process that is currently running exceeds the timeout then the alarm goes and offs it
					waitpid(-1, NULL, 0); // sits and waits for all child processes to end 

				}
			}

			alarm(0); //resets the alarm after sequential execution

		} else { // parallel execution
			
            //TBD

		}
	} 
	
}

