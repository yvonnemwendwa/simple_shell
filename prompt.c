#include "shell.h"

#define MAX_CMD 10

/**
 * prompt - displays the prompt like the normal shell
 * 
 * @av: array of strings representing the arguments passed
 * @env: array of strings representing the environment variables
 */
void prompt(char **av, char **env)
{
	char *string = NULL;
	int i, status, b;
	size_t n = 0;
	ssize_t num_char;
	char *argv[MAX_CMD];
	pid_t child_pid;

	while (1)
	{
		 
			if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		num_char = getline(&string , &n, stdin);

		if (num_char == -1)
		{
			free(string);
			exit(98);
		}

		i = 0;
		while (string[i])
		{   
			if (string[i] == '\n')
				string[i] = 0;
			
			i++;
		}

	
		b = 0;
		argv[b] = strtok(string, " ");
		while(argv[b])
			argv[++b] = strtok(NULL, " ");
		/**
		 * Parses the input string into inividual command line arguments using the strtok() function
		 * The delimeter used to separate the arguments is a space character(' ')
		 * The resulting arguments are stored in the 'argv' array
		 */

		
		child_pid = fork();/*Child process is created*/
		if (child_pid == -1)/*checks if the fork function failed*/
		{
			free(string);
			exit(98);
		}
		if (child_pid == 0)/*Where we excecute the command that the user typed*/
		{
			
			if (execve(argv[0], argv, env) == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
			}
		}
		else 
			wait(&status);/*We are storing it in the address of status*/
	}
}
