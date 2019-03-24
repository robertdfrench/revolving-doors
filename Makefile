include lib.mk

test: $(subst /,,*/) ## Run all tests
	$(info done!)

knock_knock: host_check ## Open a door and call a function inside
	$(call announce,$@)
	$(MAKE) -C $@ test

hello_world: host_check ## Open a door an receive a greeting
	$(call announce,$@)
	$(MAKE) -C $@ test

door_through_door: host_check ## Open a door on a client's behalf
	$(call announce,$@)
	$(MAKE) -C $@ test

payload_size: host_check ## How much can we send and how fast can we send it?
	$(call announce,$@)
	$(MAKE) -C $@ test
