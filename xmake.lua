set_project("bstring")
set_version("0.0.0")

add_rules("mode.debug", "mode.release", "mode.valgrind")
set_defaultmode("debug")

target("bstring")
    set_kind("shared")
    add_files("src/bstring.c")
    add_files("src/internal/bstring.c")
    add_files("src/internal/cstring.c")
    add_files("src/internal/char.c")
    set_group("main")

includes("xmake/targets.lua")

add_dir_tests("tests/unit", "unit")
add_dir_tests("tests/integration", "integration")

add_dir_examples("examples")

includes("xmake/examples.lua")
includes("xmake/tasks.lua")
