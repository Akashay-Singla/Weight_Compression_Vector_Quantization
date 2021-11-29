#include<stdint.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define CDROW_N 14
#define CDCOL_N 5
#define ADDROW_N 2
#define ADDCOL_N 26
#define THETACOL_N 26
#define THETAROW_N 10
#define DIV_THETA 5 //(25/5)

int8_t g[THETAROW_N][THETACOL_N]= 
{{0, -4, -8, 8, 1, 0, -5, 3, 3, -2, 9, -1, 3, -1, -1, 1, -5, 3, 6, -3, -1, -5, 2, 10, 5, -5 }, 
{-3, 4, -1, -6, -6, -1, 3, -4, 1, 2, 3, 2, -1, 7, 1, 2, -4, -1, -2, 1, -2, -3, -4, -2, 0, 0 }, 
{-4, 0, 1, 4, 1, -1, 1, -9, 2, 1, -5, -2, 4, 0, 1, -1, -4, -1, 2, 1, 1, -3, -4, -7, 6, -4 }, 
{0, 2, 2, 4, -3, -5, 2, -1, -5, 2, -3, 7, -4, -2, -3, -5, 5, -2, -2, 4, 0, 5, 1, 1, -3, -1 }, 
{-2, -1, 1, -5, 0, -3, -7, 3, -3, -1, -3, -3, 6, -2, 4, -2, -2, -2, 1, 2, 2, 7, 0, -3, 5, -3 }, 
{-1, 4, 1, -4, -3, 1, -4, 7, 2, 0, 2, 4, 3, -1, -1, 0, 5, -1, -5, -10, -3, -4, 0, -2, -3, 1 }, 
{-2, -3, 0, -2, 7, -1, 1, -8, -3, 3, 8, -4, -2, -1, -5, 2, -3, 4, 0, -1, 4, 2, 12, 3, -2, 2 }, 
{-6, 2, 1, -4, 2, -1, 0, 6, 4, -3, -5, -4, -7, 4, 0, -4, -2, -4, 0, 1, 4, -2, -4, -4, 0, 2 }, 
{-2, -2, 2, 1, 1, -1, 2, 0, 4, -1, -3, -6, -2, -5, -1, 8, 7, -5, -2, 1, 0, 2, 0, 1, -2, -2 }, 
{-2, -5, -2, -5, 0, 3, 1, 1, -1, 2, -4, -2, -3, -4, 6, -3, -4, 3, 0, 5, -5, -2, -5, -1, -8, 5 }
 };

int8_t addr_book [ADDROW_N][ADDCOL_N];
int8_t cdbook[CDROW_N][CDCOL_N] = 
                        {
                         {8,8,-8,8,8},
                         {-2,1,1,1,-1},
                         {8,9,-10,5,9},
                         {-2,-5,-2,-5,0},
                         {0,1,-3,0,-1},
                         {4,-5,5,-4,5},
                         {-3,-2,-1,-3,-3},
                         {-3,-5,6,-3,-5},
                         {-4,-7,-3,-1,-10},
                         {7,-5,-7,7},
                         {-2,1,0,-2,1},
                         {-4,-5,-9,9,4},
                         {-3,-2,-1,1,2},
                         {-7,-7,7,7,-7},
                         };
//codebook training function

