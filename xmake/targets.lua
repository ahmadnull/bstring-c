--- Shared target definitions for tests and examples.

local function run_under_valgrind(target)
    os.exec("valgrind --leak-check=full --error-exitcode=1 " .. target:targetfile())
    return true
end

local function define_binary_target(name, source, group)
    target(name)
        set_kind("binary")
        set_default(false)
        add_deps("bstring")
        add_files(source)
        set_group(group)
end

function add_test_target(name, source, group)
    define_binary_target(name, source, group .. "_tests")
    add_tests("default")
    if is_mode("valgrind") then
        on_test(run_under_valgrind)
    end
end

function add_example_target(name, source)
    define_binary_target(name, source, "examples")
    if is_mode("valgrind") then
        on_run(run_under_valgrind)
    end
end

function add_dir_tests(dir, group)
    for _, source in ipairs(os.files(dir .. "/*.c")) do
        add_test_target(group .. "_" .. path.basename(source), source, group)
    end
end

function add_dir_examples(dir)
    for _, source in ipairs(os.files(dir .. "/*.c")) do
        add_example_target(path.basename(source), source)
    end
end
