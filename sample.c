#include<stdint.h>
#include<stdio.h>
#include<math.h>
//Input weight values
/*uint8_t g[8][8]= {
		{139, 144, 149, 153, 155, 155, 155, 155},
		{144, 151, 153, 156, 159, 156, 156, 156},
		{150, 155, 160, 163, 158, 156, 156, 156},
		{159, 161, 162, 160, 160, 159, 159, 159},
		{159, 160, 161, 162, 162, 155, 155, 155},
		{161, 161, 161, 161, 160, 157, 157, 157},
		{162, 162, 161, 163, 162, 157, 157, 157},
		{162, 162, 161, 161, 163, 158, 158, 158}};

//Initialisation of code book
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
//Address book (initialised with 0)
int8_t addr_book[4][4]= {0};
*/
//Akashay Singla
//015349334

uint8_t g[12][2] = {
    {72,180}, {65,120},{59,119},{64,150},{65,162},{57,88},
    {72,175},{44,41},{62,114},{60,110},{56,91}, {70,172}};
uint8_t cdbook[4][2]={
    {45,50}, {75,117},{45,117},{80,180}};
int8_t addr_book[12]= {0};
//codebook training function
void codebook_training(uint8_t input_vec[12][2])
{
int d[2];//distortion
int mean_sqr_err[4]; //mean square error
int i=0, num=0;
int sum[4]={0},sum_temp[4]={0};
int count=0;//for counting numbers of same values of address book
int flag;
int diff[4]={0}; //for calculating the difference between previous change
int max=0; //for verifying when loop doesn't change further
while(1){
	//First updates the address book with the address of the row of the codebook which has min. distortion
for(int8_t row=0;row<12;row++)
{
	    	for(int8_t cd_row=0;cd_row<4;cd_row++)
	    		{
	    		//calcualtes the difference and then square the value
          d[0]= pow((input_vec[row][0]-cdbook[cd_row][0]),2);
          d[1] = pow((input_vec[row][1] - cdbook[cd_row][1]),2);
          //Calculating the mean square value
          mean_sqr_err[cd_row] = (int)((d[0]+d[1])/2);
         //updates the address book with value of the codebook's row which has less mean square error
          if(cd_row){
                if(mean_sqr_err[cd_row]<mean_sqr_err[cd_row-1]){ //Comparing the value with the last mean square value
                	addr_book[row]= cd_row;

                }
                else{
                	mean_sqr_err[cd_row]=mean_sqr_err[cd_row-1];
                }
          }
          else
          {
        	  addr_book[row]= cd_row;
          }
	}
}

//Akashay Singla
//015349334
//for updating the codebook. It updates those rows only which are updated in the address book
for(int cod_row=0;cod_row<4;cod_row++)
{
	sum[0]=0;sum[1]=0;sum[2]=0; sum[3]=0;
	count=0;
for(int addr_row =0;addr_row<12;addr_row++)
{
      //It matches the address book value with row of the codebook
            if(addr_book[addr_row]== cod_row)
            {
            	//adds the values for calculating the average
            	sum[0] += input_vec[addr_row][0];
            	sum[1] += input_vec[addr_row][1];
            	count++;
            	flag++;
            }
	}

            if(flag){
            	//averaging the sum of input matrix which matches with the row of code
            	sum_temp[0]= ceil(((double)sum[0]/(double)count));
            	sum_temp[1]= ceil(((double)sum[1]/(double)count));
            	//calcuating the difference between last codebook value
            	diff[0]= cdbook[cod_row][0] - sum_temp[0];
            	diff[1]= cdbook[cod_row][1] - sum_temp[1];

            	if(diff[0]>max) max=diff[0];
            	else if(diff[1]>max) max=diff[1];

            	//updating the codebook values
            	cdbook[cod_row][0]= sum_temp[0];
            	cdbook[cod_row][1]= sum_temp[1] ;
            	flag=0;
            }
}
//Akashay Singla
//015349334
if(max){
	max=0;
}
else{
	break; //if all the codebook' last and updated values become same then it breaks the loop
}
}
//for printing the updated codebook
printf("\n");
printf("Codebook\n");
for(int l=0;l<4;l++)
{
	for(int k=0;k<2;k++)
	{
		printf(" %d, ",cdbook[l][k]);
	}
	printf("\n");
}

//for printing the updated address book
printf("\n");
printf("Address book\n");
for(int n1=0;n1<4; n1++){
	printf(" %d, ",addr_book[n1]);
	printf("\n");
}
}



int main()
{
	//passing values to codebook training function
	codebook_training(g);
	return 0;
}
