#!/bin/env sh

BOLD=$'\x1b[1m'
NORMAL=$'\x1b[0m'
GREEN=$'\x1b[32m'
BLUE=$'\x1b[33m'
YELLOW=$'\x1b[34m'

in_files=$(find just -type f -name "*.in.just")
for f in $in_files;
do
    rel=${f%.in.just}.just
    base=$(basename -s .in.just "$f")
    dir=$(dirname "$f")

    # ancestor group names, nearest-last, excluding the top-level "just" dir
    anc=""
    cur="$dir"
    while [ "$cur" != "." ] && [ "$cur" != "/" ] && [ "$cur" != "just" ]; do
        anc=$(basename "$cur")" $anc"
        cur=$(dirname "$cur")
    done

    # comma-separated groups: ancestors then self
    groups=$(printf '%s %s' "$anc" "$base" | awk '{$1=$1; gsub(/ +/, ","); print}')

    awk -v groups="$groups" -f "$(dirname "$0")/gen-just.awk" "$f" > "$rel"

    printf "${BOLD}${GREEN}[generated]${NORMAL} ${YELLOW}%s${NORMAL} ${GREEN}->${NORMAL} ${BLUE}%s${NORMAL}\n" "$f" "$rel"
done
