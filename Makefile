include lib.mk

test: $(subst /,,*/) ## Run all tests
	$(info done!)

hello_world: host_check ## Open a door an receive a greeting
	$(MAKE) -C $@ test

door_through_door: host_check ## Open a door on a client's behalf
	$(MAKE) -C $@ test

payload_size: host_check ## How much can we send and how fast can we send it?
	$(MAKE) -C $@ test
