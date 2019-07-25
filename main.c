#include<stdio.h>
#include<macros.h>

int main(void)
{
    char inputBuffer[MAX_LINE]; /* buffer to hold the input command */
    int flag; // equals 1 if a command is followed by "&"
    char *args[MAX_LINE/2 + 1];/* max arguments */
    int should_run =1;
    
    pid_t pid,tpid;
    int i;
   
    
    while (should_run) //infinite loop for shell prompt
    {            
        flag = 0; //flag =0 by default
        printf("New_Shell>>$");
        fflush(stdout);
        if(-1!=formatCommand(inputBuffer,args,&flag)) // get next command  
	{
		pid = fork();
        
        	if (pid < 0)//if pid is less than 0, forking fails
        	{
            
            		printf("Fork failed.\n");
            		exit (1);
        	}
        
       		 else if (pid == 0)//if pid ==0
        	{
            
           	 	//command not executed
            		if (execvp(args[0], args) == -1)
           	 	{	
		
                		printf("Error executing command\n");
            		}
       		 }
           
        	else
        	{
            		i++;
           	 	if (flag == 0)
           		 {
                		i++;
      //          		wait(NULL);
           		 }
        	}
   	 }
     }
}
