ifeq ($(wildcard configure),) 
default:
	@echo -n "Bootstrapping... "
	./bootstrap.sh
	@echo "Now you have to run configure:\t./configure --with-vmkit-src=<path/to/vmkit>"

else 
ifeq ($(wildcard Makefile.config),) 
default:
	@echo "You have to run configure first !\nrun ./configure --with-vmkit-src=<path/to/vmkit>"
else

LEVEL=.

SUB_DIRS=lib tools

include $(LEVEL)/Makefile.rules

endif
endif
