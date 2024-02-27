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

	if (!str || !delim)
	{
		return (0);
	}
	else
	{
		dupdstr = strdup(string);

		r = 0;

		token = strtok(dupstr, delim);

		while (token != NULL)
		{
			r++;
			token = strtok(NULL, delim);
		}

		free(dupstr);
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
			free(dupdstr);
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
			free(dupdstr);
			return (strings);
		}
	}
}
char **build(char **arr, int cnt, char *name)
{
	int r, x, y, z, len;

	char **newarr;
	char *namedup;

	if (!strings || !cnt || !name)
	{
		return (NULL);
	}
	else
	{
		namedup = strdup(name);
		newarr = malloc(sizeof(char *) * cnt);

		if (!newarr)
		{
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
			free(namedup);
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
	int r;

	struct stat st;

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
			return (0);
		}
		else
		{
			return (-1);
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
int checkexis(char *string, char *delim, char *name)
{
	int r, cnt, answer;
	char *stringdup;
	char *namedup;
	char **arr;
	char **built;
	int flag = 0;

	struct stat st;

	r = 0;

	if (!string || !delim || !name)
	{
		return (-1);
	}
	else
	{
		stringdup = strdup(string);

		namedup = strdup(name);

		cnt = countwords(stringdup, delim);

		if (!cnt)
		{
			free(stringdup);
			free(namedup);
			return (-1);
		}
		else
		{
			arr = tokenize(stringdup, delim, cnt);

			if (!arr)
			{
				free(stringdup);
				free(namedup);
				return (-1);
			}
			else
			{
				built = build(arr, cnt, namedup);

				if (!built)
				{
					free(namedup);
					free(stringdup);
					freefunc(arr, cnt);
					return (-1);
				}
				else
				{
					answer = check(built, cnt);

					if (answer == 0)
					{
						free(stringdup);
						free(namedup);
						freefunc(arr, cnt);
						freefunc(arr, cnt);
						return (0);
					}
					else
					{
						free(stringdup);
						free(namedup);
						freefunc(arr, cnt);
						freefunc(built, cnt);
						return (-1);
					}
				}
			}
		}
	}
}
