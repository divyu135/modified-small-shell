#include "dcsmallsh.h"

void changeDirectory(char **argv);

int runcommand(char **cline, int where)
{
	pid_t pid;
	int status;
	if (strcmp(cline[0],"cd")==0) {
		changeDirectory(cline);
	}
	else 
	switch (pid = fork()) {
		case -1:
			perror("smallsh");
			return (-1);
		case 0:
			// if command is "cd" then call changeDirectory()
			// from "project.c"
			
				execvp(cline[0], cline);
				perror(*cline);
				exit(1);
	}
	//code for parents
	if (where == BACKGROUND)
	{
		printf("[process id %d]\n", pid);
		return (0);
	}
	
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	else
		return (status);
}
