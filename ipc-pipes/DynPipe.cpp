// file: DynPipe.cpp
// author: Bo Seong Kim
// date: 11/13/2025
// purpose: CS3377
// description:
// 	this program is dynamic and execute two to five arguments passed as arguments.
// 	each argument should be a unix/linux command with its parameters.
// 	it executes arguments respectively, assuming only valid commands can be used.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> // for wait()
#include <string.h> // strtok

int main(int argc, char **argv) {
	// argc[0] = program name
	if (argc < 3 || argc > 6){ // 3 <= # of arguments <= 5
		fprintf(stderr, "error: the number of commands should be at least two or at most 5\n");
		exit(1);
	}
  
  int num_cmds = argc - 1; // # of commands = argc - 1
	int pipes[4][2]; // at most 5 commands = 4 pipes
  
  // create pipes
	for (int i = 0; i < num_cmds - 1; i++) { // # of pipes = # of commands - 1
    // validate
    if (pipe(pipes[i]) == -1) {
      perror("failed pipe");
		  exit(1);
	  }
  }
	
  // create a child process for each command
	for (int i = 0; i < num_cmds; i++) {
    int pid = fork();
    // validate
    if (pid == -1) {
      perror("failed fork");
      exit(1);
    }

    // if child process
    if (pid == 0) {
      // stdin
      if (i > 0) { // no stdin need for the first command (i = 0)
        dup2(pipes[i-1][0], 0);
      }
      // stdout
      if (i < num_cmds - 1) {
        dup2(pipes[i][1], 1);
      }

      // close all pipes
      for (int j = 0; j < num_cmds - 1; j++) {
        close(pipes[j][0]);
        close(pipes[j][1]);
      }

      char *args[10]; // command array
      int k = 0; 
      char *token = strtok(argv[i+1], " "); //
        
      while (token != NULL) {
        args[k] = token;
        k = k + 1;
        token = strtok(NULL, " ");
      }
      args[k] = NULL; // null terminator for execvp


      execvp(args[0], args);
      perror("execvp failed");
      exit(1);
    }
  }

  for (int i = 0; i < num_cmds - 1; i++) {
    close(pipes[i][0]);
    close(pipes[i][1]);
  }

   
  for (int i = 0; i < num_cmds; i++) {
    wait(NULL);
  }

  return 0;
}
    
