include lib.mk

test: $(subst /,.test,$(sort $(wildcard */))) ## Run all tests
	$(info done!)

%.test: host_check
	$(call announce,$*)
	$(MAKE) -C $* test

links:
	@find . -type f -name README.md \
		| grep -v "\./README.md" \
		| sort \
		| awk -f navigation.awk \
		| awk -f transform.awk
