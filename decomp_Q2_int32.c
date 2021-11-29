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

int32_t output_vec[THETAROW_N][THETACOL_N];

int32_t cd_book [CDROW_N][CDCOL_N] =
{{ 117821194,  15336290,  -407616107,  932562473,  -471377087 },
{ -462812133,  677684815,  352427096,  6243802,  -408710236 },
{ 983640099,  -906625560,  487706038,  502682903,  -784177796 },
{ 931260908,  -1080795554,  788845434,  -86267337,  10003209 },
{ -36272203,  1099303660,  -501348495,  -300133679,  -553737514 },
{ 17169175,  -48753206,  44389163,  -740364192,  -450170573 },
{ -770320831,  -7431730,  -85179320,  -264784032,  293398508 },
{ 239214290,  -312189393,  126055666,  30700510,  -392444249 },
{ -646273007,  -190643876,  -371152682,  62183327,  -747038039 },
{ 213181040,  -501938335,  -720096972,  -301561604,  -300431636 },
{ 1191632922,  -1911794,  -844544155,  -180589957,  -471850216 },
{ -229330434,  -505731927,  -876747763,  158881638,  596428795 },
{ -442683614,  262222814,  -237820574,  170752980,  -19020319 },
{ -269866838,  176808788,  107082143,  138447840,  -237859377 },
{ 442430577,  -109426356,  401220536,  -443580052,  515799773 },
{ -117812647,  -503721243,  -190080137,  -278161034,  169559624 }
};

int32_t addr_book[ADDROW_N][ADDCOL_N]= 
{{ 9,  12,  6,  2,  15,  5,  8,  11,  5,  13,  10,  0,  14,  4,  6,  5,  8,  7,  14,  12,  15,  11,  9,  10,  14,  8 },
{ 15,  7,  7,  8,  1,  15,  12,  3,  7,  12,  4,  9,  9,  5,  15,  0,  0,  6,  6,  6,  1,  12,  4,  12,  8,  14 }
};

void decompression_func(int32_t addr_book[ADDROW_N][ADDCOL_N])
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