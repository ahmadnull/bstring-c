set_project("bstring")
set_version("0.0.0")

add_rules("mode.debug", "mode.release", "mode.valgrind")
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
        add_tests(name)
        if is_mode("valgrind") then
            on_test(function (target)
                os.exec("valgrind --leak-check=full --error-exitcode=1 " .. target:targetfile())
                return true
            end)
        end
end

add_test("example_bstring", "examples/example_bstring.c")
add_test("test_bstring", "tests/test_bstring.c")
