#include "dcsmallsh.h"

int gettok(char **outptr);
int runcommand(char **cline, int where);

int join(char *com1[]);
void redirect(char *com1[], int arc);

void procline(void)
{
	char *arg[MAXARG + 1];

	int toktype;
	int narg;
	int type;

	narg = 0, one = 0, two = 0;
	int p = 1, rd = 0;
	int re_sbl = 0;

	for (;;)
	{
		switch (toktype = gettok(&arg[narg]))
		{
		case ARG:
			if (narg < MAXARG)
			{
				narg++;
				p == 1 ? one++ : two++;
			}
			break;
		case PIPE:
			printf("\npipe\n");
			ispipe = PIPE;
			p = 0;
			break;
		case REDIRECT:
			printf("\nRedirect\n");
			rd = 1;
			re_sbl = narg;
			break;

		case EOL:
		case SEMICOLON:
		case AMPERSAND:
			// Handling pipe
			if (ispipe == PIPE)
			{
				int ret = join(arg);
				ispipe = 0;
			}
			else if (rd == 1)
			{
				redirect(arg, re_sbl);
			}
			else
			{
				if (toktype == AMPERSAND)
					type = BACKGROUND;
				else
					type = FOREGROUND;
				if (narg != 0)
				{
					arg[narg] = NULL;
					//To use in change directory
					argcc = narg;

					//Task 3: exit the prompt if the user enter
					// quit or exit command
					// also handles error for more arguments with exit or quit
					if (strcmp(arg[0], "quit") == 0 || strcmp(arg[0], "exit") == 0)
					{
						if (narg == 1)
							exit(1);
						else
							printf("error: exit/quit require no arguments\n");
					}
					else if (strcmp(arg[0], "calculator") == 0 || strcmp(arg[0], "./dccalculator") == 0 || strcmp(arg[0], "./calculator") == 0)
					{
						if (narg == 1)
							{	
								signal(SIGALRM, SIG_IGN);
								strcpy(arg[0],"./dccalculator");
								runcommand(arg,type);
							}
						else
							printf("error: exit/quit require no arguments\n");
					}
					else
						runcommand(arg, type);
				}
			}
			if (toktype == EOL)
				return;
			narg = 0;
			break;
		}
	}
}
