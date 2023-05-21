#include "shell.h"

/*
    betty
*/
void check_file(char *file)
{
    struct stat fileStat;
    
    
    if (stat(file, &fileStat) == 0) {
        printf("File Size: %ld bytes\n", fileStat.st_size);
        printf("File Permissions: %o\n", fileStat.st_mode);
        printf("File Inode: %lu\n", fileStat.st_ino);
        

    
        if (S_ISREG(fileStat.st_mode)) {
            printf("File is a regular file.\n");
        }

        if (S_ISDIR(fileStat.st_mode)) {
            printf("File is a directory.\n");
        }
    } else {
        printf("Failed to retrieve file information.\n");
    }
}

char *get_command_from_file(char *file)
{
    char* line;
    line = _strdup(file);
    
	return (line);
}
