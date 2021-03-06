/*------------------------------------------------------------------------------
* (c) Copyright, Augusta Technology, Inc., 2006-present.
* (c) Copyright, Augusta Technology USA, Inc., 2006-present.
*  
* This software, document, web pages, or material (the "Work") is copyrighted 
* by its respective copyright owners.  The Work may be confidential and 
* proprietary.  The Work may be further protected by one or more patents and 
* be protected as a part of a trade secret package.
*   
* No part of the Work may be copied, photocopied, reproduced, translated, or 
* reduced to any electronic medium or machine-readable form, in whole or in 
* part, without prior written consent of the copyright owner. Any other 
* reproduction in any form without the permission of the copyright owner is 
* prohibited.
*   
* All Work are protected by the copyright laws of all relevant jurisdictions, 
* including protection under the United States copyright laws, and may not be 
* reproduced, distributed, transmitted, displayed, published, or broadcast 
* without the prior written permission of the copyright owner.
*
------------------------------------------------------------------------------*/
#include <command.h>
#include <common.h>
#include <asm/string.h>
#include <linux/list.h>
#include <asm/arch-atxx/clock.h>
#include <asm/arch-atxx/cache.h>
#include <asm/arch-atxx/memory_map.h>
#include <i2c.h>

static int cache_test(int argc, char *argv[])
{
	char *action;
	int ret = -1;

	if (argc < 3){
		return ret;
	}
	action = argv[2];
	if (!strcmp(action, "on")) {
		printf("cache and mmu on\n");
		mmu_cache_on(memory_map);
		ret = 0;
	} else if (!strcmp(action, "off")){
		printf("cache and mmu off\n");
		mmu_cache_off();
		ret = 0;
	}
	return ret;
}

#define DISP_LINE_LEN	16

int do_i2c_rd ( cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	u_char	chip;
	uint	addr, alen, length;
	int	j, nbytes, linebytes;


	if (argc < 3) {
		cmd_usage(cmdtp);
		return 1;
	}

	/*
	 * I2C chip address
	 */
	chip = simple_strtoul(argv[1], NULL, 16);

	/*
	 * I2C data address within the chip.  This can be 1 or
	 * 2 bytes long.  Some day it might be 3 bytes long :-).
	 */
	addr = simple_strtoul(argv[2], NULL, 16);
	alen = 1;
	/*
	 * If another parameter, it is the length to display.
	 * Length is the number of objects, not number of bytes.
	 */
	if (argc > 3)
		length = simple_strtoul(argv[3], NULL, 16);
	else
		length = DISP_LINE_LEN;

	/*
	 * Print the lines.
	 *
	 * We buffer all read data, so we can make sure data is read only
	 * once.
	 */
	nbytes = length;
	do {
		unsigned char	linebuf[DISP_LINE_LEN];
		unsigned char	*cp;

		linebytes = (nbytes > DISP_LINE_LEN) ? DISP_LINE_LEN : nbytes;

		if (i2c_read(chip, addr, alen, linebuf, linebytes) != 0)
			puts ("Error reading the chip.\n");
		else {
			printf("%04x:", addr);
			cp = linebuf;
			for (j=0; j<linebytes; j++) {
				printf(" %02x", *cp++);
				addr++;
			}
			puts ("    ");
			cp = linebuf;
			for (j=0; j<linebytes; j++) {
				if ((*cp < 0x20) || (*cp > 0x7e))
					puts (".");
				else
					printf("%c", *cp);
				cp++;
			}
			putc ('\n');
		}
		nbytes -= linebytes;
	} while (nbytes > 0);

}


/* Write (fill) memory
 *
 * Syntax:
 *	stest i2c write {i2c_chip} {addr} {data} [{count}]
 */
int do_i2c_wt ( cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	uchar	chip;
	ulong	addr;
	uint	alen;
	uchar	byte;
	int	count;
	int	j;

	if ((argc < 4) || (argc > 5)) {
		cmd_usage(cmdtp);
		return 1;
	}

	/*
	 * Chip is always specified.
	 */
	chip = simple_strtoul(argv[1], NULL, 16);

	/*
	 * Address is always specified.
	 */
	addr = simple_strtoul(argv[2], NULL, 16);
	alen = 1;

	/*
	 * Value to write is always specified.
	 */
	byte = simple_strtoul(argv[3], NULL, 16);

	/*
	 * Optional count
	 */
	if (argc == 5)
		count = simple_strtoul(argv[4], NULL, 16);
	else
		count = 1;

	while (count-- > 0) {
		if (i2c_write(chip, addr++, 1, &byte, 1) != 0)
			puts ("Error writing the chip.\n");
		/*
		 * Wait for the write to complete.  The write can take
		 * up to 10mSec (we allow a little more time).
		 */
	}

	return (0);
}

/*
 * Syntax:
 *	i2c probe {addr}{.0, .1, .2}
 */
int do_i2c_probe (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int j;

	puts ("Valid chip addresses:");
	for (j = 0; j < 128; j++) {
		if (i2c_probe(j) == 0)
			printf(" %02X", j);
	}
	putc ('\n');
	return 0;
}
/*
 * Syntax:
 *	i2c reset
 */
