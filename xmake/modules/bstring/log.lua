--!A build utility based on Lua
--
-- Leveled console logging built on the shared style module.
--

function main()
    local style = import("bstring.style")()
    local log = {}

    --- Print a top-level "[index] text" heading.
    function log.level0(color, index, text)
        print("\n" .. style.BOLD .. color .. "[" .. index .. "] " .. text .. style.NORMAL)
    end

    --- Print a nested "[major.minor] text" heading.
    function log.level1(color, major, minor, text)
        print(style.BOLD .. color .. "\n[" .. major .. "." .. minor .. "] " .. text .. "\n" .. style.NORMAL)
    end

    return log
end
