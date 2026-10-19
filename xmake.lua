set_project("bstring")
set_version("0.0.0")

add_rules("mode.debug", "mode.release", "mode.valgrind")
set_defaultmode("debug")

target("bstring")
    set_kind("shared")
    add_files("src/bstring.c")
    add_files("src/internal/bstring.c")
    add_files("src/internal/cstring.c")
    set_group("main")

includes("xmake/targets.lua")

add_test("test_unit", "tests/unit/test_unit.c", "unit")
add_test("test_integration", "tests/integration/test_integration.c", "integration")

add_example("example_bstring", "examples/example_bstring.c")

includes("xmake/examples.lua")
