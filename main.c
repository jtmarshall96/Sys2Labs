#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr );

/*
 TODO: make a function to check that each column contains the digits 1 through 9
 TODO: A thread to check that each row contains the digits 1 through 9
 TODO: Nine threads to check that each of the 3*3 subgrids contains the digits 1 through 9 
*/

int board[9][9]; 

main()
{
    
     exit(0);
}

void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}
