include etc/lib.mk

test: $(subst /,.test,$(sort $(wildcard *_*/))) ## Run all tests
	$(info done!)

%.test: host_check
	$(call announce,$*)
	$(MAKE) -C $* test

updateLinks: relativeNavigationTable.txt
	awk -f etc/transform.awk $< | bash -e
	rm -f *.txt

relativeNavigationTable.txt: navigationTable.txt
	awk '{ sub("README.md","",$$1); sub("README.md","",$$3); print }' $< > $@

navigationTable.txt: readmes.txt
	awk -f etc/navigation.awk $< > $@

readmes.txt:
	find . -type f -name README.md \
		| grep -v "\./README.md" \
		| sort > $@
