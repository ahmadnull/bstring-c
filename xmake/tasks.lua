--- Text Styling ---
local NORMAL  = "\27[0m"
local BOLD    = "\27[1m"
local RED     = "\27[31m"
local GREEN   = "\27[32m"
local YELLOW  = "\27[33m"
local CYAN    = "\27[36m"
local MAGENTA = "\27[35m"

--- Helpers ---

local function pad(text, width)
    return text .. string.rep(" ", math.max(0, width - #text))
end

local function center(text, width)
    local left = math.floor((width - #text) / 2)
    return string.rep(" ", math.max(0, left)) .. text
        .. string.rep(" ", math.max(0, width - #text - left))
end

local function collect_functions(os, ctags, header)
    local cmd = string.format(
        "'%s' -x --c-types=f --kinds-C=+p '%s' | cut -f 1 -d ' ' | sed 's/bstring_//g'",
        ctags, header)
    local output = os.iorunv("sh", { "-c", cmd })

    local functions = {}
    for line in (output or ""):gmatch("[^\r\n]+") do
        line = line:match("^%s*(.-)%s*$")
        if #line > 0 then
            table.insert(functions, line)
        end
    end

    return functions
end

local function print_report(os, functions, unit_dir)
    local name_width = 0
    for _, name in ipairs(functions) do
        name_width = math.max(name_width, #name)
    end

    local rows = {}
    local covered = 0
    local missing = {}

    for _, name in ipairs(functions) do
        local file = "test_" .. name .. ".c"
        local found = os.isfile(unit_dir .. "/" .. file)
        local content
        local color

        if found then
            covered = covered + 1
            content = "[+] " .. pad(name, name_width) .. "  " .. file
            color = GREEN
        else
            table.insert(missing, name)
            content = "[-] " .. pad(name, name_width) .. "  (missing)"
            color = RED
        end

        table.insert(rows, { content = content, color = color })
    end

    local total = #functions
    local percentage = total > 0 and (covered * 100 / total) or 0
    local coverage_color = percentage >= 100 and GREEN or (percentage >= 50 and YELLOW or RED)

    local title = "BSTRING TEST COVERAGE"
    local summary = string.format("Coverage: %d/%d functions (%.1f%%)", covered, total, percentage)
    local missing_line = "Missing: " .. (#missing > 0 and table.concat(missing, ", ") or "none")

    local width = #title
    width = math.max(width, #summary)
    width = math.max(width, #missing_line)
    for _, row in ipairs(rows) do
        width = math.max(width, #row.content)
    end

    local function border()
        print(CYAN .. BOLD .. "+" .. string.rep("-", width + 2) .. "+" .. NORMAL)
    end

    local function line(text, color)
        color = color or CYAN
        print(color .. BOLD .. "| " .. NORMAL .. text
            .. string.rep(" ", math.max(0, width - #text))
            .. color .. BOLD .. " |" .. NORMAL)
    end

    print("")
    border()
    line(center(title, width), MAGENTA)
    border()

    for _, row in ipairs(rows) do
        line(row.content, row.color)
    end

    border()
    line(summary, coverage_color)
    line(missing_line, #missing > 0 and RED or GREEN)
    border()
    print("")
end

--- Tasks ---

task("test-coverage")
    set_menu({
        usage = "xmake test-coverage",
        description = "Check that every public function has a tests/unit/test_<function>.c file",
    })
    on_run(function ()
        import("lib.detect.find_program")

        local ctags = find_program("ctags")
        if not ctags then
            print(RED .. BOLD .. "error: universal-ctags not found in PATH" .. NORMAL)
            return
        end

        local root = os.projectdir()
        local functions = collect_functions(os, ctags, root .. "/include/bstring.h")
        if #functions == 0 then
            print(YELLOW .. BOLD .. "warning: no function prototypes found in include/bstring.h" .. NORMAL)
            return
        end

        print_report(os, functions, root .. "/tests/unit")
    end)
