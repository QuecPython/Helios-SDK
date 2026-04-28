KEEP_FILES = autoconf.h cleanup.mk config.in config.mk config.mk.old include menuconfig.sh
CLEANUP_FILES = $(filter-out $(KEEP_FILES),$(shell ls 2> /dev/null))
all:
	@rm -rf $(KCONFIG_INCLUDE_DIR)/*
ifneq ($(CLEANUP_FILES),)
	@mv -f $(CLEANUP_FILES) $(KCONFIG_INCLUDE_DIR)
endif