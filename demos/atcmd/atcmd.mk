
NAME := ATCMD

include config/$(KCONFIG_CONFIG)

$(NAME)_SRCS = \
	example_atcmd_async.c \



$(NAME)_INCS = \
	. \
	../system/platform \
	../system/debug \
	../system/dev \
	../system/hal \
	../system/os \
	../system/ble \
	../system/startup \
	../system/at \


#$(NAME)_COMPONENTS = 

#$(NAME)_COMPONENTS += 