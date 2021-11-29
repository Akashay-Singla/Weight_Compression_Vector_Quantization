#include<stdint.h>
#include<stdio.h>
#include<math.h>

#define CDROW_N 16
#define CDCOL_N 5
#define ADDROW_N 2
#define ADDCOL_N 26
#define THETACOL_N 26
#define THETAROW_N 10
#define NUM_ELEMENT 260

int8_t output_vec[THETAROW_N][THETACOL_N];

int8_t cd_book [CDROW_N][CDCOL_N] =
{{ 8,  8,  -8,  8,  8 },
{ -1,  3,  1,  3,  -1 },
{ 8,  9,  -10,  5,  9 },
{ 3,  -3,  -4,  -1,  0 },
{ 4,  8,  -4,  -2,  -4 },
{ 6,  -2,  5,  -2,  4 },
{ -3,  0,  -3,  1,  -2 },
{ 2,  0,  2,  -4,  -3 },
{ -3,  2,  2,  0,  -6 },
{ 8,  -3,  -1,  4,  -4 },
{ 0,  2,  0,  -2,  4 },
{ -4,  -5,  -9,  9,  4 },
{ -6,  -2,  0,  2,  5 },
{ -7,  -7,  7,  7,  -7 },
};

int8_t addr_book[ADDROW_N][ADDCOL_N]= 
{{ 3,  1,  12,  9,  3,  7,  8,  3,  7,  1,  4,  1,  5,  1,  10,  7,  6,  3,  5,  1,  10,  12,  3,  9,  5,  6 },
{ 6,  7,  1,  6,  1,  10,  1,  5,  1,  10,  4,  3,  3,  7,  12,  1,  9,  10,  6,  12,  8,  6,  4,  6,  8,  10 }
};
void decompression_func(int8_t addr_book[ADDROW_N][ADDCOL_N])
{
    for(int addr_row =0; addr_row<ADDROW_N; addr_row++)
    {
        for(int addr_col = 0;addr_col <ADDCOL_N; addr_col++)
        {
            for(int cd_row = 0;cd_row <CDROW_N; cd_row++)
            {
                if(addr_book[addr_row][addr_col] == cd_row)
                {
                    for(int cd_col =0; cd_col<CDCOL_N;cd_col++)
                    {
                        output_vec[(addr_row*5) + cd_col][addr_col] = cd_book[cd_row][cd_col];
                    }
                }
               
            }
        }
    }
    printf("{");
for (int row = 0; row < THETAROW_N; row++)
  {
       printf("{");
      for (int col = 0; col < THETACOL_N; col++)
      {
       if(col == THETACOL_N-1) printf("%d ",output_vec[row][col]);
       else printf("%d, ",output_vec[row][col]);
      }
      printf("},\n");
  }
 printf("};");
}


int main()
{
   decompression_func(addr_book);
}