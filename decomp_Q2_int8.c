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
{{ 98,  -29,  13,  -6,  32 },
{ 117,  -108,  58,  59,  -93 },
{ 14,  2,  -47,  111,  -55 },
{ 74,  -100,  97,  -19,  21 },
{ 41,  -6,  57,  -55,  79 },
{ 19,  -56,  54,  61,  -20 },
{ -20,  106,  -28,  -30,  -41 },
{ -72,  4,  2,  14,  14 },
{ 2,  -53,  -31,  -27,  -5 },
{ -22,  34,  -41,  -52,  38 },
{ 22,  -24,  -64,  -80,  -48 },
{ -55,  -55,  -81,  14,  -61 },
{ -83,  27,  -65,  -6,  -45 },
{ -45,  33,  15,  14,  -58 },
{ -58,  -59,  -25,  1,  103 },
{ 23,  -27,  34,  -69,  -67 }
};

int8_t addr_book[ADDROW_N][ADDCOL_N]= 
{{ 11,  13,  0,  1,  8,  10,  13,  3,  15,  13,  12,  2,  4,  6,  9,  10,  11,  8,  0,  7,  8,  14,  8,  11,  4,  12 },
{ 8,  15,  13,  11,  6,  8,  7,  3,  5,  9,  6,  10,  10,  15,  14,  2,  2,  9,  7,  0,  13,  12,  11,  12,  14,  4 }
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