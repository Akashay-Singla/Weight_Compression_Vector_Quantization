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


int32_t g[THETAROW_N][THETACOL_N]= 
{{-110356481, -560023736, -1197229015, 983640099, 92979903, -102739840, -700734863, 307878154, 398266429, -269866838, 1084437746, -139381095, 375787070, -212250260, -231775511, 11439882, -682449413, 269994666, 744095733, -487090632, -262050155, -766539023, 137742858, 1298828098, 589352318, -773649887 }, 
{-486535054, 426503840, -212888223, -906625560, -886052490, -152001159, 336178697, -604811124, 9367529, 176808788, 325811789, 265508666, -257643457, 877318489, 77548478, 174801766, -563366650, -264328372, -280157936, 117688810, -329460023, -406652730, -661986693, -329635377, -53822667, -55677580 }, 
{-611883644, -55019021, 36370933, 487706038, 7896428, -266257646, 44739294, -1316395097, 230350751, 107082143, -671109093, -318510540, 442312080, -87341503, 107506104, -217805465, -670365444, -154586419, 171706134, 94588680, 125766809, -437100430, -584859350, -1017979218, 742192390, -570716753 }, 
{-33739488, 136044843, 140171052, 502682903, -489891767, -768181575, 150256554, -241479374, -781982551, 138447840, -424558541, 894289377, -538377557, -279102204, -428159359, -738740697, 570702164, -283302324, -367199254, 515045197, -127835287, 559242650, 34668362, 63378627, -489333890, -158322466 }, 
{-323568564, -142004232, 134065663, -784177796, -82410220, -501842584, -1026202617, 344411200, -471958365, -237859377, -486344504, -408157653, 724997553, -269316910, 419956710, -287362750, -363801416, -363682595, 75429795, 260451192, 197399943, 848446389, -11705506, -457355929, 620866432, -515957157 }, 
{-204525003, 424230368, 100047080, -614816479, -462258224, 31658934, -557939322, 931260908, 162585046, -95155947, 163350228, 526332563, 299005218, -238289774, -247126918, -60687844, 553532520, -241867795, -786250718, -1394481119, -463366042, -603169655, -59916577, -352722396, -459714394, 60487185 }, 
{-356203645, -468510290, -41280124, -306381051, 862149220, -202895824, 26026852, -1080795554, -474638789, 361601190, 940963371, -574076407, -285155189, -227180963, -743994234, 193353711, -412853509, 403177822, -55623500, -249373231, 493220409, 264812103, 1479629120, 376704088, -363972798, 153918635 }, 
{-845133139, 202813611, 683705, -538819326, 181055145, -156895596, -16465335, 788845434, 455311764, -499135497, -799138036, -666010706, -1017634191, 431269009, -82035188, -629088284, -275249499, -662440869, -39341678, 132008906, 523799047, -359085631, -617565948, -591806641, -120601182, 248671539 }, 
{-308734630, -290319982, 179484275, 60581877, 42552241, -224196574, 208590200, -86267337, 516940070, -186140261, -535668021, -811436017, -395739276, -672551945, -240146915, 966083677, 937314363, -721267128, -380102811, 65438084, -30064637, 251664648, -85630814, 99313252, -312301494, -379409510 }, 
{-312734512, -681327284, -354844436, -695153701, -122966873, 307660749, 109824873, 10003209, -169922684, 187362809, -651865467, -351645373, -514807102, -539518594, 737882159, -425828886, -580144723, 336184447, -37520089, 614305806, -694453600, -347389574, -740030165, -182366983, -1134075305, 641905309 }, 
 };


int32_t addr_book [ADDROW_N][ADDCOL_N];
int32_t cdbook[CDROW_N][CDCOL_N] = 
                         {{560023736,560023736,-560023736,560023736,-560023736},
                         {-136044843,136044843,-136044843,136044843,-136044843},
                         {845133139,-845133139,845133139,845133139,-845133139},
                         {538819326,-538819326,538819326,-538819326,538819326},
                         {-681327284,681327284,-681327284,681327284,-681327284},
                         {-7896428,-7896428,7896428,-7896428,7896428},
                         {-95155947,95155947,-95155947,-95155947,95155947},
                         {42552241,-42552241,-42552241,42552241,-42552241},
                         {-181055145,181055145,-181055145,181055145,-181055145},
                         {307660749,-307660749,-307660749,307660749,-307660749},
                         {424500521,424500521,-424500521,424500521,-424500521},
                         {304002319,-304002319,-304002319,304002319,304002319},
                         {1862521815,-1862521815,1862521815,-1862521815,-1862521815},
                         {-122966873,122966873,-122966873,122966873,-122966873},
                         {268131325,-268131325,268131325,-268131325,268131325},
                         {202895824,-202895824,-202895824,-202895824,202895824}};
//codebook training function

void codebook_training(int32_t input_vec[THETAROW_N][THETACOL_N])
{
uint64_t d;//distortion
uint64_t mean_sqr_err[CDROW_N]; //mean square error
int64_t sum[CDCOL_N]={0},sum_temp[CDCOL_N]={0};
int count=0;//for counting numbers of same values of address book
uint64_t diff[CDCOL_N]={0}; //for calculating the difference between previous change
int cod_row_match=0;
uint64_t max=0; //for verifying when loop doesn't change further

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
                     //  printf("d: %llu \n",d);
                      //  printf("input_vec[%d][%d]: %d      cdbook[%d][%d]: %d \n",(row+cd_col),col,input_vec[row+cd_col][col],cd_row,cd_col,cdbook[cd_row][cd_col]);
                    }
                      //Calculating the mean square value
                       mean_sqr_err[cd_row] = ceil((double)d/(double)CDCOL_N);
                     // printf("mean_sqr[%d]: %llu \n",cd_row,mean_sqr_err[cd_row]);
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
            	diff[num]= llabs(cdbook[cod_row][num] - sum_temp[num]);            	
                if(diff[num]>max) max=diff[num];
            	//printf("diff[%d]: %llu, max: %llu\n",num,diff[num], max);

                //updating the codebook values
            	cdbook[cod_row][num]= (int32_t)sum_temp[num];
                //printf("cdbook[%d][%d]: %d \n",cod_row, num,cdbook[cod_row][num]);
            }
            }
}
//Akashay Singla
//015349334
if(max) { 
    max=0;
}
else {

 break;
} //if all the codebook' last and updated values become same then it breaks the loop
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