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
#ifndef	___PMU_TABLE_H_______
#define	___PMU_TABLE_H_______

typedef struct ps_setting {
	u8			reg_idx;
	uchar			ps_name[16];
	power_supply_component	module;

	u32			voltage;
	power_supply_mode	default_mode;
	power_supply_mode	cur_mode;
} ps_setting_t;

/* array order is same as struct div_name */
static ps_setting_t ps_setting_default[] = {
	{D1REGC1,     "VDD_DTV_1V8",     PPS_TUNER,   1800, PS_OFF, PS_OFF, },
	{D2REGC1,     "VBBIO_3V0",       PPS_COMMON,  3000, PS_ON,  PS_ON,  },
	{D3REGC1,     "VBBA_2V5",        PPS_COMMON,  2500, PS_ON,  PS_ON,  },
	{HCREGC1,     "VCAMERA_3V0",     PPS_CAMERA,  3000, PS_OFF, PS_OFF, },
	{D4REGC1,     "VCAMERA_1V8",     PPS_CAMERA,  1800, PS_OFF, PS_OFF, },
	{D5REGC1,     "VWFVDD_1V8",      PPS_WIFI,    1800, PS_OFF, PS_OFF, },
	{D6REGC1,     "VSD_3V0",         PPS_SD,      3000, PS_ON,  PS_ON,  },
	{D7REGC1,     "VUSB_VDD3V3",     PPS_USB,     3300, PS_OFF, PS_OFF, },
	{D8REGC1,     "VCMMB_CA_3V0",    PPS_CMMB,    3000, PS_OFF, PS_OFF, },
	{RF3REGC1,    "VETH_1V8",        PPS_ETH,     1800, PS_OFF, PS_OFF, },
	{RF4REGC1,    "VGPS_3V0",        PPS_GPS,     3000, PS_OFF, PS_OFF, },
	{IOREGC1,     "IOVDD_3V0",       PPS_COMMON,  3000, PS_ON,  PS_ON,  },
	{USBREGC1,    "VDDLCD_3V3",      PPS_LCD,     3300, PS_ON,  PS_ON,  },
	{LCREGC1,     "VDD_CRYSTAL_1V8", PPS_COMMON,  1800, PS_ON,  PS_ON,  },
	{USIMREGC1,   "VWFVDD_3V0",      PPS_SDIO,    3000, PS_ON,  PS_ON,  },
	{DCD1C1,      "VDD1V3",          PPS_COMMON,  1300, PS_ON,  PS_ON,  },
	{DCD2C1,      "VMEM_1V8",        PPS_COMMON,  1800, PS_ON,  PS_ON,  },
};

#define	PS_SETTING_COUNT		ARRAY_SIZE(ps_setting_default)

#endif	/*___PMU_TABLE_H_______*/

