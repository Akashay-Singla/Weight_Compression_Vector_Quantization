#include<stdint.h>
#include<stdio.h>
#include<math.h>

uint8_t g[8][8]= {
		{139, 144, 149, 153, 155, 155, 155, 155},
		{144, 151, 153, 156, 159, 156, 156, 156},
		{150, 155, 160, 163, 158, 156, 156, 156},
		{159, 161, 162, 160, 160, 159, 159, 159},
		{159, 160, 161, 162, 162, 155, 155, 155},
		{161, 161, 161, 161, 160, 157, 157, 157},
		{162, 162, 161, 163, 162, 157, 157, 157},
		{162, 162, 161, 161, 163, 158, 158, 158}};

uint8_t cdbook[8][4]= {
		{15, 15, 15, 15},
		{47, 47, 47, 47},
		{79, 79, 79, 79},
		{112, 112, 112, 112},
		{146, 146, 146, 146},
		{178, 178, 178, 178},
		{210, 210, 210, 210},
		{242, 242, 242, 242},
};

void codebook_training(uint8_t input_vec[8][8])
{
int d[4];
int mean_sqr_err[8]; 
int sum[4]={0},sum_temp[4]={0};
int max=0; 
while(1){
for(int8_t row=0;row<8;row=row+2)
{
	    for(int8_t col=0;col<8;col=col+2)
	{
	    	for(int8_t cd_row=0;cd_row<8;cd_row++)
	    		{
          d[0]= pow((input_vec[row][col]-cdbook[cd_row][0]),2);
          d[1] = pow((input_vec[row][col+1] - cdbook[cd_row][1]),2);
          d[2] = pow((input_vec[row+1][col] - cdbook[cd_row][2]),2);
          d[3] = pow((input_vec[row+1][col+1] - cdbook[cd_row][3]),2);
          mean_sqr_err[cd_row] = (int)((d[0]+d[1]+d[2]+d[3]));
          if(cd_row){
                if(mean_sqr_err[cd_row]<mean_sqr_err[cd_row-1]){ 
				sum[0] += input_vec[row][col];
            	sum[1] += input_vec[row][col+1];
            	sum[2] += input_vec[row+1][col] ;
            	sum[3] += input_vec[row+1][col+1] ;
				sum_temp[0]= ceil((double)sum[0]/(double)2);
            	sum_temp[1]= ceil((double)sum[1]/(double)2);
            	sum_temp[2]= ceil((double)sum[2]/(double)2);
            	sum_temp[3]= ceil((double)sum[3]/(double)2);
				cdbook[cd_row][0]= sum_temp[0];
            	cdbook[cd_row][1]= sum_temp[1] ;
            	cdbook[cd_row][2]= sum_temp[2];
            	cdbook[cd_row][3]= sum_temp[3];
				max=mean_sqr_err[cd_row];
                }
                else{
                	mean_sqr_err[cd_row]=mean_sqr_err[cd_row-1];
                }
          }
	}
}
}
if(max){
	max=0;
}
else{
	break;
}
}
printf("Codebook\n");
for(int l=0;l<8;l++)
{
	for(int k=0;k<4;k++)
	{
		printf(" %d, ",cdbook[l][k]);
	}
	printf("\n");
}
}

int main()
{
	codebook_training(g);
	return 0;
}
