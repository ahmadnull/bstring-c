[group("xmake")]
[group("examples")]
@list-examples: && (xmake "list-examples")
    printf "%s%s%s\n" {{BOLD + BLUE}} "Available Examples:" {{NORMAL}}

[group("xmake")]
[group("run")]
[group("examples")]
run-examples *args: build (xmake "run-examples" args)

[group("xmake")]
[group("run")]
run-group group *args: build (run "-g" group args)

[group("xmake")]
[group("run")]
run *args: build (xmake "run" args)

[group("xmake")]
[group("test")]
test-integration *args: (test-group "integration" args)

[group("xmake")]
[group("test")]
test-unit *args: (test-group "unit" args)

[group("xmake")]
[group("test")]
test-group group *args: (test "-g" group + "_tests" args)

[group("xmake")]
[group("test")]
test *args: && config (xmake "test" "-j1" args)
    @if [ "{{mode}}" == "release" ]; then echo {{ BOLD + RED + "Can not test in release configuration" + NORMAL }}; exit 1; fi;

[group("xmake")]
build *args: config (xmake "build" rebuild_flag args)

[group("xmake")]
config *args: (xmake "config" "-m" mode args)

[group("xmake")]
check *args: (xmake "check" args)

[group("xmake")]
clean-all: (clean "--all")

[group("xmake")]
clean *args: (xmake "clean" args)

[group("xmake")]
format-check *args: (format "--dry-run" args)

[group("xmake")]
format *args: (xmake "format" "--group=*" args)

[group("xmake")]
[private]
xmake *args:
    xmake {{args}} {{verbose_flag}}
