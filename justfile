_default: check (test "-v")

staged-c := `git diff --cached --name-only -- "*.[c|h]" | tr "\n" " "`

release     := "0"
valgrind    := "0"
export mode := if release == "1" { "release" } else if valgrind == "1" { "valgrind" } else { "debug" }

verbose      := "0"
verbose_flag := if verbose == "1" { "-v" } else { "" }

force        := "0"
rebuild_flag := if force == "1" { "--rebuild" } else { "" }

cat_command := `if command -v bat >/dev/null 2>&1; then echo bat; elif command -v batcat >/dev/null 2>&1; then echo batcat; else echo cat; fi`
tree_command := `if command -v eza >/dev/null 2>&1; then echo "eza --tree --color always --icons always"; else echo tree; fi`
tree_git_ignore_flag := `if command -v eza >/dev/null 2>&1; then echo "--git-ignore"; else echo "--gitignore"; fi`

[group("info")]
tree-gitignore *args: (tree tree_git_ignore_flag args)

alias t := tree-gitignore

[group("info")]
tree *args:
    {{tree_command}} {{args}}

[group("info")]
tokei *args:
    tokei {{args}}

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
    export mode={{ if mode != "debug" { "valgrind" } else { "debug" } }}

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
format *args: (xmake "format" args)

[group("xmake")]
[private]
xmake *args:
    xmake {{args}} {{verbose_flag}}

[group("just")]
choose *args: (just "--choose" args)

alias c := choose

[group("just")]
list *args: (just "--list" args)

alias l := list

[group("just")]
[private]
just *args:
    just {{args}}

[group("cat")]
[private]
cat *args:
    {{cat_command}} {{args}}

[group("git")]
add-staged-c: (add staged-c)

[group("git")]
add-all: (add "-A")

[group("git")]
add +args: (git "add" args)

[group("git")]
[arg("type", pattern="feat|fix|refactor|perf|style|test|docs|build|ops|chore")]
[arg("scope", short="s", long="scope")]
[arg("breaking", short="B", long="breaking", value="1")]
[arg("body", short="b", long="body")]
[arg("footer", short="f", long="footer")]
commit type description scope="" breaking="0" body="" footer="": format add-staged-c
    #!/bin/env sh
    if [ -n "{{scope}}" ]; then scope="({{scope}})"; fi
    if [ "{{breaking}}" -eq "1" ]; then breaking="!"; fi
    git commit -m "{{type}}${scope}${breaking}: {{description}}" -m "{{body}}" -m "{{footer}}"

[group("git")]
[private]
git *args:
    git {{args}}
