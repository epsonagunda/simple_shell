#include <stdio.h>
#include "simple_shell.h"
int main(void)
{
// array to store command	
char command[100];
// argument vector
char *argv[4];
// eviroment vector for execve
char *envp[] = {NULL};
int status;
whele (1)
{
printf("> ");
fgets(command, sizeof(command), stdin);
// remove newline
command[strcspn(command, "\n")] = 0;
if (strchr(command, ' ') == NULL)
{
argv[0] = command;
argv[1] = NULL;
status = execve(command, argv, envp);
if (status == -1)
{
perror(command);
}
}
else
{
printf("\%s: no command\n",command);
}
}
return (0);
}
