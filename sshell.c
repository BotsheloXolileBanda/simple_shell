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
	struct stat st;
	int termconec, wstatus;
	pid_t to_fork;
	char *bufcp;
	ssize_t chars;
	char *bufptr = NULL;
	size_t len = 0;
	char *args[3];
	(void) ac;

	signal(SIGINT, SIG_IGN);
	if ((termconec = isatty(0)) == 1)
	{
		printf("[$] ");
	}

	while ((chars = getline(&bufptr, &len, stdin)) != -1)
	{
		bufcp = strdup(bufptr);
		if (bufcp[0] == 3)
		{
			bufcp = freenull(bufcp);
			printf("[$] ");
			continue;
		}
		else if (stat((strtok(bufcp, " \t\r\n\f\v")), &st) == 0)
		{
			to_fork = fork();

			if (to_fork == -1)
			{
				bufcp = freenull(bufcp);
				bufptr = freenull(bufptr);
				errorfunc("Fork failed");
			}
			else if (to_fork == 0)
			{
				args[0] = strtok(bufptr, " \t\r\n\f\v");
				args[1] = strtok(NULL, " \t\r\n\f\v");
				args[2] = NULL;
				if ((execve(args[0], args, environ)) == -1)
				{
					bufcp = freenull(bufcp);
					bufptr = freenull(bufptr);
					perror(av[0]);
					continue;
				}
			}
			else
			{
				bufcp = freenull(bufcp);
				bufptr = freenull(bufptr);
				wait(&wstatus);
				if ((termconec = isatty(0)) == 1)
				{
					printf("[$] ");
			
				}
			}
		}
		else
		{
			bufcp = freenull(bufcp);
			perror(av[0]);
			printf("[$] ");
			continue;
		}
	}
	if (chars == -1)
	{
		freenull(bufcp);
		freenull(bufptr);
		exit(EXIT_SUCCESS);
	}
	bufcp = freenull(bufcp);
	bufptr = freenull(bufptr);
	return (0);
}
