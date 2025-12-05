# Wordlang Standard Library: Loops
# Helper functions for common loop patterns

# Sum numbers from start to end-1
define sum_range with start stop do
    set _total to 0
    set _i to start
    while _i < stop do
        set _total to _total + _i
        set _i to _i + 1
    end
    return _total
end

# Product of numbers from start to end-1
define product_range with start stop do
    set _result to 1
    set _i to start
    while _i < stop do
        set _result to _result * _i
        set _i to _i + 1
    end
    return _result
end

# Count iterations (just returns the count)
define count_to with n do
    set _count to 0
    while _count < n do
        set _count to _count + 1
    end
    return _count
end

# Countdown from n to 1
define countdown with n do
    while n > 0 do
        print n
        set n to n - 1
    end
    return 0
end

# Print numbers from start to end-1
define print_range with start stop do
    set _i to start
    while _i < stop do
        print _i
        set _i to _i + 1
    end
end

