NAME := MICROPYTHON

include config/$(KCONFIG_CONFIG)

$(NAME)_ARCHIVES = ports/quectel/$(BUILD)/firmware.a


$(NAME)_PRIVATE_SCRIPT = private.mk

$(NAME)_PRIVATE_SCRIPT_TARGETS = construct clean



