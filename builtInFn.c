#include "shell.h"

void print_env(int *status)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
		fflush(stdout);
	}
	*status = 0;/*success*/
}

char *get_status(int n)
{
	char *status;
	status = num_to_char(n);
	return status;

}

char *get_process_id()
{
	char *ppid_s;
	pid_t pid = getpid();

	ppid_s = num_to_char(pid);

	return (ppid_s);
}

int is_built_in(char * line, char **line_vector ,list_path *current, char *program_name , int counter, int *status)
{
	int i, n = -1;
	char *built_in[] = {"env", "exit"};

	for (i = 0; i < 2; i++)
	{
		if (_strcmp(built_in[i], line_vector[0]) == 0)
		{
			n = i;
			break;
		}
	}
	if(n == -1)
		return (n);
	
	switch (n) {
    case 0:
        print_env(status);
        break;
    case 1:
        is_exit(line, line_vector, current, program_name, counter, status);
        break;
    default:
        return (-1);
        break;
	}
	return(0);
}

char *num_to_char(int num)
{
	/*count digits*/
	int c = 0, tmp = num;
	char *cp_num;
	if (num == 0)
	{
		c = 1;
	}
	else
	{
		while (tmp != 0)
		{
			tmp /= 10;
			c++;
		}
	}

	cp_num = malloc(sizeof(char) * (c + 1));
	if (!cp_num)
	{
		perror("malloc");
		return (NULL);
	}
	cp_num[c] = '\0';
	while (c != 0)
	{
		c--;
		cp_num[c] = '0' + num % 10;
		num /= 10;
	}

	return (cp_num);
}
