set allow-duplicate-recipes

_default: check (just "valgrind=1" "test" "-v")

staged-c := `git diff --cached --name-only -- "*.[c|h]" | tr "\n" " "`

release  := "0"
valgrind := "0"
mode     := (
    if      release  == "1" { "release"  }
    else if valgrind == "1" { "valgrind" }
    else                    { "debug"    }
)

verbose      := "0"
verbose_flag := if verbose == "1" { "-v" } else { "" }

force        := "0"
rebuild_flag := if force == "1" { "--rebuild" } else { "" }

cat_command := (`
    if command -v bat >/dev/null 2>&1; then
        echo bat
    elif command -v batcat >/dev/null 2>&1; then
        echo batcat
    else
        echo cat
    fi
`)

tree_command := (`
    if command -v eza >/dev/null 2>&1; then
        echo "eza --tree --color always --icons always"
    else
        echo tree
    fi
`)

tree_git_ignore_flag := (`
    if command -v eza >/dev/null 2>&1; then
        echo "--git-ignore"
    else
        echo "--gitignore"
    fi
`)

[group("info")]
tree-gitignore *args: (tree tree_git_ignore_flag args)

alias t := tree-gitignore

[group("info")]
tree *args:
    {{tree_command}} {{args}}

[group("info")]
tokei *args:
    tokei {{args}}

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

[group("setup")]
setup: gen-just

[group("setup")]
[script]
gen-just:
    scripts/gen-just.sh

import? "just/xmake.just"
import? "just/git.just"
