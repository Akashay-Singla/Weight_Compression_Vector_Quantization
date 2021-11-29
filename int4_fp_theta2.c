#include<stdint.h>
#include<stdio.h>
#include<math.h>

#define THETAROW_N  10
#define THETACOL_N  26
#define INT_BITS 1 // 1 for 4-bit, 5 for 8-bit, 13 for 6 bit& 29 for 32 bit  3 bits for representing integer value
int8_t g[THETAROW_N][THETACOL_N] = 
{{3, -1, -6, 8, 3, 2, -3, 3, 2, -1, 4, -1, 6, -1, 0, 2, -3, 3, 6, -1, 0, -6, 3, 8, 6, -3 },
{-3, 3, -2, -3, -3, 0, 2, -3, 0, 3, 8, 3, -2, 3, 2, 0, 0, -3, -2, 3, 2, -2, -3, -3, -2, 0 },
{-4, 1, 0, -1, -4, 2, 2, -4, 2, 1, -4, 1, 5, 1, 0, 2, -3, -4, 5, 1, 0, 0, -4, -1, 5, -3 },
{-1, 3, 2, 4, -1, -4, 0, -1, -4, 3, -2, 3, -2, 3, -2, -4, 1, -1, -2, 3, -2, 2, -1, 4, -2, 1 },
{0, -1, 5, -4, 0, -3, -6, 0, -3, -1, -4, -1, 4, -1, 4, -3, -2, 0, 4, -1, 4, 5, 0, -4, 4, -2 },
{-3, 2, -1, -3, -1, 0, -1, 6, -1, 0, 4, 3, 3, 2, -6, -1, 8, 0, -3, -6, -3, -3, 4, -3, -3, 0 },
{0, 0, 3, 0, 3, 2, 3, -2, 3, 2, 8, -3, -3, 0, -2, 3, -3, 2, 0, -2, 2, 0, 8, 0, 2, 2 },
{-3, 2, 1, -3, 1, 0, 1, 5, 1, 0, -4, -4, -4, 2, 0, 1, -1, 0, -3, 0, 2, -3, -4, -3, 2, 0 },
{1, -4, 3, 1, 3, -2, 3, -2, 3, -2, -2, -1, -1, -4, 2, 3, 4, -2, 1, 2, 0, 1, -2, 1, 0, -2 },
{-2, -3, -1, -2, -1, 4, -1, 4, -1, 4, -4, 0, 0, -3, 5, -1, -4, 4, -2, 5, -6, -2, -4, -2, -6, 4 },
};

int main()
{
    double x[THETAROW_N][THETACOL_N];
    FILE * fp;

   fp = fopen ("int4_fp_Th2.txt", "w+");
   fprintf(fp,"[");
    for(int row =0; row<THETAROW_N;row++)
    {
        //fprintf(fp,"{");
        for(int col=0;col<THETACOL_N;col++)
        {
            x[row][col] = (double)(g[row][col])/(double)(1<< INT_BITS);
            fprintf(fp,"%f ",x[row][col]);
        }
        
       fprintf(fp,"; \n");
    }
     fprintf(fp,"]\n");
    fclose(fp);
    return 0;
}