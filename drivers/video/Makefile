#
# (C) Copyright 2000-2007
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

LIB	:= $(obj)libvideo.a

COBJS-$(CONFIG_ATI_RADEON_FB) += ati_radeon_fb.o
COBJS-$(CONFIG_ATMEL_LCD) += atmel_lcdfb.o
COBJS-$(CONFIG_CFB_CONSOLE) += cfb_console.o
COBJS-$(CONFIG_S6E63D6) += s6e63d6.o
COBJS-$(CONFIG_VIDEO_CT69000) += ct69000.o
COBJS-$(CONFIG_VIDEO_MB862xx) += mb862xx.o
COBJS-$(CONFIG_VIDEO_MX3) += mx3fb.o
COBJS-$(CONFIG_VIDEO_SED13806) += sed13806.o
COBJS-$(CONFIG_SED156X) += sed156x.o
COBJS-$(CONFIG_VIDEO_SM501) += sm501.o
COBJS-$(CONFIG_VIDEO_SMI_LYNXEM) += smiLynxEM.o
COBJS-$(CONFIG_VIDEO_VCXK) += bus_vcxk.o
COBJS-$(CONFIG_ATXX_LCD) += atxxfb.o

COBJS-y +=tm320.o r61581.o rm68040.o rm68041.o inno7dd.o \
	  inno8d2.o lms350df04.o hsd070ldw1.o sharp_ls035.o ili9486.o Lcd_table.o ssd2805c.o nt35510.o


COBJS-y += videomodes.o

COBJS-$(CONFIG_LOGO_AUGUSTA) += logo_augusta.o
COBJS-$(CONFIG_LOGO_DIANYI) += logo_dianyi.o
COBJS-$(CONFIG_LOGO_DREAM) += logo_dream.o
COBJS-$(CONFIG_LOGO_DONGXING) += logo_dongxing.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
