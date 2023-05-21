#include "shell.h"

void handle_comments(char *line)
{
    int len = strlen(line);
    int x = 0;
    int _strating = 0;

    for (x = 0; x < len; x++)
    {
        if (line[x] == ' ')
        {
            _strating = 0;
        }
        else if (line[x] == '#')
        {
            if (!_strating)
            {
                line[x] = '\0';
                break;
            }
        }
        /*
        * this else handles the mid
        */
        else
        {
            _strating = 1;
        }
    }
}
/*
 *
 * didn't handle the middle # of a word
 *
 */

/*
void handle_comments(char *line)
 {
     int x;
     int hash = -1;
     int len = strlen(line);

     Find the the first '#' character
     for (x = 0; x < len; x++)
     {
         if (line[x] == '#')
         {
            hash = x;
             break;
         }
    }

     Remove what's after the '#' character
     if (hash != -1)
    {
         line[hash] = '\0';
     }
  }
*/
