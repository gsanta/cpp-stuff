help: ## Displays the available commands (this help)
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := help


coverage-xml: ## runs tests with coverage in a docker container using xml reporter
	COVERAGE_REPORTER=XML docker-compose run --rm --build tests-coverage

coverage: ## runs tests with coverage in a docker container using html reporter
	COVERAGE_REPORTER=HTML docker-compose run --rm --build tests-coverage
