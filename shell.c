#include "shell.h"

/**
 * main - main funciton
 *
 * @ac: argument count
 * @av: argument vector
 * @env: environment variable
 *
 * Return: always 0
 */

int main(int ac, char **av, char **env)
{
	if (ac == 1)
		prompt(av, env);
	return (0);
}
