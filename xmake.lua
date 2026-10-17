add_rules("mode.debug", "mode.release")
set_defaultmode("debug")

target("bstring")
    set_kind("shared")
    add_files("src/bstring.c")

function add_test(name, source)
    target(name)
        set_kind("binary")
        set_default(false)
        add_deps("bstring")
        add_files(source)
        add_tests("default")
end

add_test("example_bstring", "test/integration_tests/example_bstring.c")
add_test("test_bstring", "test/unit_tests/test_bstring.c")
