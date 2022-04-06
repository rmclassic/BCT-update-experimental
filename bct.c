#include "crypto.h"
#include "bct.h"
#include "uboot_aes.h"
#include <string.h>
#include <stdio.h>
#define BCT_HASH		0x10
#define EBT_ALIGNMENT		0x10
static u8 sbk[AES128_KEY_LENGTH] = { 0xf1, 0x42, 0x4b, 0xc7, 0x00, 0x00, 0x00, 0xc7, 0xbd, 0xf6, 0x34, 0x92, 0x00, 0x50, 0x00, 0x00 };
typedef unsigned char u8;
typedef unsigned int u32;
/*
 * \param bct		boot config table start in RAM
 * \param ect		bootloader start in RAM
 * \param ebt_size	bootloader file size in bytes
 */
int bct_patch(u8 *bct, u8 *ebt, u32 ebt_size)
{
	u8 ebt_hash[AES128_KEY_LENGTH] = { 0 };
	nvboot_config_table *bct_tbl = 0;
	u8 *bct_hash = bct;
	int ret;

	//bct += BCT_HASH;

	ret = decrypt_data_block(bct, BCT_LENGTH, sbk);
	if (ret)
		return 1;

	bct_tbl = (nvboot_config_table *)bct;

	//ebt_size = ((ebt_size / EBT_ALIGNMENT) + 1) * EBT_ALIGNMENT;

	ret = encrypt_data_block(ebt, ebt_size, sbk);
	if (ret)
		return 1;

	ret = sign_enc_data_block(ebt, ebt_size, ebt_hash, sbk);
	if (ret)
		return 1;

	memcpy((u8 *)&bct_tbl->bootloader[0].crypto_hash,
		ebt_hash, AES128_KEY_LENGTH);
	bct_tbl->bootloader[0].entry_point = 0x85858585;
	bct_tbl->bootloader[0].load_addr = 0x85858585;
	bct_tbl->bootloader[0].length = 0x8585;

	ret = sign_enc_data_block(bct, BCT_LENGTH, bct_hash, sbk);
	if (ret)
		return 1;

	ret = encrypt_data_block(bct, BCT_LENGTH, sbk);
	if (ret)
		return 1;

	return 0;
}
