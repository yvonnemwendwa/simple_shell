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
	char *string = NULL; //Where input is stored
	int i, status, b;
	size_t n = 0;
	ssize_t num_char; //Stores the no. of chars read by getline
	char *argv[MAX_CMD];
	pid_t child_pid;

	while (1)
	{
		//isatty(int fd) - tests whether fd is an open file descriptor referring to a terminal
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		num_char = getline(&string , &n, stdin); //The return value is stored in num_char
		//n - size of the buffer
		//stdin - file stream to read from
		//input - Where the input is stored

		if (num_char == -1)//Checks whether the getline function failed
		{
			free(string);
			exit(98);
		}

		i = 0;
		while (string[i])
		{   
			if (string[i] == '\n')//Replaces the new line character of a string with a null character'\0' 
				string[i] = 0;
			//This is done to make it easier to parse the input string later
			i++;
		}

		//char *strtok(char *str, const cha *delim) - This function breaks a string into a sequence of zero or more non-empty tokens
		b = 0;
		argv[b] = strtok(string, " ");
		while(argv[b])
			argv[++b] = strtok(NULL, " ");
		/**
		 * Parses the input string into inividual command line arguments using the strtok() function
		 * The delimeter used to separate the arguments is a space character(' ')
		 * The resulting arguments are stored in the 'argv' array
		 */

		//pid_t fork(void)
		//"Type 'man fork' kwa terminal yako kupata manual ya hii function alafu soma description first 2 paragraphs"

		child_pid = fork();/*Child process is created*/
		if (child_pid == -1)/*checks if the fork function failed*/
		{
			free(string);
			exit(98);
		}
		if (child_pid == 0)/*Where we excecute the command that the user typed*/
		{
			// type 'man execve' ikupatie manual ya hii function
			if (execve(argv[0], argv, env) == -1)
			{
				printf("%s: No such file or directory\n", av[0]);
			}
		}
		else //Blocks the parent process until the child process terminates
			wait(&status);/*We are storing it in the address of status*/
	}
}
