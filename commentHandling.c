#include "shell.h"

void handle_comments(char *line)
{
    int len = strlen(line);
    int i = 0;
    int strating = 0;

    for (i = 0; i < len; i++)
    {
        if (line[i] == ' ')
        {
            strating = 0;
        }
        else if (line[i] == '#')
        {
            if (!strating)
            {
                line[i] = '\0';
                break;
            }
        }

        else
        {
            strating = 1;
        }
    }
}
