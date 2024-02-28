#include "shell.h"

/**
  * _getenv - Implementation of getenv function.
  *
  * @envvar: Variable to get.
  * Return: The variable contents or NULL.
  */
char *_getenv(char *envvar)
{
	int r, p;

	int sign = 0;

	if (!envvar)
	{
		return (NULL);
	}
	else
	{
		for (r = 0; environ[r] != NULL; r++)
		{
			if (checkenv(environ[r], envvar, '=') == 1)
			{
				sign = 1;
				break;
			}
		}
		if (sign)
		{
			p = getinsidevar(environ[r], '=');
			return (&environ[r][p + 1]);
		}
		else
		{
			return (NULL);
		}
	}
}
