#include "shell.h"

/**
  * error_func - A function handling errors.
  *
  * @error_m: Supplimentary error message.
  * Return: No value.
  */
void errorfunc(char *error_m)
{
	perror(error_m);
	exit(EXIT_FAILURE);
}
