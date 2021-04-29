#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int childFunction(char *string);

char input;
char *line = &input;
char str[100];
int status;
int pid;
char buffer[100];

int strlength(char *string)
{
    int len = 0;
    while (string[len] != '\0')
    {
        len++;
    }
    return len;
}

int main(void)
{
    char buffer[100];
    char m1[] = "This program makes simple arithmetics, enter \"quit\" to exit\n";
    write(STDOUT_FILENO, m1, strlength(m1));

    while (1)
    {
        char m2[] = "Enter an arithmetic statement, e.g., 34 + 132 > ";
        write(STDOUT_FILENO, m2, strlength(m2));

        int i = 0;
        char ch;
        do
        {
            read(STDIN_FILENO, &ch, 1);
            str[i] = ch;
            i++;
        } while (ch != '\n');
        str[i] = '\0';
        if (strcmp(str, "quit\n") == 0)
        {
            printf("\nQUIT CALCULATOR!\n");
            exit(1);
        }
        else {
        //Create child process
            pid = fork();

            if (pid == 0)
            {
                childFunction(str);
            }
            else
            {
                if (pid > 0)
                {
                    char m3[] = "\nCreated a child to make your operation, waiting\n";
                    write(STDOUT_FILENO, m3, strlength(m3));
                    wait(&status);

                    //Task 5
                    if (WEXITSTATUS(status) == 50)
                        write(STDOUT_FILENO, "Wrong Statement\n\n", strlength("Wrong Statement\n\n"));

                    else if (WEXITSTATUS(status) == 100)
                        write(STDOUT_FILENO, "Division by zero\n\n", strlength("Division by zero\n\n"));

                    else if (WEXITSTATUS(status) == 200)
                        write(STDOUT_FILENO, "Wrong operator\n\n", strlength("Wrong operator\n\n"));
                }
            }
        }
    }

    return (0);
}

int childFunction(char *line)
{
    char opt;
    int num1, num2;

    char msg[] = "I am a child working for my parent\n";
    write(STDOUT_FILENO, msg, strlength(msg));
    sscanf(line, "%d %c %d", &num1, &opt, &num2);

    sleep(1);
    if ((sscanf(line, "%d %c %d", &num1, &opt, &num2)) != 3)
        exit(50);

    if (opt == '/' && num2 == 0)
        exit(100);

    switch (opt)
    {
    case '+':
        sprintf(buffer, "%d %c %d = %d\n\n", num1, opt, num2, num1 + num2);
        write(STDOUT_FILENO, buffer, 15);
        break;

    case '-':
        sprintf(buffer, "\n%d %c %d = %d\n\n", num1, opt, num2, num1 - num2);
        write(STDOUT_FILENO, buffer, 15);
        break;

    case '/':
        sprintf(buffer, "\n%d %c %d = %d\n\n", num1, opt, num2, num1 / num2);
        write(STDOUT_FILENO, buffer, 15);
        break;

    case '*':
        sprintf(buffer, "\n%d %c %d = %d\n\n", num1, opt, num2, num1 * num2);
        write(STDOUT_FILENO, buffer, 15);
        break;

    default:
        exit(200);
        break;
    }
    exit(0);
}
