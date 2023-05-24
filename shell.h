#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno & perror*/
#include <sys/types.h> /* for type pid*/
#include <sys/wait.h> /* for wait*/
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management*/
#include <fcntl.h> /* for open files*/

/************** MACROS **************/

#include "macros.h" /* for msg, help and prompt*/

/************** STRUCTURES **************/

/**
 * struct info - struct for the program's data
 *
 * @program_name: the name of the executable
 * @input_line: pointer to the input read of _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of executed commands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized output
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 *
 * @builtin: name of the builtin
 * @function: associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/************** MAIN FUNCTIONS **************/


/*========== shell.c ==========*/

/* Inicialize the struct with the info of the program */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt */
void sisifo(char *prompt, data_of_program *data);

/* Prints the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);


/*========== _getline.c ==========*/

/* Read one line of the standard input */
int _getline(data_of_program *data);

/* Split each linefor the logical operators if it exists */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*========== expansions.c ==========*/

/* expand variables */
void expand_variables(data_of_program *data);

/* expand aliases */
void expand_alias(data_of_program *data);

/* append the string to the end of the buffer */
int buffer_add(char *buffer, char *str_to_add);


/*========== _strtok.c ==========*/

/* Separate the string into tokens using a designed delimeter */
void tokenize(data_of_program *data);

/* Creates a pointer to that part of the string */
char *_strtok(char *line, char *delim);


/*========== execute.c ==========*/

/* Executes a command with its entire path */
int execute(data_of_program *data);


/*========== builtins_list.c ==========*/

/* If match a builtin, executes it */
int builtins_list(data_of_program *data);


/*========== find_in_path.c ==========*/

/* Creates an array of the path directories */
char **tokenize_path(data_of_program *data);

/* Search for program in path */
int find_program(data_of_program *data);


/************** HELPERS FOR MEMORY MANAGEMENT **************/


/*========== helpers_free.c ==========*/

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free the fields needed for each loop */
void free_recurrent_data(data_of_program *data);

/* Free all field of the data */
void free_all_data(data_of_program *data);


/************** BUILTINS **************/


/*========== builtins_more.c ==========*/

/* Close the shell */
int builtin_exit(data_of_program *data);

/* Change the current directory */
int builtin_cd(data_of_program *data);

/* set the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* show help information */
int builtin_help(data_of_program *data);

/* set, unset and show alias */
int builtin_alias(data_of_program *data);


/*========== builtins_env.c ==========*/

/* Shows the environment where the shell runs */
int builtin_env(data_of_program *data);

/* Create or overide a variable environment */
int builtin_set_env(data_of_program *data);

/* Delete a variable environment */
int builtin_unset_env(data_of_program *data);


/************** HELPERS FOR ENVIRONMENT VARIABLE MANAGEMENT **************/


/*========== env_management.c ==========*/

/* Gets the vakue of an environment variable */
char *env_get_key(char *name, data_of_program *data);

/* Overwrite the value of the environment variable */
int env_set_key(char *key, char *value, data_of_program *data);

/* Remove a key from the environment */
int env_remove_key(char *key, data_of_program *data);

/* Prints the current environ */
void print_environ(data_of_program *data);


/************** HELPERS FOR PRINTING **************/


/*========== helpers_print.c ==========*/

/* Prints a string in the standard output */
int _print(char *string);

/* Prints a string in the standard error */
int _printe(char *string);

/* Prints a string in the standard error */
int _print_error(int errorcode, data_of_program *data);


/************** HELPERS FOR STRING MANAGEMENT **************/


/*========== helpers_string.c ==========*/

/* Counts the number of characters of a string */
int str_length(char *string);

/* Duplicates a string */
char *str_duplicate(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);

/* Reverses a string */
void str_reverse(char *string);


/*========== helpers_numbers.c ==========*/

/* Cast from int to string */
void long_to_string(long number, char *string, int base);

/* Convert a string into a number */
int _atoi(char *s);

/* Count the coincidences of a character in a string */
int count_characters(char *string, char *character);


/*========== alias_management.c ==========*/

/* Print the list of alias */
int print_alias(data_of_program *data, char *alias);

/* Get the alias name */
char *get_alias(data_of_program *data, char *alias);

/* Set the alias name */
int set_alias(char *alias_string, data_of_program *data);


#endif
