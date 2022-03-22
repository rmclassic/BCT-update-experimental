#include "bct_t30.h"
#include <stdio.h> //TO BE DELETED
#define NVBOOT_BOOTDATA_VERSION(a, b) ((((a)&0xffff) << 16) | ((b)&0xffff))

#define BOOTDATA_VERSION_T30		NVBOOT_BOOTDATA_VERSION(0x3, 0x1)

int if_bct_is_t30_get_soc_config(void *bct_raw, nvboot_config_table ** bct)
{
	*bct = (nvboot_config_table *) bct_raw;
	printf("%d\n", (*bct)->boot_data_version);

	if ((*bct)->boot_data_version == BOOTDATA_VERSION_T30)
	{
		return 1;
	}
	return 0;
}

void t30_test(uint8_t* bct_raw)
{
	nvboot_config_table * bct = 0;
	if (1 == if_bct_is_t30_get_soc_config(bct_raw, &bct))
	{
		printf("bl[0] address is: 0x%x\n", sizeof(nvboot_config_table));
		printf("base address is 0x%x\n", &bct->boot_data_version);
		printf("bl[0].entry_point: 0x%x\n", bct->bootloader[0].entry_point);
		printf("changing to 0x%x\n", 0x20588);

		bct->bootloader[0].entry_point = 0x20588;
	}


}
