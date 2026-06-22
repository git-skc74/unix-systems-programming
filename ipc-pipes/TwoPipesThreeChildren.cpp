// file: TwoPipesThreeChildren.cpp
// author: Bo Seong Kim
// date: 11/12/2025
// purpose: CS3377
// description:
// 	this program executes "ls -ltr | grep 3377 | wc -l", by dividing the threee command
// 	among three children processes

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> // For waitpid

int main (int argc, char **argv){
	int status; // for waitpid, to check if a child process is finished successfully
	
	// for three child processes
	int childpid1;
	int childpid2;
	int childpid3;
	
	// cat -> grep -> wc
	// child1 child2 child3
	char *cat_args[] = {(char *)"ls", (char *)"-ltr", NULL};
	char *grep_args[] = {(char *)"grep", (char *)"3377", NULL};
	char *wc_args[] = {(char *)"wc", (char *)"-l", NULL};
	
	// create two pipes
	int pipe1[2];
	int pipe2[2];
	
	pipe(pipe1);
	pipe(pipe2);
	
	// create a child process and exit if failed
	if ((childpid1 = fork()) == -1){
		perror("Error creating a child process");
		exit(1);
	}
	// child1: ls -ltr
	if (childpid1 == 0){
		// ls's stdout -> write part of pipe1
		dup2(pipe1[1], 1);
		
		// close all pipes
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		
		// execute the command and exit if failed
		execvp(*cat_args, cat_args);
		perror("execvp failed for ls");
		exit(1);
	}
	
	// create a child process and exit if failed
	if ((childpid2 = fork()) == -1){
		perror("Error creating a child process");
		exit(1);
	}
	// child2: grep 3377
	if (childpid2 == 0){
		// grep's stdin -> read part of pipe1
		// grep's stdout -> write part of pipe2
		dup2(pipe1[0], 0);
		dup2(pipe2[1], 1);
		
		// close all pipes
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		
		// execute the command and exit if failed	
		execvp(*grep_args, grep_args);
		perror("execvp failed for grep");
		exit(1);
	}
	
	// create a child process and exit if failed
	if ((childpid3 = fork()) == -1){
		perror("Error creating a child process");
		exit(1);
	}
	// child3: wc -l
	if (childpid3 == 0){
		// wc's stdin -> read part of pipe2
		dup2(pipe2[0], 0);
		
		// close all pipes
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);

		// execute the command and exit if failed	
		execvp(*wc_args, wc_args);
		perror("execvp failed for wc");
		exit(1);
	}	
	
	// parent
	// close all pipes
	close(pipe1[0]);
	close(pipe1[1]);
	close(pipe2[0]);
	close(pipe2[1]);
	
	// wait until all child processes finish running
	waitpid(childpid1, &status, 0);
	waitpid(childpid2, &status, 0);
	waitpid(childpid3, &status, 0);	

	return 0;
}
