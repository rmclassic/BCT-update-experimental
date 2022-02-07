#include "bct.h"
#include <stdio.h>
#include <stdlib.h>
#include "bct_t20.h"

u8 key[16] =             { 0x28, 0xa5 , 0xd1, 0x26 ,
               0xad, 0xf4 , 0x21, 0xe6 ,
               0xa3, 0x9b , 0xfc, 0x8f ,
               0x7f, 0xf3 , 0x23, 0x08 };

// u8 key[16] = {
//                 0x08, 0x23, 0xf3, 0x7f,
//                 0x8f, 0xfc, 0x9b, 0xa3,
//                 0xe6, 0x21, 0xf4, 0xad,
//                 0x26, 0xd1, 0xa5, 0x28 };

int main()
{
  FILE* f = fopen("../BCT_enc.bin", "rb");
  fseek(f, 0, SEEK_END);
  int filesize = ftell(f);

  char* file = (char*)malloc(filesize);
  fseek(f, 0, SEEK_SET);
  int hmuch = fread(file, filesize, filesize, f);
  fclose(f);
  printf("%d\n", hmuch);
  u8* bct_dec = (u8*)malloc(filesize);

  int result = decrypt_bct(file, filesize, (u8*)key, (u8*)bct_dec);
  if (result != BCT_ERR_SUCCESS)
  {
    printf("error\n");
    return 0;
  }

  t20_test(bct_dec);

  return 0;
}
