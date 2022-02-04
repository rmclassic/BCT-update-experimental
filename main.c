#include "bct.h"

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
  std::ifstream f("../BCT_enc.bin", std::ios::ate | std::ios::binary);
  int filesize = f.tellg();
  f.seekg(0);

  char* file = new char[filesize];
  f.read(file, filesize);
  f.close();

  std::cout << filesize;

  u8* bct_dec = new u8[filesize];

  int result = decrypt_bct(file, filesize, (u8*)key, (u8*)bct_dec);
  if (result != BCT_ERR_SUCCESS)
  {
    std::cout << "error\n";
    return 0;
  }

  std::ofstream ff("BCT_dec.bin", std::ios::binary);
  ff.write((char*)bct_dec, filesize);
  ff.close();
  return 0;
}
