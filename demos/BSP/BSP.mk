
NAME := BSP

include config/$(KCONFIG_CONFIG)

$(NAME)_SRCS = \
	example_gpio.c \
	example_adc.c \
	example_extint.c \
	example_uart.c \
	example_timer.c \
	example_rtc.c \
	example_iic.c \
	example_spi.c \
	example_lpm.c \
	example_power.c \
	example_pwm.c \
	example_wdt.c
	

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


