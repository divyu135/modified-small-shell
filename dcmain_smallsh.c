#include "dcsmallsh.h"

char *prompt = "$";

int userin(char *p);
void procline(void);

int main()
{
	//To display the "annoying" message 
	printf("\nPlease enter a command within 10 seconds or you will be annoyed...\n\n");
	while (userin(prompt) != EOF)
	{
		//to handle after alarm signal, i.e. with empty buffer.
		if (timeout!=1)
			procline();
		else
			printf("Please enter a command within 10 seconds again or you will be annoyed...\n\n");
	}
}