int do_i2c_reset (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	i2c_init(1,0x70);
	puts ("reset i2c:");
	putc ('\n');

	return 0;
}

extern void pmu_power_show();
int do_i2c(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	/* Strip off leading 'i2c' command argument */
	argc--;
	argv++;
	
	if (!strncmp(argv[0], "read", 4))
		return do_i2c_rd(cmdtp, flag, argc, argv);
	if (!strncmp(argv[0], "write", 5))
		return do_i2c_wt(cmdtp, flag, argc, argv);
	if (!strncmp(argv[0], "reset", 5)) {
		i2c_init(1, 0x70);
		return 0;
	}else if (!strncmp(argv[0], "showreg", 7)) {
		pmu_power_show();
		return 0;
	}
	cmd_usage(cmdtp);
	return 0;
}


int atxx_do_gpio(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	int gpio;
	int value;

	
	argc--;
	argv++;

	if (argc < 2) {
		cmd_usage(cmdtp);
		return -1;
	}

	gpio = simple_strtoul(argv[0], NULL, 10);
	if (atxx_request_gpio(gpio) < 0) {
		printf("Wrong gpio request!\n");
		return -1;
	}
	
	if (!strncmp(argv[1], "input", 5)) {
		atxx_set_gpio_direction(gpio, 1);
		value = atxx_gpio_get(gpio);
		printf("gpio %d: %d\n", gpio, value);

		return 0;
	}
	if (!strncmp(argv[1], "output", 6)) {
		if (argc < 3) {
			cmd_usage(cmdtp);
			return -1;
		}
		
		value = simple_strtoul(argv[2], NULL, 10);
		if (value)
			value = 1;
	
		atxx_set_gpio_direction(gpio, 0);
		atxx_gpio_set(gpio, value);
		
		return 0;
	}

	cmd_usage(cmdtp);
	return 0;
}


int set_clock (cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	char *name;
	ulong rate;
	int ret;

	if(argc < 3)
		return -1;

	name = argv[1];
	rate = simple_strtoul(argv[2], NULL, 0);
	ret = clk_set_by_name(name, rate * MHZ);
	if(ret){
		printf("set clock rate failing\n");
	}

	return 0;
}

int enable_clock (cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	char *name = NULL;
	unsigned int enable_flag = 0;
	int ret;

	if(argc < 3)
		return -1;

	name = argv[1];
	enable_flag = simple_strtoul(argv[2], NULL, 0);
	ret = clk_enable_by_name(name, enable_flag);
	if(ret){
		if(enable_flag){
			printf("enable clock failing\n");
		}else{
			printf("disable clock failing\n");
		}
	}

	return 0;
}

int parent_clock (cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	char *name = NULL, *parent_name = NULL;
	int ret;

	if(argc < 3)
		return -1;

	name = argv[1];
	parent_name = argv[2];
	ret = clk_parent_by_name(name, parent_name);
	if(ret){
		printf("set clock parent failing\n");
	}

	return 0;
}

int do_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int ret = -1;
	char *subcmd;

	if (argc < 2) {
		goto done;
	}
	subcmd = argv[1];

	/* stest cache on/off */
	if (!strcmp(subcmd, "cache")) {
		ret = cache_test(argc, argv);

	/* stest clkd */
	}else if (!strcmp(subcmd, "clkd")) {
			dump_clock();
			ret = 0;
	}else if (!strcmp (subcmd, "clks")) {
			argc--;
			argv++;
			ret = set_clock (cmdtp, flag, argc, argv);
	}else if (!strcmp (subcmd, "clke")) {
			argc--;
			argv++;
			ret = enable_clock (cmdtp, flag, argc, argv);
	}else if (!strcmp (subcmd, "clkp")) {
			argc--;
			argv++;
			ret = parent_clock (cmdtp, flag, argc, argv);
	}else if (!strcmp(subcmd, "i2c")) {
			argc--;
			argv++;
			do_i2c(cmdtp, flag, argc, argv);
			ret = 0;
	}else if (!strcmp(subcmd, "gpio")) {
			argc--;
			argv++;
			atxx_do_gpio(cmdtp, flag, argc, argv);
			ret = 0;
	}
done:
	if (ret < 0)		
		cmd_usage(cmdtp);
	return 1;
}

U_BOOT_CMD(
	stest,   7,   1,	do_test,
	"self test for: cache, clkd, i2c, gpio",
	"stest cache on|off\n"
	"stest clkd - clock dump\n"
	"stest clks [name] [rate] - clock set\n"
	"stest clke [name] [enable] - clock enable/disable\n"
	"stest clkp [name] [parent name] - set parent node of current clock \n"
	"stest i2c read chip address [# of objects] - read from I2C device\n"
	"stest i2c write chip address value [count] - write to I2C device (fill)\n"
	"stest i2c reset - re-init the I2C Controller\n"
	"stest i2c showreg - dump PMU register\n"
	"stest gpio number input\n"
	"stest gpio number output value\n"
);

