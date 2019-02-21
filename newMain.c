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


   struct arg_struct{
		int gridBoard[9][9];
		int rowStart;
		int rowEnd;	
		int colStart;
		int colEnd;
	};




int check_collumn(int board[9][9]);

int check_row(int board[9]);

int check_three_by_three( struct arg_struct *args);




int main(int argc, char *argv[])
{
	char digit;
	int x,y,board[9][9], ret_val,temp,grid_val;
	FILE *in_file;
	int argsArr[5]= {board, 0,2,0,2};
	char *filename = argv[argc-1];
	
	struct arg_struct *args = (struct arg_struct*)malloc(sizeof(struct arg_struct));

	in_file = fopen(filename,"r");

	
		
	for(x=0;x<9;x++){
		for(y =0;y<9 && (digit =fgetc(in_file)) != EOF ;y++){
			
			if(digit == '\n'){ digit = fgetc(in_file);}
			board[x][y] = atoi(&(digit));
			(*args).gridBoard[x][y] = atoi(&(digit)); 	
		}		
	}
		
	pthread_t block1, block2, block3, block4, block5, block6, block7, block8, block9;
	pthread_t row1, row2, row3, row4, row5, row6, row7, row8, row9;
	pthread_t check_columns_thread;
	
	ret_val = 2;

	/*create the threads for rows*/
	pthread_create(&row1,NULL,&check_row,(void *)board[0]);
	pthread_create(&row2,NULL,&check_row,(void *)board[1]);
	pthread_create(&row3,NULL,&check_row,(void *)board[2]);
	pthread_create(&row4,NULL,&check_row,(void *)board[3]);
	pthread_create(&row5,NULL,&check_row,(void *)board[4]);
	pthread_create(&row6,NULL,&check_row,(void *)board[5]);
	pthread_create(&row7,NULL,&check_row,(void *)board[6]);
	pthread_create(&row8,NULL,&check_row,(void *)board[7]);
	pthread_create(&row9,NULL,&check_row,(void *)board[8]);
	
	/*get the return value of the thread*/
	pthread_join(row1,&ret_val);
	if(ret_val){
		pthread_join(row2,&ret_val);
		if(ret_val){
			pthread_join(row3,&ret_val);
			if(ret_val){
				pthread_join(row4,&ret_val);
				if(ret_val){
					pthread_join(row5,&ret_val);
					if(ret_val){
						pthread_join(row6,&ret_val);
						if(ret_val){
							pthread_join(row7,&ret_val);
							if(ret_val){
								pthread_join(row8,&ret_val);
								if(ret_val){
									pthread_join(row9,&ret_val);
								}
							}
						}	
					}
				}
			}
		}
	}

	/*create thread, then join thread for checking columns*/
	pthread_create(&check_columns_thread,NULL,&check_collumn,(void *)board);
	pthread_join(check_columns_thread,&temp);
	
	/*create threads, then join threads for checking grids*/

	/*GRID 1: TOP LEFT*/
	(*args).rowStart = 0;
	(*args).rowEnd = 2;
	(*args).colStart = 0;
	(*args).colEnd = 2;
	pthread_create(&block1,NULL,&check_three_by_three, (void *)args);
	pthread_join(block1,&grid_val);
	
	if (grid_val){
		/*GRID 2: TOP MIDDLE*/
		(*args).rowStart = 0;
		(*args).rowEnd = 2;
		(*args).colStart = 3;
		(*args).colEnd = 5;
		pthread_create(&block2,NULL,&check_three_by_three, (void *)args);
		pthread_join(block2,&grid_val);
		if (grid_val){
			/*GRID 3: TOP RIGHT*/
			(*args).rowStart = 0;
			(*args).rowEnd = 2;
			(*args).colStart = 6;
			(*args).colEnd = 8;
			pthread_create(&block3,NULL,&check_three_by_three, (void *)args);
			pthread_join(block3,&grid_val);
			if (grid_val){
				/*GRID 4: MIDDLE LEFT*/
				(*args).rowStart = 3;
				(*args).rowEnd = 5;
				(*args).colStart = 0;
				(*args).colEnd = 2;
				pthread_create(&block4,NULL,&check_three_by_three, (void *)args);
				pthread_join(block4,&grid_val);
				if (grid_val){
					/*GRID 5: MIDDLE MIDDLE*/
					(*args).rowStart = 3;
					(*args).rowEnd = 5;
					(*args).colStart = 3;
					(*args).colEnd = 5;
					pthread_create(&block5,NULL,&check_three_by_three, (void *)args);
					pthread_join(block5,&grid_val);
					if (grid_val){
						/*GRID 6: MIDDLE LEFT*/
						(*args).rowStart = 3;
						(*args).rowEnd = 5;
						(*args).colStart = 6;
						(*args).colEnd = 8;
						pthread_create(&block6,NULL,&check_three_by_three, (void *)args);
						pthread_join(block6,&grid_val);
						if (grid_val){
							/*GRID 7: BOTTOM LEFT*/
							(*args).rowStart = 6;
							(*args).rowEnd = 8;
							(*args).colStart = 0;
							(*args).colEnd = 2;
							pthread_create(&block7,NULL,&check_three_by_three, (void *)args);
							pthread_join(block7,&grid_val);
							if (grid_val){
								/*GRID 8: BOTTOM MIDDLE*/
								(*args).rowStart = 6;
								(*args).rowEnd = 8;
								(*args).colStart = 3;
								(*args).colEnd = 5;
								pthread_create(&block8,NULL,&check_three_by_three, (void *)args);
								pthread_join(block8,&grid_val);
								if (grid_val){
									/*GRID 9: BOTTOM RIGHT*/
									(*args).rowStart = 6;
									(*args).rowEnd = 8;
									(*args).colStart = 6;
									(*args).colEnd = 8;
									pthread_create(&block9,NULL,&check_three_by_three, (void *)args);
									pthread_join(block9,&grid_val);
								}
							}
						}
					}
				}
			}
		}

	}

	
	
	//printf("%d\n",(ret_val && temp && grid_val));

	if ((ret_val && temp && grid_val)){
		printf("Puzzle is valid \n");
	} else {
		printf("Puzzle is NOT valid.\n");
	}
	return (ret_val && temp && grid_val);

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


//printf ("Row Result is %d\n", overallResult);

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
		//printf ("Column Result is %d\n", overall);
	}

	
	return overall;

}

int check_three_by_three( struct arg_struct *args)
{
	
int i=0;
int j=0;
int isValid[9] = {0,0,0,0,0,0,0,0,0};
int overallResult = 1;
int gridResult = 1;

	for (i = args->rowStart; i<=args->rowEnd; i++){
		for (j=args->colStart; j<=args->colEnd; j++){
			int underExam = args->gridBoard[i][j];
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

//printf ("GRID Overall Result is %d\n", gridResult);

return gridResult;
}

