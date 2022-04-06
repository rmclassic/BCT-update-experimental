#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"
#include "bct.h"

u8 key[16] = { 0x28, 0xa5 , 0xd1, 0x26 ,
               0xad, 0xf4 , 0x21, 0xe6 ,
               0xa3, 0x9b , 0xfc, 0x8f ,
               0x7f, 0xf3 , 0x23, 0x08 };

int ReadFile(char* filename, u8** data)
{
  FILE* f = fopen(filename, "rb");
  fseek(f, 0, SEEK_END);
  int filesize = ftell(f);

  char* file = (char*)malloc(filesize);
  fseek(f, 0, SEEK_SET);
  int hmuch = fread(file, 1, filesize, f);
  fclose(f);
  printf("read %d bytes\n", hmuch);
  *data = file;
  return hmuch;
}

void WriteFile(char* filename, u8* data, int filesize)
{
  FILE* f = fopen(filename, "wb");

  fseek(f, 0, SEEK_SET);
  int hmuch = fwrite(data, 1, filesize, f);
  fclose(f);
  printf("wrote %d bytes\n", hmuch);
}

int main()
{
  u8* bct = 0;
  u8* ebt = 0;

  int bct_size = ReadFile("orig_bct.bin", &bct);
  int ebt_size = ReadFile("mod_bl_dec", &ebt);
  bct_patch(bct, ebt, ebt_size);

  nvboot_config_table * bct_tbl = (nvboot_config_table *)bct;


  WriteFile("bct_test.bin", bct, bct_size);

  return 0;
}
