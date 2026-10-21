[group("xmake")]
[group("test")]
test-coverage: (xmake "test-coverage")

# Test a single integration test
[group("xmake")]
[group("test")]
test-integration-target target *args: (test-target "integration" target args)

# Test a single unit test
[group("xmake")]
[group("test")]
test-unit-target target *args: (test-target "unit" target args)

# Test all unit tests
[group("xmake")]
[group("test")]
test-integration *args: (test-group "integration" args)

# Test all integration tests
[group("xmake")]
[group("test")]
test-unit *args: (test-group "unit" args)

# Test a group
[group("xmake")]
[group("test")]
test-group group *args: (test "-g" group + "_tests" args)

# Test a single target
[group("xmake")]
[group("test")]
test-target group target *args: (test "-v" group + "_" + target + "/*" args)

[group("xmake")]
[group("test")]
test *args: && config (xmake "test" "-j1" args)
    @if [ "{{mode}}" == "release" ]; then echo {{ BOLD + RED + "Can not test in release configuration" + NORMAL }}; exit 1; fi;
