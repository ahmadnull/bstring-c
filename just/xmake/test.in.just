test-coverage: (xmake "test-coverage")

# Test a single integration test
test-integration-target target *args: (test-target "integration" target args)

# Test a single unit test
test-unit-target target *args: (test-target "unit" target args)

# Test all unit tests
test-integration *args: (test-group "integration" args)

# Test all integration tests
test-unit *args: (test-group "unit" args)

# Test a group
test-group group *args: (test "-g" group + "_tests" args)

# Test a single target
test-target group target *args: (test "-v" group + "_" + target + "/*" args)

test *args: && config (xmake "test" "-j1" args)
    @if [ "{{mode}}" == "release" ]; then echo {{ BOLD + RED + "Can not test in release configuration" + NORMAL }}; exit 1; fi;
