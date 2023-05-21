#include "shell.h"

/*
 * main - Entry point to the shell
 * @argc: arguements count
 * @argv: arguements values
 * @env: environment vector
 * Return : the process
 */
int main(int argc, char *argv[], char *env[])
{
	int mode, counter = 0, *status, t = 0, non_int_count = 1;
	char *line, **line_vector = NULL, *new_path;
	list_path *current;
	/*mode checking*/
	current = set_all_paths_to_list();
	mode = check_mode(argc);
	status = &t;
	while (++counter && non_int_count)
	{
		if (mode == NON_INTERACTIVE_PIPED)
		{
			line = get_command_from_pipe();
			non_int_count = 0;/*stop*/
		}
		else if (mode == NON_INTERACTIVE_FILE)
			line = get_command_from_file(argv[1]);
		else if (mode == INTERACTIVE)
			line = get_command_from_user(current);
		if(!line)
			continue;
		line_vector = get_av_with_flags(line, *status);
		if(is_dir(line_vector[0]) == 0)
		{
			print_error(argv[0] , counter, line_vector[0], PERMISSION_DENIED);
			*status = PERMISSION_DENIED;
			free_l_v(line, line_vector);
			continue;
		}
		if (is_built_in(line, line_vector, current, argv[0], counter, status) != 0)	
			{
			if (access(line_vector[0], X_OK) == 0)
				execute_command(line_vector[0], line_vector, env, status);
				else
				{
					if ((new_path = check_access(line_vector[0], current)))
					{
						execute_command(new_path, line_vector, env, status);
						free(new_path);
					}
					else
					{
						print_error(argv[0] , counter, line_vector[0], NOT_FOUND);
						*status = NOT_FOUND;
					}
				}
			}
		free_l_v(line, line_vector);
	}
	exit(*status);
}

char *get_command_from_pipe()
{
	char input[1024];
    ssize_t bytesRead;
	char* command;
	
    bytesRead = read(STDIN_FILENO, input, 1024);
	if(bytesRead == -1)
		return (NULL);

	input[bytesRead - 1] = '\0';
    command = strtok(input, " ");
	command = _strdup(command);
	if (!command)
		return (NULL);
	
	return command;
	
}
void free_l_v(char * line, char ** line_vector)
{
	free(line);
	free_vector(line_vector);
}

int is_dir(char *line)
{
	struct stat st;

    if (stat(line, &st) == 0)
	 {
        if (S_ISDIR(st.st_mode)) 
		{
            return (0);
        }
    }
	return (-1);
}

void print_error(char *program_name , int counter,char *command, int type_of_error)
{
	char * counter_s;

	counter_s = num_to_char(counter);
	write(STDERR_FILENO, program_name, _strlen(program_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_s, _strlen(counter_s));
	write(STDERR_FILENO, ": ", 2);
	if(type_of_error == EXIT_ERROR)
		write(STDERR_FILENO, "exit", 4);
	else
		write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": ", 2);
	if(type_of_error == NOT_FOUND)
		write(STDERR_FILENO, "not found\n", 10);
	else if(type_of_error == PERMISSION_DENIED)
		write(STDERR_FILENO, "Permission denied\n", 18);
	else if(type_of_error == EXIT_ERROR)
	{
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, command, _strlen(command));
		write(STDERR_FILENO, "\n", 1);
	}
	free(counter_s);
}
