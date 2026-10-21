[group("examples")]
@list-examples: && (xmake "list-examples")
    printf "%s%s%s\n" {{BOLD + BLUE}} "Available Examples:" {{NORMAL}}

[group("run")]
[group("examples")]
run-examples *args: build (xmake "run-examples" args)

[group("run")]
run-group group *args: build (run "-g" group args)

[group("run")]
run *args: build (xmake "run" args)

build *args: config (xmake "build" rebuild_flag args)

config *args: (xmake "config" "-m" mode args)

check *args: (xmake "check" args)

clean-all: (clean "--all")

clean *args: (xmake "clean" args)

format-check *args: (format "--dry-run" args)

format *args: (xmake "format" "--group=*" args)

[private]
xmake *args:
    xmake {{args}} {{verbose_flag}}

import? "xmake/test.just"
