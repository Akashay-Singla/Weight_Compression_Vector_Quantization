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

int16_t g[THETAROW_N][THETACOL_N]= 
{{-3367, -17090, 29000, 30019, 2838, -3135, -21384, 9396, 12155, -8235, -32441, -4253, 11469, -6477, -7073, 350, -20826, 8240, 22708, -14864, -7997, -23392, 4204, -25898, 17986, -23609 }, 
{-14847, 13016, -6496, -27668, -27040, -4638, 10260, -18457, 286, 5396, 9943, 8103, -7862, 26774, 2367, 5335, -17192, -8066, -8549, 3592, -10054, -12410, -20202, -10059, -1642, -1699 }, 
{-18673, -1679, 1110, 14884, 241, -8125, 1366, 25363, 7030, 3268, -20480, -9720, 13499, -2665, 3281, -6646, -20457, -4717, 5241, 2887, 3839, -13339, -17848, -31066, 22650, -17416 }, 
{-1029, 4152, 4278, 15341, -14950, -23443, 4586, -7369, -23864, 4226, -12956, 27292, -16429, -8517, -13066, -22544, 17417, -8645, -11206, 15718, -3901, 17067, 1058, 1935, -14933, -4831 }, 
{-9874, -4333, 4092, -23931, -2514, -15315, -31317, 10511, -14403, -7258, -14842, -12455, 22126, -8218, 12817, -8769, -11102, -11098, 2302, 7949, 6025, 25893, -357, -13957, 18948, -15745 }, 
{-6241, 12947, 3054, -18762, -14107, 967, -17026, 28420, 4962, -2903, 4986, 16063, 9125, -7272, -7541, -1852, 16893, -7381, -23994, 22980, -14140, -18407, -1828, -10764, -14029, 1846 }, 
{-10870, -14297, -1259, -9350, 26311, -6191, 795, 32553, -14484, 11036, 28716, -17519, -8702, -6933, -22704, 5901, -12599, 12305, -1697, -7610, 15052, 8082, -20381, 11497, -11107, 4698 }, 
{-25791, 6190, 21, -16443, 5526, -4788, -502, 24074, 13896, -15232, -24387, -20325, -31055, 13162, -2503, -19198, -8399, -20216, -1200, 4029, 15986, -10958, -18846, -18060, -3680, 7589 }, 
{-9421, -8859, 5478, 1849, 1299, -6841, 6366, -2632, 15776, -5680, -16347, -24763, -12077, -20524, -7328, 29483, 28605, -22011, -11599, 1998, -917, 7681, -2613, 3031, -9530, -11578 }, 
{-9543, -20792, -10828, -21214, -3752, 9390, 3352, 306, -5185, 5718, -19893, -10731, -15710, -16464, 22519, -12995, -17704, 10260, -1145, 18748, -21193, -10601, -22583, -5565, 30927, 19590 } 
 };


int16_t addr_book [ADDROW_N][ADDCOL_N];
int16_t cdbook[CDROW_N][CDCOL_N] = {{-6500,-6500,6500,-6500,6500},
                                   {5000,-5000,-5000,-5000,5000},
                                   {-15000,-15000,15000,15000,15000},
                                   {-10000,10000,10000,-10000,-10000},
                                   {3500,-3500,3500,3500,-3500},
                                   {8000,-8000,8000,-8000,8000},
                                   {-1500,-1500,1500,-1500,1500},
                                   {-9000,9000,9000,-9000,9000},
                                   {-18000,18000,-18000,18000,-18000},
                                   {-3000,3000,3000,-3000,-3000},
                                   {-1000,1000,-1000,1000,1000},
                                   {-12000,-12000,12000,12000,-12000},
                                   {-1200,1200,-1200,1200,-1200},
                                    {-15000,15000,-5000,-15000,-15000},
                                    {9000,-9000,9000,9000,-9000},
                                    {-4000,4000,4000,-4000,4000}};
//codebook training function

void codebook_training(int16_t input_vec[THETAROW_N][THETACOL_N])
{
int64_t d;//distortion
int64_t mean_sqr_err[CDROW_N]; //mean square error
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
            	cdbook[cod_row][num]= (int16_t)sum_temp[num];
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
	if(n2== ADDCOL_N-1)printf(" %d ",addr_book[n1][n2]);
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