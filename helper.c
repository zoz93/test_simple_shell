#include "shell.h"

/*
 * check_mode - check mode of the program
 * @argc: arguements count
 * Return : mode
 */
int check_mode(int argc)
{
	struct stat stdin_stat;

    fstat(STDIN_FILENO, &stdin_stat);
	
	if(isatty(STDIN_FILENO) && argc == 1)
		return (INTERACTIVE);
	if((!isatty(STDIN_FILENO) || S_ISFIFO(stdin_stat.st_mode)) && argc == 1)
		return (NON_INTERACTIVE_PIPED);
	if((!isatty(STDIN_FILENO) && argc == 2))
		return (NON_INTERACTIVE_FILE);
	
	return (ERROR);
}


void is_exit(char *line,char **line_vector, list_path *current,
		char *program_name, int counter, int *status)
		{
	int n;
	if (_strcmp(line_vector[0], "exit") == 0)
	{
		if(line_vector[1] == NULL)
		{
			free(line);
			free_list(current);
			free_vector(line_vector);
			exit(*status);/*TODO status*/
		}
		else if(line_vector[1] != NULL )
		{
			if(_strlen(line_vector[1]) <= 9)
			{
				n = _atoi(line_vector[1]);
				if(n != -1)
				{
					free(line);
					free_list(current);
					free_vector(line_vector);
					exit(n);
				}
				else
				{
					*status = EXIT_ERROR;
					print_error(program_name, counter, line_vector[1], EXIT_ERROR);
				}
			}
			else
			{
				*status = EXIT_ERROR;
				print_error(program_name, counter, line_vector[1], EXIT_ERROR);
			}
			
		}
	}
}
int _atoi(char *s)
{
	unsigned int n, i;
	char positive;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (!((s[i] >= '0') && (s[i] <= '9')))
		{
			return(-1);
		}
		if (((s[i] >= '0') && (s[i] <= '9')))
		{
			n = (n * 10) + (s[i] - '0');
		}
		else if (s[i] == '+')
			positive++;

		i++;
	}

return (n);
}



void execute_command(char *path, char **av, char **env, int *status)
{
	pid_t pid;

	pid = fork();
	if (pid == ERROR)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(path, av, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		
		waitpid(pid, status, WUNTRACED);
		*status  = WEXITSTATUS(*status);
	}
}


void free_vector(char** argv) {
    char** curr;
	if (argv == NULL) {
        return;  
    }

    curr = argv;
    while (*curr != NULL) {
        free(*curr);
        curr++;
    }

    free(argv);
}

char *check_access(char *line_av_1, list_path *current)
{
	char *full_path;
	int found = 0, len;

	if (current == NULL)
		return (NULL);
	while (current)
	{
		len = _strlen(current->path) + _strlen(line_av_1) + 2; /* to calculate the length of the full path*/
		if (len > 1024)
		{
			write(STDERR_FILENO, "ERROR: Path too long\n", 21);
			continue;
		}
		full_path = (char *)malloc(len * sizeof(char));
		_strcpy(full_path,current->path);
		_strcat(full_path, "/");
		_strcat(full_path, line_av_1);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			break;
		}
		else
			free(full_path);

		current = current->next;
	}
	if (found)
		return (full_path);

	else
			return (NULL);
}
