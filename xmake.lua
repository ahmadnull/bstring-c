add_rules("mode.debug", "mode.release")

target("bstring")
    set_kind("shared")
    add_files("src/bstring.c")

target("bstring_test")
    set_kind("binary")
    add_deps("bstring")
    add_files("test/main.c")
