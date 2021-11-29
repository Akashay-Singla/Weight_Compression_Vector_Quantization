#include<stdint.h>
#include<stdio.h>
#include<math.h>

#define CDROW_N 20
#define CDCOL_N 5
#define ADDROW_N 5
#define ADDCOL_N 401
#define THETACOL_N 401
#define THETAROW_N 25
#define NUM_ELEMENT 10025

int8_t output_vec[THETAROW_N][THETACOL_N];

int8_t addr_book[ADDROW_N][ADDCOL_N]= 
{{ 18,  10,  10,  9,  10,  9,  9,  9,  9,  9,  9,  10,  9,  10,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  10,  10,  9,  9,  9,  9,  9,  9,  9,  10,  9,  9,  9,  10,  9,  10,  9,  9,  9,  9,  9,  9,  10,  9,  9,  10,  10,  10,  9,  9,  11,  9,  9,  10,  11,  10,  10,  10,  10,  9,  9,  9,  9,  10,  10,  9,  10,  10,  9,  9,  11,  17,  17,  17,  17,  18,  17,  10,  10,  10,  9,  9,  9,  10,  9,  9,  9,  9,  8,  11,  17,  17,  17,  18,  18,  18,  17,  10,  10,  8,  9,  9,  9,  9,  9,  9,  9,  8,  8,  11,  11,  10,  10,  18,  18,  18,  18,  17,  0,  8,  8,  9,  9,  10,  9,  9,  9,  3,  3,  11,  11,  9,  9,  3,  3,  18,  18,  13,  0,  8,  8,  9,  10,  9,  9,  9,  3,  3,  3,  11,  8,  8,  2,  2,  19,  18,  18,  18,  1,  8,  8,  9,  9,  9,  9,  18,  11,  8,  11,  11,  0,  5,  5,  7,  19,  19,  18,  11,  1,  8,  9,  9,  9,  9,  11,  18,  11,  1,  13,  0,  0,  0,  5,  2,  2,  19,  3,  1,  1,  8,  9,  9,  9,  9,  11,  13,  11,  11,  10,  0,  0,  5,  2,  2,  2,  3,  3,  1,  10,  11,  9,  10,  9,  9,  11,  13,  10,  1,  10,  0,  5,  2,  2,  2,  3,  3,  11,  9,  9,  9,  9,  9,  9,  9,  9,  10,  10,  0,  10,  8,  2,  2,  2,  8,  13,  13,  13,  9,  9,  9,  10,  9,  10,  10,  9,  11,  17,  0,  8,  8,  8,  9,  10,  10,  13,  13,  11,  11,  9,  9,  9,  9,  9,  10,  9,  11,  9,  10,  8,  17,  17,  17,  18,  17,  18,  18,  18,  11,  11,  9,  9,  9,  9,  9,  9,  9,  9,  11,  11,  17,  17,  18,  17,  11,  18,  18,  18,  11,  9,  9,  9,  9,  9,  9,  9,  9,  9,  11,  11,  10,  9,  10,  10,  10,  9,  11,  9,  9,  10,  9,  9,  9,  9,  9,  10,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  10,  10,  9,  9,  9,  10,  9,  9,  10,  9,  10,  9,  9,  10,  9,  9,  9,  9,  9,  10,  9,  9,  9, },
{ 11,  9,  10,  9,  9,  9,  9,  9,  9,  10,  9,  9,  9,  9,  9,  9,  9,  10,  9,  10,  10,  9,  9,  9,  9,  9,  9,  10,  9,  9,  9,  10,  9,  10,  9,  10,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  10,  9,  10,  10,  10,  9,  10,  10,  10,  10,  10,  9,  9,  9,  9,  9,  9,  10,  9,  1,  1,  1,  10,  9,  9,  9,  9,  1,  1,  10,  10,  10,  10,  9,  9,  9,  9,  10,  10,  16,  16,  1,  9,  12,  12,  3,  8,  9,  8,  8,  8,  1,  10,  10,  10,  10,  9,  10,  9,  1,  1,  1,  9,  12,  12,  3,  3,  9,  10,  6,  8,  1,  16,  1,  9,  9,  9,  9,  1,  1,  11,  9,  12,  12,  12,  11,  1,  3,  7,  10,  8,  9,  11,  1,  9,  10,  9,  9,  1,  1,  10,  10,  12,  12,  19,  12,  12,  3,  7,  13,  10,  12,  9,  1,  10,  9,  9,  10,  16,  1,  1,  10,  12,  19,  19,  19,  9,  7,  7,  13,  10,  12,  9,  1,  9,  9,  9,  10,  16,  8,  5,  1,  12,  19,  19,  7,  7,  7,  13,  13,  10,  12,  8,  1,  10,  10,  10,  13,  16,  8,  5,  16,  7,  7,  7,  7,  13,  13,  13,  13,  9,  12,  9,  9,  10,  9,  9,  13,  13,  8,  5,  16,  16,  10,  7,  10,  11,  11,  11,  13,  10,  9,  9,  10,  9,  9,  10,  10,  10,  9,  5,  1,  1,  1,  1,  8,  1,  17,  11,  9,  8,  12,  9,  10,  10,  9,  10,  13,  13,  10,  5,  8,  5,  5,  8,  6,  17,  17,  9,  10,  8,  12,  9,  9,  9,  9,  10,  10,  13,  12,  17,  1,  5,  5,  8,  11,  11,  11,  10,  1,  1,  9,  9,  9,  9,  9,  9,  10,  12,  12,  11,  9,  5,  2,  3,  11,  11,  10,  10,  1,  9,  9,  9,  9,  10,  10,  9,  9,  9,  12,  19,  12,  9,  2,  3,  3,  1,  1,  1,  10,  9,  9,  9,  9,  9,  9,  9,  9,  9,  12,  12,  12,  12,  9,  9,  9,  9,  1,  1,  10,  10,  9,  10,  9,  9,  9,  9,  9,  9,  9,  12,  17,  10,  9,  9,  10,  10,  9,  10,  9,  9,  9,  10,  9,  10,  9,  9,  10,  9,  10,  10,  10,  9,  9,  9,  9,  9,  9,  9,  9,  10,  10,  9,  10,  10, },
{ 16,  9,  9,  9,  9,  9,  9,  9,  9,  10,  10,  9,  10,  10,  10,  9,  10,  9,  9,  9,  9,  9,  10,  10,  9,  10,  9,  10,  9,  9,  9,  9,  9,  9,  10,  9,  9,  9,  9,  9,  9,  9,  10,  9,  9,  9,  9,  10,  10,  10,  9,  9,  10,  10,  9,  9,  9,  9,  9,  10,  9,  9,  9,  9,  10,  9,  9,  10,  10,  10,  11,  11,  9,  8,  8,  8,  8,  9,  9,  9,  9,  9,  10,  9,  10,  9,  10,  10,  17,  11,  11,  3,  8,  8,  6,  6,  6,  10,  9,  10,  9,  9,  9,  9,  9,  10,  0,  10,  17,  11,  11,  3,  3,  8,  6,  6,  6,  0,  13,  18,  9,  9,  9,  9,  9,  8,  0,  10,  17,  11,  12,  3,  3,  1,  8,  6,  6,  6,  18,  11,  10,  9,  9,  10,  8,  6,  0,  13,  17,  11,  3,  3,  1,  16,  16,  8,  6,  6,  17,  13,  10,  9,  9,  9,  6,  6,  0,  13,  18,  11,  3,  5,  5,  16,  16,  8,  6,  6,  17,  13,  10,  9,  9,  9,  6,  6,  13,  13,  11,  17,  8,  5,  7,  7,  7,  9,  17,  6,  10,  13,  10,  9,  9,  9,  6,  6,  13,  13,  13,  10,  9,  7,  7,  7,  7,  3,  12,  6,  10,  13,  10,  9,  9,  11,  6,  6,  13,  13,  10,  16,  16,  16,  16,  16,  3,  3,  6,  6,  10,  13,  10,  10,  9,  11,  6,  6,  13,  0,  17,  18,  18,  16,  16,  1,  8,  6,  6,  17,  10,  13,  9,  9,  9,  9,  8,  6,  0,  0,  17,  16,  18,  1,  1,  8,  6,  6,  6,  9,  10,  10,  10,  9,  9,  9,  9,  8,  0,  0,  0,  16,  16,  9,  6,  6,  6,  6,  6,  10,  10,  10,  9,  9,  9,  9,  9,  8,  8,  6,  0,  17,  8,  12,  12,  6,  6,  6,  10,  10,  10,  10,  10,  9,  9,  9,  9,  9,  8,  6,  6,  6,  12,  12,  12,  8,  8,  10,  9,  9,  9,  9,  9,  10,  9,  10,  9,  9,  12,  6,  12,  9,  9,  9,  9,  8,  10,  10,  9,  9,  10,  9,  9,  9,  9,  9,  10,  9,  9,  8,  9,  9,  9,  9,  10,  10,  9,  9,  9,  9,  9,  10,  9,  9,  9,  9,  9,  9,  9,  10,  9,  9,  10,  10,  9,  9,  9,  9,  9,  9,  9,  10,  9, },
{ 16,  9,  9,  10,  9,  9,  9,  9,  10,  9,  10,  9,  9,  9,  10,  9,  9,  9,  9,  9,  9,  9,  9,  9,  10,  9,  9,  9,  9,  10,  9,  9,  10,  10,  9,  9,  9,  9,  9,  10,  9,  9,  10,  9,  9,  10,  10,  10,  10,  10,  9,  9,  10,  10,  10,  10,  10,  9,  9,  9,  10,  9,  9,  9,  9,  10,  10,  10,  10,  9,  9,  9,  9,  10,  17,  0,  10,  10,  10,  9,  9,  9,  9,  9,  10,  10,  10,  10,  13,  1,  1,  3,  3,  6,  6,  0,  0,  10,  10,  9,  10,  9,  10,  9,  10,  0,  0,  13,  13,  1,  3,  3,  3,  12,  6,  0,  17,  17,  10,  10,  9,  10,  9,  9,  10,  10,  10,  13,  13,  3,  3,  3,  19,  3,  19,  17,  17,  17,  10,  13,  10,  10,  9,  9,  10,  17,  10,  13,  11,  3,  3,  3,  11,  19,  19,  19,  12,  0,  10,  10,  10,  9,  9,  9,  17,  17,  17,  13,  12,  3,  3,  1,  17,  19,  19,  19,  19,  0,  0,  10,  10,  9,  9,  10,  17,  17,  17,  12,  12,  13,  16,  16,  16,  16,  9,  12,  18,  0,  0,  10,  10,  9,  9,  18,  17,  17,  11,  10,  0,  16,  16,  16,  16,  16,  7,  18,  11,  0,  0,  10,  9,  10,  9,  18,  12,  17,  1,  0,  0,  16,  16,  16,  1,  13,  10,  18,  18,  0,  10,  10,  10,  9,  9,  18,  11,  17,  17,  0,  0,  7,  3,  1,  1,  10,  18,  18,  17,  10,  10,  9,  9,  9,  9,  18,  18,  17,  0,  0,  0,  10,  1,  9,  17,  12,  18,  18,  11,  10,  9,  9,  9,  9,  9,  18,  9,  6,  0,  0,  10,  9,  11,  18,  18,  18,  18,  17,  9,  9,  1,  9,  10,  9,  9,  9,  9,  0,  0,  0,  10,  11,  3,  19,  19,  12,  17,  17,  10,  9,  1,  9,  9,  9,  9,  10,  9,  8,  0,  0,  10,  11,  19,  19,  19,  17,  17,  10,  10,  9,  9,  9,  9,  9,  9,  9,  9,  10,  10,  0,  10,  9,  9,  9,  9,  17,  10,  9,  9,  9,  10,  9,  9,  9,  9,  9,  10,  9,  9,  10,  10,  9,  9,  9,  9,  10,  9,  9,  10,  9,  10,  9,  9,  9,  9,  10,  10,  9,  9,  10,  9,  9,  9,  10,  9,  9,  9,  9,  10,  9,  10,  9,  9, },
{ 13,  9,  9,  10,  9,  9,  10,  9,  9,  9,  9,  9,  10,  9,  9,  10,  9,  10,  9,  9,  10,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  10,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  10,  9,  9,  10,  10,  9,  9,  10,  9,  9,  9,  9,  9,  10,  9,  9,  9,  9,  9,  9,  9,  9,  10,  9,  10,  9,  9,  9,  9,  9,  9,  9,  17,  17,  17,  10,  9,  9,  9,  9,  9,  9,  9,  10,  11,  11,  9,  9,  9,  18,  18,  18,  11,  17,  17,  17,  9,  9,  9,  9,  9,  9,  10,  10,  11,  11,  3,  3,  3,  11,  18,  18,  18,  11,  17,  10,  9,  9,  9,  9,  9,  10,  9,  17,  11,  11,  3,  3,  3,  12,  18,  13,  13,  18,  17,  10,  9,  9,  9,  10,  10,  10,  17,  17,  11,  11,  3,  3,  3,  9,  16,  13,  13,  13,  17,  18,  9,  9,  9,  9,  9,  10,  17,  17,  17,  11,  3,  3,  3,  10,  0,  0,  13,  13,  17,  11,  9,  9,  9,  9,  9,  17,  17,  17,  17,  10,  9,  8,  8,  0,  0,  0,  13,  13,  17,  18,  18,  9,  9,  10,  10,  17,  17,  17,  17,  10,  0,  0,  0,  0,  0,  5,  1,  17,  17,  11,  11,  9,  9,  9,  10,  17,  17,  17,  11,  1,  1,  8,  0,  1,  1,  3,  11,  17,  17,  9,  9,  9,  9,  9,  10,  10,  17,  17,  11,  1,  1,  8,  5,  16,  1,  11,  18,  17,  17,  9,  9,  9,  9,  9,  9,  10,  17,  17,  9,  11,  18,  18,  9,  3,  11,  18,  17,  17,  17,  9,  9,  9,  9,  10,  10,  10,  10,  10,  1,  11,  18,  18,  12,  12,  9,  18,  17,  17,  11,  9,  9,  9,  9,  9,  9,  10,  9,  9,  3,  11,  18,  18,  18,  12,  17,  17,  17,  17,  9,  9,  9,  9,  9,  9,  9,  9,  9,  3,  1,  11,  18,  18,  18,  18,  17,  17,  17,  11,  9,  9,  9,  9,  9,  9,  9,  10,  9,  1,  1,  3,  9,  10,  10,  10,  10,  10,  10,  10,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  1,  9,  9,  9,  10,  10,  10,  9,  9,  9,  9,  10,  9,  9,  9,  9,  9,  10,  9,  9,  10,  9,  10,  10,  10,  10,  9,  9,  9,  9,  9,  9,  9,  9, },
};

int8_t cd_book [CDROW_N][CDCOL_N] =
{{ -15,  -2,  16,  14,  1 },
{ 10,  -8,  -1,  8,  7 },
{ 26,  28,  17,  0,  -7 },
{ 20,  11,  -10,  2,  -2 },
{ 48,  4,  -14,  32,  11 },
{ 18,  -3,  20,  12,  -7 },
{ -10,  7,  2,  23,  -12 },
{ 7,  3,  21,  -22,  2 },
{ 5,  6,  3,  14,  -3 },
{ 2,  1,  0,  1,  0 },
{ -2,  -1,  2,  1,  2 },
{ 3,  0,  -14,  2,  3 },
{ -5,  15,  -10,  3,  -9 },
{ -9,  1,  -1,  -5,  20 },
{ -25,  -25,  -25,  -25,  -25 },
{ -30,  -30,  -30,  -30,  -30 },
{ 9,  -20,  9,  -4,  9 },
{ -12,  -8,  -9,  4,  -1 },
{ -6,  1,  -19,  -12,  6 },
{ 4,  9,  -21,  -11,  -20 }
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