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
	int r;
	int flag = 0;
	struct stat st;
	int termconec, wstatus;
	pid_t to_fork;
	char *bufcp;
	ssize_t chars;
	char *bufptr = NULL;
	size_t len = 0;
	char *args[4];
	char *path;
	char *pathcp;
	(void) ac;

	signal(SIGINT, SIG_IGN);
	if ((termconec = isatty(0)) == 1)
	{
		printf("[$] ");
	}

	while ((chars = getline(&bufptr, &len, stdin)) != -1)
	{
		flag = 1;
		path = getenv("PATH");
		pathcp = strdup(path);
		bufcp = strdup(bufptr);
		if (stat((strtok(bufcp, " \t\r\n\f\v")), &st) == 0)
		{
			to_fork = fork();

			if (to_fork == -1)
			{
				pathcp = freenull(pathcp);
				bufcp = freenull(bufcp);
				bufptr = freenull(bufptr);
				errorfunc("Fork failed");
			}
			else if (to_fork == 0)
			{
				args[0] = strtok(bufptr, " \t\r\n\f\v");
				args[1] = strtok(NULL, " \t\r\n\f\v");
				args[2] = strtok(NULL, " \t\r\n\f\v");
				args[3] = NULL;
				if ((execve(args[0], args, environ)) == -1)
				{
					pathcp = freenull(pathcp);
					bufcp = freenull(bufcp);
					bufptr = freenull(bufptr);
					perror(av[0]);
					continue;
				}
			}
			else
			{
				pathcp = freenull(pathcp);
				bufcp = freenull(bufcp);
				bufptr = freenull(bufptr);
				wait(&wstatus);
				if ((termconec = isatty(0)) == 1)
				{
					printf("[$] ");
			
				}
			}
		}
		else if ((strcmp(bufcp, "env")) == 0)
		{
			r = 0;

			while (environ[r])
			{
				printf("%s\n", environ[r]);
				r++;
			}
		}
		else if ((strcmp(bufcp, "exit")) == 0)
		{
			break;
		}
		else
		{
			pathcp = freenull(pathcp);
			bufcp = freenull(bufcp);
			bufptr = freenull(bufptr);
			perror(av[0]);
			printf("[$] ");
			continue;
		}
	}
	if (chars == -1)
	{
		if (flag)
		{
			pathcp = freenull(pathcp);
			bufcp = freenull(bufcp);
			bufptr = freenull(bufptr);
			exit(EXIT_SUCCESS);
		}
		else
		{
			bufptr = freenull(bufptr);
			exit(EXIT_SUCCESS);
		}
	}
	pathcp = freenull(pathcp);
	bufcp = freenull(bufcp);
	bufptr = freenull(bufptr);
	return (0);
}
