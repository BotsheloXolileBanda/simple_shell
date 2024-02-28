#include "shell.h"

/**
  * errorfunc - A function handling errors.
  *
  * @error_m: Supplimentary error message.
  * Return: No value.
  */
void errorfunc(char *error_m)
{
	perror(error_m);
	exit(EXIT_FAILURE);
}
/**
  * freefunc -Frees a char**.
  * @arr: The variable.
  * @cnt: Number of elemnts.
  * Return: No value.
  */
char **freefunc(char **arr, int cnt)
{
	int r;

	r = 0;

	if (!arr || !cnt)
	{
		return (NULL);
	}
	else
	{
		while (r < cnt)
		{
			free(arr[r]);
			arr[r] = NULL;
			r++;
		}
		free(arr);
		arr = NULL;
		return (NULL);
	}
}
/**
  * freenull - Frees a pointer.
  *
  * @ptr: Ptr to free.
  * Return: NULL.
  */
char *freenull(char *ptr)
{
	if (ptr == NULL)
	{
		return (ptr);
	}
	else
	{
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
}
