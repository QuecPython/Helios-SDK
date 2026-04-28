
NAME := NETWORK

include config/$(KCONFIG_CONFIG)

$(NAME)_SRCS = \
	example_cellocator.c \
	example_datacall.c \
	example_nw.c \
	example_sim.c \
	example_sms.c \
	example_voicecall.c \
	example_wifiscan.c \
	

$(NAME)_INCS = \
	. \
	../system/platform \
	../system/debug \
	../system/dev \
	../system/fs \
	../system/hal \
	../system/lwip \
	../system/network \
	../system/os \
	../system/ble \
	../system/startup \


#$(NAME)_COMPONENTS = 

#$(NAME)_COMPONENTS += 


