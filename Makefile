include lib.mk

test: $(subst /,.test,$(sort $(wildcard */))) ## Run all tests
	$(info done!)

%.test: host_check
	$(call announce,$*)
	$(MAKE) -C $* test
