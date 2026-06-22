// file: TwoPipeTwoChildren.cpp
// author: Bo Seong Kim
// date: 11/10/2025
// purpose: CS3377
// description: 
// 	this program executes "ls -ltr | grep 3377 | wc -l", by deviding the three command
//	among the children and parent process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char **argv){
	// initialize childpid
	int childpid1;
	int childpid2;
	
	// cat -> grep -> wc
	// child1 child2  parent
	char *cat_args[] = {(char *) "ls", (char *) "-ltr", NULL};
	char *grep_args[] = {(char *) "grep", (char *) "3377", NULL};
	char *wc_args[] = {(char *) "wc", (char *) "-l", NULL};

	// create two pipes to send the output of one command to the next command	
	// pipe 1: ls to grep
	// pipe 2: grep to wc
	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	
	// create the first child process and check if it is created
	if ((childpid1 = fork()) == -1){
		perror("Error creating a child process for ls");
		exit(1);
	}
	// child1: ls -ltr
	if (childpid1 == 0){
		// replace cat's stdout with write part of 1st pipe
		dup2(pipe1[1], 1);

		// close all pipes (very important!); end we're using was safely copied
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
		
		// execute ls -ltr and exit if failed
		execvp(*cat_args, cat_args);
		perror("execvp failed for ls");
		exit(1);
	}
	
	// create the second child process and check if it is created
	if ((childpid2 = fork()) == -1){
		perror("Error creating a child process for grep");
		exit(1);
	}
	// child2: grep 3377
	if (childpid2 == 0){
		// replace grep's stdin with read part of 1st pipe
		// replace grep's stdout with write part of 2nd pipe
		dup2(pipe1[0], 0);
		dup2(pipe2[1], 1);
		
		// close all pipes
		close(pipe1[0]);
		close(pipe1[1]);		
		close(pipe2[0]);
		close(pipe2[1]);
		
		// execute grep 3377 and exit if failed
		execvp(*grep_args, grep_args);
		perror("execvp failed for grep");
		exit(1);
	}
	
	// parent: wc -l
	// replace wc's stdout with write part of 2nd pipe
	dup2(pipe2[0], 0);
	
	// close all pipes
	close(pipe1[0]);
	close(pipe1[1]);
	close(pipe2[0]);
	close(pipe2[1]);
	
	// execute wc -l and exit if failed
	execvp(*wc_args, wc_args);
	perror("execvp failed for wc");
	exit(1);
}
