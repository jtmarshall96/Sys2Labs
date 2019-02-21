/*
*
* Authors: Mansa thada, Jacob Marshall
*	Systems 2: Operating systems 
*	Lab 2
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



#define TRUE 1;
#define FALSE 0;



int check_collumn(int board[9][9]);

int check_row(int board[9]);

int check_three_by_three(int *board[9][9], int rowStart, int rowEnd, int colStart, int colEnd);


   struct arg_struct{
		int gridBoard[9][9];
		int rowStart;
		int rowEnd;	
		int colStart;
		int colEnd;
	} ;




int main()
{
	char digit;
	int x,y,board[9][9], ret_val,temp,grid_val;
	FILE *in_file;
	int argsArr[5]= {board, 0,2,0,2};

	
       struct arg_struct *args = malloc(sizeof(struct arg_struct));

	in_file = fopen("sudoku.txt","r");

	
		
	for(x=0;x<9;x++){
		for(y =0;y<9 && (digit =fgetc(in_file)) != EOF ;y++){
			
			if(digit == '\n'){ digit = fgetc(in_file);}
			board[x][y] = atoi(&(digit));
			(*args).gridBoard[x][y] = atoi(&(digit)); 	
		}		
	}
	
	
	(*args).rowStart = 0;
	(*args).rowEnd = 2;
	(*args).colStart = 0;
	(*args).colEnd = 2;

	
	
	
	pthread_t block1, block2, block3, block4, block5, block6, block7, block8, block9, check_blocks_thread;
	pthread_t row1, row2, row3, row4, row5, row6, row7, row8, row9,check_columns_thread;

	pthread_create(&block1,NULL,&check_three_by_three, (void *)args);


	
	ret_val = 2;
	/*create the thread for rows*/
	pthread_create(&row1,NULL,&check_row,(void *)board[0]);
	pthread_create(&row2,NULL,&check_row,(void *)board[1]);
	pthread_create(&row3,NULL,&check_row,(void *)board[2]);
	pthread_create(&row4,NULL,&check_row,(void *)board[3]);
	pthread_create(&row5,NULL,&check_row,(void *)board[4]);
	pthread_create(&row6,NULL,&check_row,(void *)board[5]);
	pthread_create(&row7,NULL,&check_row,(void *)board[6]);
	pthread_create(&row8,NULL,&check_row,(void *)board[7]);
	pthread_create(&row9,NULL,&check_row,(void *)board[8]);
	/*create thread for checking columns*/
	pthread_create(&check_columns_thread,NULL,&check_collumn,(void *)board);
	
	/*get the return value of the thread*/
	pthread_join(row1,&ret_val);
	if(ret_val){
		pthread_join(row2,&ret_val);
			if(ret_val){pthread_join(row3,&ret_val);
				if(ret_val){pthread_join(row4,&ret_val);
					if(ret_val){pthread_join(row5,&ret_val);
						if(ret_val){pthread_join(row6,&ret_val);
							if(ret_val){pthread_join(row7,&ret_val);
								if(ret_val){pthread_join(row8,&ret_val);
									if(ret_val){pthread_join(row9,&ret_val);}
								}
							}	
						}
				}	}
		}	}
	
	
	pthread_join(check_columns_thread,&temp);
	pthread_join(block1,&grid_val);
	printf("executed check 3 by 3: %d\n",grid_val);

	
	
	
	printf("%d\n",(ret_val && temp));
	return (ret_val && temp);
	

	
}



int check_row(int board[9])
{


int i=0;
int j=0;
int k=0;
int isValid[9] = {0,0,0,0,0,0,0,0,0};
int overallResult = 1;
int underExam;
		for (j=0; j<9; j++){
			underExam = board[j];
			if (isValid[underExam-1] == 0){
				isValid[underExam-1] = 1;
			} else {
				/*row is now invalid*/
				overallResult = 0;
			}
		
		}


printf ("Row Result is %d\n", overallResult);

return overallResult;
}

int check_collumn(int board[9][9]){

	int row,collumn,number,i,overall;
	int nums[9];
	overall = TRUE;
	for(row = 0; row<9;row++){
		/*re initialize the valid numbers array*/
		for(i = 0; i<9;i++){
		nums[i] = FALSE;
		}

		for(collumn =0;collumn<9;collumn++){
			number = board[collumn][row];
			if(nums[number-1]){
				overall= FALSE;
			}
			else{
				nums[number-1] = TRUE;
			}	
		}
		printf ("cOLLUMN Result is %d\n", overall);
	}

	
	return overall;

}

int check_three_by_three(int *board[9][9], int rowStart, int rowEnd, int colStart, int colEnd)
{

	printf("%d\n", rowStart);
	printf(" board: %d\n", board[0][0]);

int i=0;
int j=0;
int isValid[9] = {0,0,0,0,0,0,0,0,0};
int overallResult = 1;
int gridResult = 1;

	for (i = rowStart; i<=rowEnd; i++){
		for (j=colStart; j<=colEnd; j++){
			int underExam = board[i][j];
			if (isValid[underExam-1] == 0){
				isValid[underExam-1] = 1;
			}
		}
	}

	for (int m=0; m<9; m++){
		if (isValid[m] != 1){
			gridResult = 0;
		}
	}

printf ("GRID Overall Result is %d\n", gridResult);

return gridResult;
}

