.PHONY: help

help:
	@# Help Menu due to https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
	@grep -Eh '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
		| sort \
		| awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

announce=@printf "\n\033[31m\#\# $(1)\033[0m\n"
emphasize=@printf "\033[36m($(1) )\033[0m\n"

host_check: illumos cc;

illumos:
	@[ `uname` = SunOS ] || (echo "You need to be on Illumos to run these tests."; exit 1)

cc:
	@(which cc) || (echo "You need to install a C compiler to run these tests."; exit 1)
