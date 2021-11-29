#include<stdint.h>
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define CDROW_N 16
#define CDCOL_N 5
#define ADDROW_N 2
#define ADDCOL_N 26
#define THETACOL_N 26
#define THETAROW_N 10
#define DIV_THETA 5 //(25/5)

int8_t g[THETAROW_N][THETACOL_N]= 
{{-13, -66, 114, 117, 11, -12, -83, 36, 47, -32, -127, -16, 44, -25, -27, 1, -81, 32, 88, -58, -31, -91, 16, -102, 70, -92, }, 
{-57, 50, -25, -108, -105, -18, 40, -72, 1, 21, 38, 31, -30, 104, 9, 20, -67, -31, -33, 14, -39, -48, -78, -39, -6, -6, }, 
{-72, -6, 4, 58, 0, -31, 5, 100, 27, 12, -80, -37, 52, -10, 12, -25, -79, -18, 20, 11, 14, -52, -69, -121, 88, -68, }, 
{-4, 16, 16, 59, -58, -91, 17, -28, -93, 16, -50, 106, -64, -33, -51, -88, 68, -33, -43, 61, -15, 66, 4, 7, -58, -18, }, 
{-38, -16, 15, -93, -9, -59, -122, 41, -56, -28, -57, -48, 86, -32, 50, -34, -43, -43, 8, 31, 23, 101, -1, -54, 74, -61, }, 
{-24, 50, 11, -73, -55, 3, -66, 111, 19, -11, 19, 62, 35, -28, -29, -7, 65, -28, -93, 90, -55, -71, -7, -42, -54, 7, }, 
{-42, -55, -4, -36, 102, -24, 3, -128, -56, 43, 112, -68, -33, -27, -88, 23, -49, 48, -6, -29, 58, 31, -80, 44, -43, 18, }, 
{-100, 24, 0, -64, 21, -18, -1, 94, 54, -59, -95, -79, -121, 51, -9, -74, -32, -78, -4, 15, 62, -42, -73, -70, -14, 29, }, 
{-36, -34, 21, 7, 5, -26, 24, -10, 61, -22, -63, -96, -47, -80, -28, 115, 111, -85, -45, 7, -3, 30, -10, 11, -37, -45, }, 
{-37, -81, -42, -82, -14, 36, 13, 1, -20, 22, -77, -41, -61, -64, 87, -50, -69, 40, -4, 73, -82, -41, -88, -21, 121, 76, }, 
}; 

int8_t addr_book [ADDROW_N][ADDCOL_N];
int8_t cdbook[CDROW_N][CDCOL_N] = 
                        {
                         {8,8,8,8,8},
                         {25,25,25,25,25},
                         {8,9,11,15},
                         {31,22,35,37,39},
                         {23,24,18,14,30},
                         {12,15,25,35,22},
                         {-3,-2,-1,-3,-3},
                         {-5,-5,-5,-5,-5},
                         {-10,-10,-10,-10,-10},
                         {-15,-15,-15,-15},
                         {-25,-25,-25,-25,-25},
                         {-30,-30,-30,-30,-30},
                         {-18,-18,-18,-18,-18},
                         {-7,-7,7,7,-7},
                         {-20,-20,-20,-20},
                         {-12,-12,-12,-12,-12}
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