# Emit path-derived [group("...")] lines above each recipe, before that
# recipe's own attribute block, so existing [arg]/[private]/[group]
# decorators stay attached to their recipe.
#
# Usage: awk -v groups="ancestor,self" -f gen-just.awk <input.just.in>

function emit_groups() {
    n = split(groups, g, ",")
    for (i = 1; i <= n; i++) {
        print "[group(\"" g[i] "\")]"
    }
}

function flush_buf() {
    if (buf != "") {
        printf "%s", buf
        buf = ""
    }
}

# A recipe signature: starts at column 0 and contains a colon, but is not a
# comment, attribute, import, alias or set directive.
/^[^ \t]/ && /:/ && !/^#/ && !/^\[/ && !/^import/ && !/^alias/ && !/^set/ {
    emit_groups()
    flush_buf()
    print
    next
}

# Buffer attribute lines so they can be flushed after the injected groups.
/^\[/ {
    buf = buf $0 "\n"
    next
}

{
    flush_buf()
    print
}

END {
    flush_buf()
}
