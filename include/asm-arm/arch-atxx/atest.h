#ifndef __ATESTPARAM_H
#define __ATESTPARAM_H

typedef enum {
	READ_ID = 0,
	READ_WRITE,
} i2c_test_type;

typedef struct atest_i2c_setting {
	uchar		name[16];
	u8			chip_addr;
	i2c_test_type			test_type;
	u32			id_addr;
	u8			id_addr_len;
	u32			id_data;
	u8			id_data_len;
} atest_i2c_setting_t;


#if	defined(CONFIG_BOARD_CAYMAN20)
#include "atest_cayman20.h"
#elif	defined(CONFIG_BOARD_MIRACLE)
#include "atest_miracle.h"
#elif	defined(CONFIG_BOARD_G20)
#include "atest_g20.h"
#else
#error   "atest_<board>.h is missing!"
#endif

#define	ATEST_I2C_COUNT		ARRAY_SIZE(atest_i2c_item)


#endif /* __ATESTPARAM_H */