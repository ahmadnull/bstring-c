function add_target(name, source, group, is_test)
    target(name)
        set_kind("binary")
        set_default(false)
        add_deps("bstring")
        add_files(source)
        set_group(group)
        if is_test then
            add_tests("default")
        end
        if is_mode("valgrind") then
            on_test(function (target)
                os.exec("valgrind --leak-check=full --error-exitcode=1 " .. target:targetfile())
                return true
            end)
        end
end

function add_test(name, source, group)
    add_target(name, source, group .. "_tests", true)
end

function add_example(name, source)
    add_target(name, source, "examples", true)
end
