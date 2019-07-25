#include <stdio.h>
#include <stdlib.h>
#include <macros.h>
#include <string.h>

//function to display the history of commands
void displayHistory()
{    
    printf("Shell history:\n");
    
    int i;
    int j = 0;
    int histCount = count;
    
    //loop for iterating through commands
    for (i = 0; i<50;i++)
    {
        printf("%d.  ", histCount);
        while (history[i][j] != '\n' && history[i][j] != '\0')
        {	
		//printing command character by character
            printf("%c", history[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        histCount--;
        if (histCount ==  0)
            break;
    }
    printf("\n");
} 

//Fuction to get the command from shell, tokenize it and set the args parameter

int formatCommand(char inputBuffer[], char *args[],int *flag)
{
   	int length; // # of chars in command line
    	int i;     // loop index for inputBuffer
    	int start;  // index of beginning of next command
    	int ct = 0; // index of where to place the next parameter into args[]
    	int hist;
    	//read user input on command line and checking whether the command is !! or !n

 	length = read(STDIN_FILENO, inputBuffer, MAX_LINE);	
    start = -1;
    if (length == 0)
        exit(0);   //end of command
    if (length < 0)
    {
        printf("Command not read\n");
        exit(-1);  //terminate
    }
    
   //examine each character
    for (i=0;i<length;i++)
    {
        switch (inputBuffer[i])
        {
            case ' ':
            case '\t' :               // to seperate arguments
                if(start != -1)	
                {
                    args[ct] = &inputBuffer[start]; 
                    ct++;
                }
                inputBuffer[i] = '\0'; 
                start = -1;
                break;
                
            case '\n':     
                if (start != -1)
                {
                    args[ct] = &inputBuffer[start];
                    ct++;
                }
                inputBuffer[i] = '\0';
                args[ct] = NULL; 
                break;
                
            default :           
                if (start == -1)
                    start = i;
                if (inputBuffer[i] == '&')
                {
                    *flag  = 1; //this flag is the differentiate whether the child process is invoked in background
                    inputBuffer[i] = '\0';
                }
        }
    }
    
    args[ct] = NULL; //if the input line was > 100

if(strcmp(args[0],"history")==0)	//when we type on the command line, "history"(not quotes) then this command will store in args[0]. Now if we compare args[0] and "history" using strcmp function then it will return 0. so when we type history and if count > 0 then history will be displayed otherwise not. 
        {		
               if(count>0)
		{
		
                displayHistory();
		}
		else
		{
		printf("\nNo Commands in the history\n");
		}
		return -1;
        }

	else if (args[0][0]-'!' ==0)
	{	int x = args[0][1]- '0'; 
		int z = args[0][2]- '0'; 
		
		if(x>count) //second letter check
		{
		printf("\nNo Such Command in the history\n");
		strcpy(inputBuffer,"Wrong command");
		} 
		else if (z!=-48) //third letter check
		{
		printf("\nNo Such Command in the history. Enter <=!9 (buffer size is 10 along with current command)\n");
		strcpy(inputBuffer,"Wrong command");
		}
		else
		{

			if(x==-15)//Checking for '!!',ascii value of '!' is 33.
			{	 strcpy(inputBuffer,history[0]);  // this will be your 10 th(last) command
			}
			else if(x==0) //Checking for '!0'
			{	 printf("Enter proper command");
				strcpy(inputBuffer,"Wrong command");
			}
			
			else if(x>=1) //Checking for '!n', n >=1
			{
				strcpy(inputBuffer,history[count-x]);

			}
			
		}
	}
 for (i = 49;i>0; i--) 
       	strcpy(history[i], history[i-1]);
    
    strcpy(history[0],inputBuffer); //Updating the history array with input buffer
    count++;
	if(count>10)
	{ count=10;
	}
}
