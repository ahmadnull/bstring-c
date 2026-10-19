--- Text Styling ---
local NORMAL  = "\27[0m"
local BOLD   = "\27[1m"
local DIM    = "\27[2m"
local ITALIC = "\27[3m"
local BLACK  = "\27[30m"
local RED    = "\27[31m"
local GREEN  = "\27[32m"
local YELLOW = "\27[33m"
local BLUE   = "\27[34m"
local MAGENTA= "\27[35m"
local CYAN   = "\27[36m"
local WHITE  = "\27[37m"

--- Functions ---

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

local function log_level0(color, count, text)
    print("\n" .. BOLD .. color .. "[" .. count .. "] " .. text .. NORMAL)
end

local function log_level1(color, count_level0, count_level1, text)
    print(BOLD .. color .. "\n[" .. count_level0 .. "." .. count_level1 .. "] " .. text .. "\n" .. NORMAL)
end

local function print_sourcebatches(sourcebatches, count, cat_command, os)
    for _, sourcebatch in pairs(sourcebatches) do
        if sourcebatch.sourcefiles then
            local source_count = 0;
            for _, sourcefile in ipairs(sourcebatch.sourcefiles) do
                log_level1(YELLOW, count, source_count, "Source File: " .. sourcefile)
                os.exec(cat_command .. " \"" .. sourcefile .. "\"")
                source_count = source_count + 1
            end
        end
    end
end

local function find_cat_command(find_program)
    -- Prefer 'bat', fallback to 'cat'
    local cat_command = "cat"
    if find_program("bat") then
        cat_command = "bat --style=plain --color=always"
    elseif find_program("batcat") then
        cat_command = "batcat --style=plain --color=always"
    end

    return cat_command
end

local function run_examples(project, find_program, os)
    local cat_command = find_cat_command(find_program)
    local count = 0

    for _, target in pairs(project.targets()) do
        if target:get("group") == "examples" then
            local name = target:name()

            log_level0(BLUE, count, "Example Target: " .. name)

            -- Properly fetch and print all expanded source files
            local sourcebatches = target:sourcebatches()
            if sourcebatches then
                print_sourcebatches(sourcebatches, count, cat_command, os)
            end

            -- Build and run the target
            log_level0(GREEN, count, "Execution Output")
            os.exec("xmake run " .. name)

            count = count + 1
        end
    end

    print("\nSuccessfully ran " .. count .. " example(s).")
end

--- Tasks ---

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
        run_examples(project, find_program, os)
    end)
