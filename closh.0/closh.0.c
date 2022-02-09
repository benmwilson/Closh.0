// closh.0.c - COSC 315, Winter 2021 
// Ben Wilson 35835933
// Eric Shanks 72533946
// Richardo Brown 10142529

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

pid_t childPid;

void terminator(int inSignal) { // handler function for the alarm, aka the terminator
	
    printf("Alarm signal called, terminating child process %d. I'll be back...\n", childPid);
    kill(childPid, SIGKILL); // kill child process, rest in pep
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    
    int parallel; // whether to run in parallel or sequentially
    
    signal(SIGALRM, terminator);
    
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
			
            for (int i = 0; i < count; i++) {

                childPid = fork();
				
                if (childPid == -1) { // quick error catching, display error msg 
					
                    printf("Error while forking (don't ask us), please try again.");
					exit(1); // exit failure, abnormal program termination
				}

				else if (childPid == 0) { // have child process do its work and then immediately exit
					
                    printf("Child process %d forked with Parent process %d\n", getpid(), getppid());
					execvp(cmdTokens[0], cmdTokens); // swaps out the current process with the program given from user
					
                    printf("Child process %d failed execution\n", getpid()); // only executes if the process fails :(
                    exit(1); // exit failure

				} else { // wait for child process to wrap up
					
                    alarm(timeout); // if the child process that is currently running exceeds the timeout then the alarm goes
					
                    waitpid(-1, NULL, 0); // sits and waits for all child processes to end  (-1 for any process)

				}
			}

			alarm(0); // alarm reset after each sequential execution

		} else { // parallel execution
            
			pid_t childPidArr[count]; // child pid array
			
			for (int i = 0; i < count; i++) {
				
                childPidArr[i] = fork();
				
                if(childPidArr[i] == -1){ // quick error catching, display error msg 
					
                    printf("Error while forking (don't ask us), please try again.");
					exit(1); // exit failure, abnormal program termination

                } else if (childPidArr[i] == 0) { //child process does work then exits
					
                    printf("Child process %d forked with Parent process %d\n", getpid(), getppid());
					alarm(timeout);
					
                    execvp(cmdTokens[0], cmdTokens); // swaps out the current process with the program given from user
					
                    printf("Child process %d failed execution\n",getpid()); // only reached if running there is a failure :(
				    
                    exit(1);
				}
			}
			
            for (int j = 0; j < count; j++) {
				
                if (childPidArr[j] > 0) { 
					
                    waitpid(childPidArr[j], NULL, 0); // terminate any lingering child processes
				}
			}

		}
	} 
	
}


