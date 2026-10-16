_default: check run

staged-c := `git diff --cached --name-only -- "*.[c|h]" | tr '\n' ' '`

[group('xmake')]
run *args: build (xmake "run" args)

[group('xmake')]
build *args: (xmake "build" args)

[group('xmake')]
test *args: (xmake "test" args)

[group('xmake')]
check *args: (xmake "check" args)

[group('xmake')]
format *args: (xmake "format" args)

[group('xmake')]
[private]
xmake *args:
    xmake {{args}}

[group('git')]
add-staged-c: (add staged-c)

[group('git')]
add-all: (add "-A")

[group('git')]
add +args: (git "add" args)

[group('git')]
[arg('type', pattern='feat|fix|refactor|perf|style|test|docs|build|ops|chore')]
[arg('scope', short='s', long='scope')]
[arg('breaking', short='B', long='breaking', value='1')]
[arg('body', short='b', long='body')]
[arg('footer', short='f', long='footer')]
commit type description scope='' breaking='0' body='' footer='': format add-staged-c
    #!/bin/env sh
    if [ -n "{{scope}}" ]; then scope="({{scope}})"; fi
    if [ "{{breaking}}" -eq "1" ]; then breaking="!"; fi
    git commit -m "{{type}}${scope}${breaking}: {{description}}" -m "{{body}}" -m "{{footer}}"

[group('git')]
[private]
git *args:
    git {{args}}
