// Kaustav Vats (2016048)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "shell.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char input[100];
char *pArg[100];
char *path = "/bin/";
char *pPath[30];

int main(int argc, char const *argv[])
{
	printf("Ultra Simple Shell: Type" ANSI_COLOR_RED " 'exit' " ANSI_COLOR_RESET "to exit the shell.\n");
	while ( 1 )
	{
		printf(ANSI_COLOR_CYAN "ush at " ANSI_COLOR_RESET);
		pwd();

		if( fgets(input, 100, stdin) == NULL )
		{
    		break;
		}
		if (input[strlen(input) - 1] == '\n')
		{
    		input[strlen(input) - 1] = '\0';
		}

		if ( strcmp(input, "exit") == 0 )
		{
			printf(ANSI_COLOR_YELLOW "Thankyou for using Ultra Simple Shell.\n" ANSI_COLOR_RESET);
			break;
		}
		// Parse(pArg, input);

		char *parser;
		parser = strtok(input, " ");
		int j = 0;
		while ( parser != NULL )
		{
			pArg[j] = parser;
			parser = strtok(NULL, " ");
			j++;
		}
		pArg[j] = NULL;

		strcpy(pPath, path);
		strcat(pPath, pArg[0]);

		if ( strcmp(pArg[0], "help") == 0 )
		{
			Help();
		}
		else if ( strcmp(pArg[0], "clear") == 0 )
		{
			clear();
		}
		else if ( strcmp(pArg[0], "cd") == 0 )
		{
			chdir(pArg[1]);
		}
		else if ( fork() == 0 )
		{
			// Child
			execvp(pPath, pArg);
		}
		else
		{
			// Parent
			wait(NULL);
		}

	}

	return 0;
}

void Help()
{
	printf("\n-----Need Help?-----\n");
	printf("Commands Available\n");
	printf("cd\n");
	printf("exit\n");
	printf("ls\n");
	printf("pwd\n");
	printf("Some general commands\n");
}
void pwd()
{
	char currentwd[1024];
	getcwd(currentwd, sizeof(currentwd));
	printf("%s ==> ", currentwd );
}
void clear()
{
	printf("\033[H\033[J");
}

// void Parse(char **parg, char *str)
// {
// 	char *parser;
// 	parser = strtok(str, " ");
// 	int j = 0;
// 	while ( parser != NULL )
// 	{
// 		*parg[j] = parser;
// 		parser = strtok(NULL, " ");
// 		j++;
// 	}
// 	*parg[j] = NULL;
// }