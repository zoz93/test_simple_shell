#include "shell.h"

void execute_command_with_waitpid(char *path, char **av, char **env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        execve(path, av, env);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else {
        waitpid(pid, &status, 0);
    }
}
void handle_semicolons(char *line)
{
    char *token;
    char *args[100];
    int i;
    token = strtok(line, ";"); 
    while (token != NULL)
    {
        handle_comments(token);
        i = 0;
        args[0] = strtok(token, " ");
        i = 0;
        while (args[i] != NULL && i < 99)
        {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (i > 0) {
            execute_command_with_waitpid(args[0], args, NULL);
        }

        token = strtok(NULL, ";"); 
    }
}
