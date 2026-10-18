set_project("bstring")
set_version("0.0.0")

add_rules("mode.debug", "mode.release", "mode.valgrind")
set_defaultmode("debug")

target("bstring")
    set_kind("shared")
    add_files("src/api_impl.c")
    add_files("src/internal.c")

function add_test(name, source, group)
    target(name)
        set_kind("binary")
        set_default(false)
        add_deps("bstring")
        add_files(source)
        set_group(group .. "_tests")
        add_tests("default")
        if is_mode("valgrind") then
            on_test(function (target)
                os.exec("valgrind --leak-check=full --error-exitcode=1 " .. target:targetfile())
                return true
            end)
        end
end

add_test("test_unit", "tests/unit/test_unit.c", "unit")
add_test("test_integration", "tests/integration/test_integration.c", "integration")

function add_example(name, source)
    target(name)
        set_kind("binary")
        set_default(false)
        add_deps("bstring")
        add_files(source)
        set_group("examples")
        if is_mode("valgrind") then
            on_test(function (target)
                os.exec("valgrind --leak-check=full --error-exitcode=1 " .. target:targetfile())
                return true
            end)
        end
end

add_example("example_bstring", "examples/example_bstring.c")
