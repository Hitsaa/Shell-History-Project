#ifndef MACROS_H
#define MACROS_H

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LINE 100 
#define BUFFER_SIZE 80	

#define buffer "\n\Shell History:\n"
char history[50][BUFFER_SIZE]; 
int count = 0;

//function to display the history of commands
void displayHistory()

//Fuction to get the command from shell, tokenize it and set the args parameter
int formatCommand(char inputBuffer[], char *args[],int *flag)

#endif
