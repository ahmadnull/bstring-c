add-staged-c: (add staged-c)

add-all: (add "-A")

add +args: (git "add" args)

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

[private]
git *args:
    git {{args}}
