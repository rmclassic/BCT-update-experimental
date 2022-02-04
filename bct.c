#include "bct.h"


int decrypt_bct(void *bct_image, u32 bct_size, u8 *key, u8* bct_dec)
{
  u8 expanded_key[AES128_EXPAND_KEY_LENGTH];

  if (bct_size % AES_BLOCK_LENGTH != 0)
    return BCT_ERR_INVALID_SIZE;

  u8 iv[16] = { 0 };

  aes_expand_key(key, BCT_KEY_SIZE, expanded_key);
  aes_cbc_decrypt_blocks(BCT_KEY_SIZE, expanded_key, iv, (u8*)bct_image, bct_dec, bct_size / AES_BLOCK_LENGTH);
  return BCT_ERR_SUCCESS;
}
