#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/dir.h>
#include <sys/wait.h>
#include <unistd.h>

int search(char *file, char *dir)
{
    DIR *dirptr = opendir(dir);
    struct dirent *entry = readdir(dirptr);
    int status;
    while (entry = readdir(dirptr))
    {
        if ( strlen(entry->d_name) == strlen(file) && (strcmp(entry->d_name, file) == 0))
        {    
            printf("File Found\n");
            return 0; /* return success */
        }
        // check if directory
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0)
        {
            int child = fork();
            if(child == 0)
            {
		char path[1024];

                strcpy(path,dir);
                strcat(path,"/");
                strcat(path,entry->d_name);
                
		        dir = path;		
                // in child process
                dirptr = opendir(path);
            }
            else 
            {
                // parent
                wait(&status);
            }
        }
    }
    return 1; /* return failure */
}

int main(int argc, char *argv[])
{
    search(argv[1],argv[2]);
    return 0;
}
