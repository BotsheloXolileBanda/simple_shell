#include "shell.h"
/**
  * countwords - Counts words in a string.
  *
  * @string: The string.
  * @delim: The delimiters.
  * Return: 0 or words.
  */
int countwords(char *string, char *delim)
{
	char *token;
	int r;
	char *dupdstr;

	if (!string || !delim)
	{
		return (0);
	}
	else
	{
		dupdstr = strdup(string);

		r = 0;

		token = strtok(dupdstr, delim);

		while (token != NULL)
		{
			r++;
			token = strtok(NULL, delim);
		}

		dupdstr = freenull(dupdstr);
		return (r);
	}
}
/**
  * separator - Tokenizes a string into an array.
  *
  * @string: The string.
  * @delim: The delimiter.
  * @cnt: Number of words to expect.
  * Return: AN array of words or NULL.
  */
char **separator(char *string, char *delim, int cnt)
{
	char **strings;
	char *dupdstr;
	char *token;
	int r = 0;

	if (!string || !delim || !cnt)
	{
		return (NULL);
	}
	else
	{
		dupdstr = strdup(string);

		strings = malloc(sizeof(char *) * (cnt));

		if (!strings)
		{
			dupdstr = freenull(dupdstr);
			return (NULL);
		}
		else
		{
			token = strtok(dupdstr, delim);

			while (token != NULL)
			{
				strings[r] = strdup(token);
				r++;
				token = strtok(NULL, delim);
			}
			dupdstr = freenull(dupdstr);
			return (strings);
		}
	}
}
char **build(char **arr, int cnt, char *name)
{
	int r, x, y, z, len;

	char **newarr;
	char *namedup;

	if (!arr || !cnt || !name)
	{
		return (NULL);
	}
	else
	{
		namedup = strdup(name);
		newarr = malloc(sizeof(char *) * cnt);

		if (!newarr)
		{
		namedup = freenull(namedup);
		return (NULL);
		}
		else
		{
			len = strlen(namedup) + 2;

			for (r = 0; r < cnt; r++)
			{
				newarr[r] = malloc(sizeof(char) * ((len) + strlen(arr[r])));
			}
			for (x = 0; x < cnt; x++)
			{
				strcpy(newarr[x], arr[x]);
			}
			for (y = 0; y < cnt; y++)
			{
				strcat(newarr[y], "/");
			}
			for (z = 0; z < cnt; z++)
			{
				strcat(newarr[z], namedup);
			}
			namedup = freenull(namedup);
			arr = freefunc(arr, cnt);
			return (newarr);
		}
	}
}
/**
  * check - Checks exitance of file.
  *
  * @built: Different files.
  * @cnt: Number of files.
  * Return: ) on success, -1 otherwise.
  */
int check(char **built, int cnt)
{
	struct stat st;
	int r, flag;

	flag = 0;

	r = 0;

	if (!built || !cnt)
	{
		return (0);
	}
	else
	{
		while (r < cnt)
		{
			if (stat(built[r], &st) == 0)
			{
				flag = 1;
				break;
			}
			r++;
		}

		if (flag)
		{
			return (r);
		}
		else
		{
			return (0);
		}
	}
}
/**
  * checkexis - Checks if a file exits.
  *
  * @string: Path variable.
  * @delim: THe :.
  * name: The inputted file.
  * Return: 0 on success, -1 otherwise.
  */
char *checkexis(char *string, char *delim, char *name)
{
	int cnt, answer;
	char *stringdup;
	char *namedup;
	char **arr;
	char **built;
	char *found;

	if (!string || !delim || !name)
	{
		return (NULL);
	}
	else
	{
		stringdup = strdup(string);

		namedup = strdup(name);

		cnt = countwords(stringdup, delim);

		if (!cnt)
		{
			stringdup = freenull(stringdup);
			namedup = freenull(namedup);
			return (NULL);
		}
		else
		{
			arr = separator(stringdup, delim, cnt);

			if (!arr)
			{
				stringdup = freenull(stringdup);
				namedup = freenull(namedup);
				return (NULL);
			}
			else
			{
				built = build(arr, cnt, namedup);

				if (!built)
				{
					namedup = freenull(namedup);
					stringdup = freenull(stringdup);
					arr = freefunc(arr, cnt);
					return (NULL);
				}
				else
				{
					answer = check(built, cnt);

					if (answer)
					{
						found = strdup(built[answer]);
						stringdup = freenull(stringdup);
						namedup = freenull(namedup);
						built = freefunc(built, cnt);
						return (found);
					}
					else
					{
						stringdup = freenull(stringdup);
						namedup = freenull(namedup);
						built = freefunc(built, cnt);
						return (NULL);
					}
				}
			}
		}
	}
}
