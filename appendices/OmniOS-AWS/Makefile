include tools.mk
help: ##: Display this help menu
	@echo "USAGE:"
	@echo
	@awk -F': ' \
		'/##:/ && !/awk/ { print "\t","make",$$1,"-",$$3 }' \
	       	$(MAKEFILE_LIST)

login: build/provision.stamp ##: Log in to the lab environment
	ssh -i build/lab_key root@`cat build/ipv4_address`

provision_lab_host: build/provision.stamp ##: Configure lab environment

build/provision.stamp: build/lab_setup.mk.stamp build/lab_key build/ipv4_address
	ssh -i build/lab_key root@`cat build/ipv4_address` make -f lab_setup.mk
	@touch $@

build/lab_setup.mk.stamp: lab_setup.mk build/lab_key build/ipv4_address | build/
	scp -i build/lab_key lab_setup.mk root@`cat build/ipv4_address`:~/
	@touch $@

create_lab_host: build/ipv4_address ##: Create an EC2 instance running OmniOS

build/ipv4_address: \
	$(TERRAFORM) lab_host.tf build/lab_key.pub build/initialized.stamp
	$(TERRAFORM) apply
	$(TERRAFORM) output -raw ipv4_address > $@

init: build/initialized.stamp ##: Initialize Terraform for this directory

build/initialized.stamp: \
	$(TERRAFORM) providers.tf $(wildcard *.lock.hcl) | build/
	$(TERRAFORM) init
	@touch $@

build/lab_key build/lab_key.pub: | build/
	ssh-keygen -f build/lab_key -N ''

build/:
	mkdir $@

clean: $(TERRAFORM) ##: Remove this lab's resources from your AWS account
	$(TERRAFORM) destroy
	rm -rf \
		.terraform \
		terraform.tfstate \
		terraform.tfstate.backup \
		build
