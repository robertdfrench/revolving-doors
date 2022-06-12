TERRAFORM=$(shell which terraform || echo "terraform.missing")

%.missing:
	$(error "You'll need to install $* before proceeding")
