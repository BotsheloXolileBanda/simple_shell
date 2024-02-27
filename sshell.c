#include "shell.h"

/**
  * main - Implements a shell.
  *
  * @ac: Argument counter.
  * @av: Array of argument strings.
  * Return: 0 on success.
  */
int main(int ac, char **av)
{
	int termconec, wstatus;
	pid_t to_fork;
	ssize_t chars;
	char *bufptr = NULL;
	size_t len = 0;
	char *args[3];
	(void) ac;
	(void) av;

	signal(SIGINT, SIG_IGN);
	if ((termconec = isatty(0)) == 1)
	{
		printf("[$] ");
	}

	while ((chars = getline(&bufptr, &len, stdin)) != -1)
	{
		to_fork = fork();

		if (to_fork == -1)
		{
			free(bufptr);
			errorfunc("Fork failed");
		}
		else if (to_fork == 0)
		{
			args[0] = strtok(bufptr, " \t\r\n\f\v");
			args[1] = strtok(NULL, " \t\r\n\f\v");
			args[2] = NULL;
			if ((execve(args[0], args, environ)) == -1)
			{
				free(bufptr);
				errorfunc(av[0]);
			}
		}
		wait(&wstatus);
		if ((termconec = isatty(0)) == 1)
		{
			printf("[$] ");
		}
	}
	if (chars == -1)
	{
		free(bufptr);
		exit(EXIT_SUCCESS);
	}
	free(bufptr);
	return (0);
}
