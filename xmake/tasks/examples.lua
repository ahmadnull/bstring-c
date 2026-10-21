--- Tasks for listing and running the targets in the 'examples' group.

local function list_examples(project)
    local count = 0
    for _, target in pairs(project.targets()) do
        if target:get("group") == "examples" then
            print(target:name())
            count = count + 1
        end
    end
    print("Total found: " .. count)
end

local function find_cat_command(find_program)
    if find_program("bat") then
        return "bat -P --style=plain --color=always"
    elseif find_program("batcat") then
        return "batcat -P --style=plain --color=always"
    end
    return "cat"
end

local function print_source_files(sourcebatches, index, cat_command, os, style, log)
    for _, batch in pairs(sourcebatches) do
        if batch.sourcefiles then
            local file_index = 0
            for _, file in ipairs(batch.sourcefiles) do
                log.level1(style.YELLOW, index, file_index, "Source File: " .. file)
                os.exec(cat_command .. " \"" .. file .. "\"")
                file_index = file_index + 1
            end
        end
    end
end

local function run_examples(project, find_program, os, style, log)
    local cat_command = find_cat_command(find_program)
    local count = 0

    for _, target in pairs(project.targets()) do
        if target:get("group") == "examples" then
            local name = target:name()

            log.level0(style.BLUE, count, "Example Target: " .. name)

            local sourcebatches = target:sourcebatches()
            if sourcebatches then
                print_source_files(sourcebatches, count, cat_command, os, style, log)
            end

            log.level0(style.GREEN, count, "Execution Output")
            os.exec("xmake run " .. name)

            count = count + 1
        end
    end

    print("\nSuccessfully ran " .. count .. " example(s).")
end

task("list-examples")
    set_menu({
        usage = "xmake list-examples",
        description = "List all targets in the 'examples' group",
    })
    on_run(function ()
        import("core.project.project")
        list_examples(project)
    end)

task("run-examples")
    set_menu({
        usage = "xmake run-examples",
        description = "Print source files and execute each target in the 'examples' group",
    })
    on_run(function ()
        import("core.project.project")
        import("lib.detect.find_program")
        local style = import("bstring.style")()
        local log = import("bstring.log")()
        run_examples(project, find_program, os, style, log)
    end)
