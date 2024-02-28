#include "shell.h"

/**
  * checkenv - Checks if inputted string is a evnv var.
  *
  * @str1: Env string to check.
  * @str2: Variable to get.
  * @sym: The symbol to stop at in envvar.
  * Return: 1 if found, 0 if not.
  */
int checkenv(char *str1, char *str2, char sym)
{
	int r, sign;

	sign = 1;

	for (r = 0; str1[r] != sym; r++)
	{
		if (str1[r] != str2[r])
		{
			sign = 0;
			break;
		}
	}

	if (sign)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/**
  * getinsidevar - Gets an environment var.
  *
  * @str: The string to get.
  * @sym: Terminating symbol.
  * Return: Point after symbol.
  */
int getinsidevar(char *str, char sym)
{
	int r, x;

	for (x = 0; str[x] != sym; x++)
	{
	}
	r = x;

	return (r);
}
