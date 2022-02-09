<h1 align="center">
  Closh.0
</h1>
<p align="center">
  
</p>

<p align="center">
 Closh.0 is a simple shell-like program designed to run multiple copies of a program at once. 
</p> 

<p align="center">
  🚧
 Closh.0 was developed for the COSC 315 Operating Systems course at the University of British Columbia Okanagan.
  🚧
</p>

<br><br>

## Table of Contents

- [Documentation](#documentation)
- [Contributors](#contributors)
- [Resources](#resources)

### Documentation
 - [Project Outline](#project-outline)
 - [Design Choices](#design-choices)
 - [Feautres](#features)
 - [Unfinished Feautres](#unfinished-features)
 - [Sample Output](/sample-output.txt) TBD

### Contributors
 - [Ben Wilson](https://github.com/benmwilson)
 - [Eric Shanks](https://github.com/EricShanks68)
 - [Richardo Brown](https://github.com/Buttertoastt)
 
#### Project Outline

The goal of this project is to implement a simple shell in C, which will require the use of
system calls directly. Using system calls like fork and exec, we have implemented a command-line shell like Bash. 
Closh.0, (aka Clone Shell Zero), is a simple shell-like program designed to run multiple copies of a program at once. 


#### Design Choices




#### Features
The features included in this project are creating new processes, having the processes run either in parallel or sequentially,
 and timing out the processes. 
 
* The creating new processes feature takes an integer from 1 to 9 from the user, then creates a loop that that runsthe amount of times that the user specified. In each iteration of the loop the fork() method is called to create a child process which is just a copy of the parent process. In each iteration, in the child process that was just created, we call execvp() to replace the current program (what the parent process is currently running) with a new program that the user has specified.

* The program also asks the user if they want the processes to run in parallel or sequentially. 
  * If the program is running sequentially a waitpid() must called. This causes the parent process to wait for the child process that was just forked to finish before the parent process can continue. This makes the child processes run sequentially. 
  * For the paralallel code, the lack of a waitpid() call or a waitpid() call with the parameter of WNOHANG will cause the parent process to continue without waiting for the child process to finish which causes the parent and all the children processes to run in parallel.

*  The user produces a timeout value. If the time elapsed of the child process is greater than the timeout value then the parent kills the child process.

### Unfinished Features
* Could not get our timer to work properly. The code for checking if time elapsed is greater than the timeout value works properly, so the parent will kill the child process properly if this condition is met. The issue we are running into is tracking the time that the child process is taking. We are not sure when the timer should start and when the timer should end for the timeout value to produce a reasonable value. How we might fix this if we had more time would be figureout how to better track the child process when the execvp() function is called and track the new program.


### Resources

* https://www.geeksforgeeks.org/fork-system-call/
* https://www.geeksforgeeks.org/difference-fork-exec/
* https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/ 
* https://www.delftstack.com/howto/c/kill-child-process-in-c  
* https://canvas.ubc.ca/courses/86705/discussion_topics/1334092
* https://linuxhint.com/sigalarm_alarm_c_language/
