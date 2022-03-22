#include "bct.h"
#include <stdio.h>
#include <stdlib.h>
//#include "bct_t20.h"
#include "bct_t30.h"
#include "crypto.h"

u8 key[16] = { 0x28, 0xa5 , 0xd1, 0x26 ,
               0xad, 0xf4 , 0x21, 0xe6 ,
               0xa3, 0x9b , 0xfc, 0x8f ,
               0x7f, 0xf3 , 0x23, 0x08 };

int main()
{
  FILE* f = fopen("../BCT_dec.bin", "rb");
  fseek(f, 0, SEEK_END);
  int filesize = ftell(f);

  char* file = (char*)malloc(filesize);
  fseek(f, 0, SEEK_SET);
  int hmuch = fread(file, 1, filesize, f);
  fclose(f);
  printf("%d\n", hmuch);


  // ENCRYPTION
  encrypt_data_block(file, filesize, key);

  f = fopen("../BCT_TEST.bin", "w+");
  fwrite(file, 1, filesize, f);
  //


  return 0;
}

//
//
// int main()
// {
//   FILE* f = fopen("../BCT_dec.bin", "rb");
//   fseek(f, 0, SEEK_END);
//   int filesize = ftell(f);
//
//   char* file = (char*)malloc(filesize);
//   fseek(f, 0, SEEK_SET);
//   int hmuch = fread(file, 1, filesize, f);
//   fclose(f);
//   printf("read %d bytes\n", hmuch);
//   u8* bct_dec = (u8*)malloc(AES128_KEY_LENGTH);
//
//   for (int i = 0; i < AES128_KEY_LENGTH; i++)
//     bct_dec[i] = 0;
//
//
//   int result = sign_data_block(file, filesize, (u8*)bct_dec, (u8*)key);
//   printf("result %d\n", result);
//
//   for (int i = 0; i < AES128_KEY_LENGTH; i++)
//   {
//     printf("%x", bct_dec[i]);
//   }
//
//   return 0;
// }
