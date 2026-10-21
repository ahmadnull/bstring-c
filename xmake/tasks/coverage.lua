--- Report which public functions are missing a tests/unit/test_<function>.c file.

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

local function scan(functions, unit_dir, os)
    local name_width = 0
    for _, name in ipairs(functions) do
        name_width = math.max(name_width, #name)
    end

    local rows = {}
    local missing = {}
    local covered = 0

    for _, name in ipairs(functions) do
        local file = "test_" .. name .. ".c"
        local found = os.isfile(unit_dir .. "/" .. file)
        if found then
            covered = covered + 1
        else
            table.insert(missing, name)
        end
        table.insert(rows, { name = name, file = file, found = found })
    end

    return rows, covered, missing, name_width
end

local function render(style, rows, covered, missing, name_width)
    local total = #rows
    local percentage = total > 0 and (covered * 100 / total) or 0
    local coverage_color = percentage >= 100 and style.GREEN
        or (percentage >= 50 and style.YELLOW or style.RED)

    local title = "BSTRING TEST COVERAGE"
    local summary = string.format("Coverage: %d/%d functions (%.1f%%)", covered, total, percentage)
    local missing_line = "Missing: " .. (#missing > 0 and table.concat(missing, ", ") or "none")

    local body = {}
    for _, row in ipairs(rows) do
        if row.found then
            table.insert(body, {
                text = "[+] " .. style.pad(row.name, name_width) .. "  " .. row.file,
                color = style.GREEN,
            })
        else
            table.insert(body, {
                text = "[-] " .. style.pad(row.name, name_width) .. "  (missing)",
                color = style.RED,
            })
        end
    end

    local width = math.max(#title, #summary, #missing_line)
    for _, row in ipairs(body) do
        width = math.max(width, #row.text)
    end

    local function border()
        print(style.CYAN .. style.BOLD .. "+" .. string.rep("-", width + 2) .. "+" .. style.NORMAL)
    end

    local function line(text, color)
        color = color or style.CYAN
        print(color .. style.BOLD .. "| " .. style.NORMAL .. text
            .. string.rep(" ", math.max(0, width - #text))
            .. color .. style.BOLD .. " |" .. style.NORMAL)
    end

    print("")
    border()
    line(style.center(title, width), style.MAGENTA)
    border()
    for _, row in ipairs(body) do
        line(row.text, row.color)
    end
    border()
    line(summary, coverage_color)
    line(missing_line, #missing > 0 and style.RED or style.GREEN)
    border()
    print("")
end

task("test-coverage")
    set_menu({
        usage = "xmake test-coverage",
        description = "Check that every public function has a tests/unit/test_<function>.c file",
    })
    on_run(function ()
        import("lib.detect.find_program")
        local style = import("bstring.style")()

        local ctags = find_program("ctags")
        if not ctags then
            print(style.RED .. style.BOLD .. "error: universal-ctags not found in PATH" .. style.NORMAL)
            return
        end

        local root = os.projectdir()
        local functions = collect_functions(os, ctags, root .. "/include/bstring.h")
        if #functions == 0 then
            print(style.YELLOW .. style.BOLD .. "warning: no function prototypes found in include/bstring.h" .. style.NORMAL)
            return
        end

        local rows, covered, missing, name_width = scan(functions, root .. "/tests/unit", os)
        render(style, rows, covered, missing, name_width)
    end)
