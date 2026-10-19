-- Reset formatting
local NORMAL  = "\27[0m"

-- Styles
local BOLD   = "\27[1m"
local DIM    = "\27[2m"
local ITALIC = "\27[3m"

-- Colors
local BLACK  = "\27[30m"
local RED    = "\27[31m"
local GREEN  = "\27[32m"
local YELLOW = "\27[33m"
local BLUE   = "\27[34m"
local MAGENTA= "\27[35m"
local CYAN   = "\27[36m"
local WHITE  = "\27[37m"

task("list-examples")
    set_menu({
        usage = "xmake list-examples",
        description = "List all targets in the 'examples' group",
    })
    on_run(function ()
        import("core.project.project")

        local count = 0
        for _, target in pairs(project.targets()) do
            if target:get("group") == "examples" then
                print(target:name())
                count = count + 1
            end
        end
        print("Total found: " .. count)
    end)

task("run-examples")
    set_menu({
        usage = "xmake run-examples",
        description = "Print source files and execute each target in the 'examples' group",
    })
    on_run(function ()
        import("lib.detect.find_program")

        -- Choose viewer: prefer 'bat', fallback to 'cat'
        local viewer = "cat"
        if find_program("bat") then
            viewer = "bat --style=plain --color=always"
        elseif find_program("batcat") then
            viewer = "batcat --style=plain --color=always"
        end

        import("core.project.project")
        local count = 0
        for _, target in pairs(project.targets()) do
            if target:get("group") == "examples" then
                local name = target:name()

                print("\n" .. BOLD .. BLUE .. "[" .. count .. "] Example Target: " .. name .. NORMAL)

                -- Properly fetch and print all expanded source files
                local sourcebatches = target:sourcebatches()
                if sourcebatches then
                    for _, sourcebatch in pairs(sourcebatches) do
                        if sourcebatch.sourcefiles then
                            local source_count = 0;
                            for _, sourcefile in ipairs(sourcebatch.sourcefiles) do
                                print(BOLD .. YELLOW .. "\n[" .. count .. "." .. source_count .. "] Source File: " .. sourcefile .. "\n" .. NORMAL)
                                os.exec(viewer .. " \"" .. sourcefile .. "\"")
                            end
                        end
                    end
                end

                count = count + 1

                -- Build and run the target
                print(BOLD .. GREEN .. "\n[" .. count .. "] Execution Output" .. NORMAL)
                os.exec("xmake run " .. name)
            end
        end

        if count == 0 then
            print("No targets found in the 'examples' group.")
        else
            print("\nSuccessfully ran " .. count .. " example(s).")
        end
    end)
