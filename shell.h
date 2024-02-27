#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

extern char **environ;
void errorfunc(char *error_m);
void catchsig(int signum);
int countwords(char *string, char *delim);
char **separator(char *string, char *delim, int cnt);
char **built(char **arr, int cnt, char *name);
int checkexis(char *string, char *delim, char *name);
int check(char **built, int cnt);
void freefunc(char **arr, int cnt);
#endif
