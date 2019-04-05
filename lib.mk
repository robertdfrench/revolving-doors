.PHONY: help

CC=$(shell which cc || which gcc || (echo "You need to install a C compiler to run these tests."; exit 1))

announce=@printf "\n\033[31m\#\# $(1)\033[0m\n"
emphasize=@printf "\033[36m($(1) )\033[0m\n"

help:
	$(call announce, Run 'make test' to build and run the exercises)

host_check: illumos $(CC);

illumos:
	@[ `uname` = SunOS ] || (echo "You need to be on Illumos to run these tests."; exit 1)
