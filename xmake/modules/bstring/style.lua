--!A build utility based on Lua
--
-- ANSI text styling and small text-layout helpers.
--

function main()
    local style = {}

    style.NORMAL  = "\27[0m"
    style.BOLD    = "\27[1m"
    style.DIM     = "\27[2m"
    style.RED     = "\27[31m"
    style.GREEN   = "\27[32m"
    style.YELLOW  = "\27[33m"
    style.BLUE    = "\27[34m"
    style.MAGENTA = "\27[35m"
    style.CYAN    = "\27[36m"
    style.WHITE   = "\27[37m"

    --- Pad `text` on the right with spaces to `width` visible characters.
    function style.pad(text, width)
        return text .. string.rep(" ", math.max(0, width - #text))
    end

    --- Center `text` within `width` visible characters.
    function style.center(text, width)
        local left = math.floor((width - #text) / 2)
        return string.rep(" ", math.max(0, left)) .. text
            .. string.rep(" ", math.max(0, width - #text - left))
    end

    return style
end
