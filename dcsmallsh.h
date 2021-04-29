
//*****************************************************************
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>


//#include <sys/wait.h>

#define EOL 1 
#define ARG 2 

#define AMPERSAND 3 
#define SEMICOLON 4 
#define MAXARG 512 
#define MAXBUF 512 

#define FOREGROUND 0 
#define BACKGROUND 1

//my addition
#define PIPE 5
#define REDIRECT 6

int argcc;
int timeout;
int ispipe;
int one;
int two;



