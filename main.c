#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr );

/*
 TODO: make a function to check that each column contains the digits 1 through 9
 TODO: A thread to check that each row contains the digits 1 through 9
 TODO: Nine threads to check that each of the 3*3 subgrids contains the digits 1 through 9 
*/

int board[9][9] = {6,2,4,5,3,9,1,8,7,
		   5,1,9,7,2,8,6,3,4,
		   8,3,7,6,1,4,2,9,5,
		   1,4,3,8,6,5,7,2,9,
		   9,5,8,2,4,7,3,6,1,
		   7,6,2,3,9,1,4,5,8,
		   3,7,1,9,5,6,8,4,2,
		   4,9,6,1,8,2,5,7,3,
		   2,8,5,4,7,3,9,1,6}; 

main()
{
     int checkRowVal = check_row(board);
     exit(0);
}

void *print_message_function(void *ptr)
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}

int cgit sheck_row(int board[9][9])
{


int i=0;
int j=0;
int isValid[9] = {0,0,0,0,0,0,0,0,0};
int overallResult = 1;

	for (i = 0; i<9; i++){
		for (j=0; j<9; j++){
			int underExam = board[i][j];
			if (isValid[underExam-1] == 0){
				isValid[underExam-1] = 1;
			} else {
				/*row is now invalid*/
				overallResult = 0;
			}
			
		}
		
		printf("row complete \n");

		for (int k=0; k<9; k++){
			printf("%d ", isValid[k]);
			isValid[k] = 0;
		}

		printf("\n");
	}

printf ("Overall Result is %d\n", overallResult);

return overallResult;
}


/*need function to go through rows
need function to go through columns
need functions to through each box
*/
