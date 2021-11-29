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

int16_t output_vec[THETAROW_N][THETACOL_N];

int16_t cd_book [CDROW_N][CDCOL_N] ={
{ -11960,  -11286,  -5867,  -8355,  9757 },
{ 6184,  -16062,  -15396,  -10067,  -8380 },
{ -23392,  -12410,  -13339,  17067,  25893 },
{ 3674,  -6395,  4565,  -19172,  -16743 },
{ -1828,  -20381,  -18846,  -2613,  -22583 },
{ 18924,  -8436,  11982,  -7276,  12788 },
{ 967,  -6191,  -4788,  -6841,  9390 },
{ -2613,  3533,  5435,  -12322,  16204 },
{ -8819,  8396,  -14484,  16872,  -10404 },
{ -14991,  14007,  4894,  2670,  -13570 },
{ -11597,  5141,  -4282,  5468,  5673 },
{ -22273,  -9575,  -21345,  4093,  -15504 },
{ 3054,  -1259,  21,  5478,  -10828 },
{ -8192,  16615,  -14878,  -16475,  -8292 },
{ 17292,  -18250,  6794,  19908,  -15606 },
{ 28420,  32553,  24074,  -2632,  306 }
};

int16_t addr_book[ADDROW_N][ADDCOL_N]= 
{{ 1,  9,  5,  14,  1,  3,  9,  5,  3,  9,  13,  8,  5,  13,  7,  13,  11,  1,  5,  10,  0,  2,  1,  11,  5,  11 },
{ 0,  3,  12,  11,  9,  6,  10,  15,  14,  10,  13,  1,  1,  3,  0,  8,  14,  13,  0,  5,  9,  8,  4,  8,  0,  7 }
};
void decompression_func(int16_t addr_book[ADDROW_N][ADDCOL_N])
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