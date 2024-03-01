#include "simple_shell.h"
/**
 * main - starting point
 * @ac: total connection for all user
 * @argv: array point to the object character
 * Return: 0 (pass)
 */

int main(int ac, char **argv)
{
char *prompt = "(simple_shell) $";
char *lineptr;
size_t n = 0;
printf("%s", prompt);
getline(&lineptr, &n, stdin);
printf("%s\n", lineptr);
free(lineptr);
return (0);
}

