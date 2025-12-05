# Wordlang Standard Library: Utils
# Common utility functions

# Print a blank line
define blank do
    print ""
end

# Print with a prefix
define say with message do
    print message
end

# Print a number with label
define show with label value do
    print label
    print value
end

# Repeat a task n times
define repeat_times with n do
    set _i to 0
    while _i < n do
        set _i to _i + 1
    end
    return n
end

# Swap two values (returns array with swapped values)
define swap with a b do
    set _temp to a
    set a to b
    set b to _temp
    return b
end

# Check if value is between min and max (inclusive)
define between with value low high do
    if value >= low and value <= high then
        return true
    end
    return false
end

# Return 1 if condition is true, 0 if false
define bool with condition do
    if condition then
        return 1
    end
    return 0
end

# Default value: return value if not zero, otherwise default
define default with value fallback do
    if value == 0 then
        return fallback
    end
    return value
end