void codebook_training(int8_t input_vec[THETAROW_N][THETACOL_N])
{
int d;//distortion
int mean_sqr_err[CDROW_N]; //mean square error
int sum[CDCOL_N]={0},sum_temp[CDCOL_N]={0};
int count=0;//for counting numbers of same values of address book
int diff[CDCOL_N]={0}; //for calculating the difference between previous change
int cod_row_match=0;
int max=0; //for verifying when loop doesn't change further
while(1){
	//First updates the address book with the address of the row of the codebook which has min. distortion
for(int col=0;col<=THETACOL_N;col++)  //401
{
	    for(int row=0;row<THETAROW_N;row=row+CDCOL_N)
	{
	    	for(int cd_row=0;cd_row<CDROW_N;cd_row++)
	    		{
                    for(int cd_col=0;cd_col<CDCOL_N;cd_col++)
	    		    {
	    		//calcualtes the difference and then square the value
                        d+= pow((input_vec[row+cd_col][col]-cdbook[cd_row][cd_col]),2);
                      //  printf("input_vec[%d][%d]: %d      cdbook[%d][%d]: %d \n",(row+cd_col),col,input_vec[row+cd_col][col],cd_row,cd_col,cdbook[cd_row][cd_col]);
                    }
          //Calculating the mean square value
          mean_sqr_err[cd_row] = ceil((double)d/(double)CDCOL_N);
                  // printf("mean_sqr: %d\n",mean_sqr_err[cd_row]);
                   d=0;
         //updates the address book with value of the codebook's row which has less mean square error
          if(cd_row){
                if(mean_sqr_err[cd_row]<mean_sqr_err[cd_row-1]){ //Comparing the value with the last mean square value
                	addr_book[row/DIV_THETA][col]= cd_row;           
                }
                else mean_sqr_err[cd_row]=mean_sqr_err[cd_row-1];
          }
          else addr_book[row/DIV_THETA][col]= cd_row;
	}
}

}



//Akashay Singla
//015349334
//for updating the codebook. It updates those rows only which are updated in the address book
for(int cod_row=0;cod_row<CDROW_N;cod_row++)
{
	sum[0]=0;sum[1]=0;sum[2]=0; sum[3]=0; sum[4]=0;
	count=0;
for(int addr_col =0;addr_col<ADDCOL_N;addr_col++)
{
	for(int addr_row=0;addr_row<ADDROW_N;addr_row++)
	{       //It matches the address book value with row of the codebook
            if(addr_book[addr_row][addr_col] == cod_row)
            {
            	//adds the values for calculating the average
                for (int cod_col = 0; cod_col<CDCOL_N; cod_col++)
                {
               sum[cod_col] += input_vec[(addr_row*DIV_THETA)+cod_col][addr_col];
               cod_row_match++;
                }
                count++;
            }
            
    }           	
}        	       //print_addr_book();
            	//averaging the sum of input matrix which matches with the row of code
                if(cod_row_match){
                    cod_row_match=0;
                for(int num=0;num<CDCOL_N;num++){
            	sum_temp[num]= ceil((double)sum[num]/(double)count);
            	//calcuating the difference between last codebook value
            	diff[num]= abs(cdbook[cod_row][num] - sum_temp[num]);
            	if(diff[num]>max) max=diff[num];
            	//updating the codebook values
            	cdbook[cod_row][num]= sum_temp[num];
                //printf("cdbook[%d][%d]: %d \n",cod_row, num,cdbook[cod_row][num]);
            }
            }
}
//Akashay Singla
//015349334
//printf("max: %d\n",max);
if(max) max=0;
else break; //if all the codebook' last and updated values become same then it breaks the loop
}


printf("****************************Codebook*******************************\n");
printf("{");
for(int l=0;l<CDROW_N;l++)
{
    printf("{");
	for(int k=0;k<CDCOL_N;k++)
	{
		//printf("cdbook[%d][%d]: %d", l,k,cdbook[l][k]);
		if(k==CDCOL_N-1)printf(" %d ",cdbook[l][k]);
        else printf(" %d, ",cdbook[l][k]);
	}
    printf("},");
	printf("\n");
}
 printf("};");
	printf("\n");
//for printing the updated address book
printf("Address book\n");
printf("{");
for(int n1=0;n1<ADDROW_N; n1++){
    printf("{");
	for(int n2=0;n2<ADDCOL_N; n2++){
	//printf("addr_book[%d][%d]: %d ", n1,n2,addr_book[n1][n2]);
	if(n2 == ADDCOL_N-1)printf(" %d ",addr_book[n1][n2]);
    else printf(" %d, ",addr_book[n1][n2]);
}
    printf("},");
	printf("\n");
}
printf("};");
}

int main()
{
	//passing values to codebook training function
	codebook_training(g);
	return 0;
}