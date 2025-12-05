# Wordlang Standard Library: Arrays
# Array manipulation functions

# Sum all elements in an array
define array_sum with arr do
    set _total to 0
    set _i to 0
    while _i < length arr do
        set _total to _total + get arr _i
        set _i to _i + 1
    end
    return _total
end

# Find maximum in array
define array_max with arr do
    if length arr == 0 then
        return 0
    end
    set _max to get arr 0
    set _i to 1
    while _i < length arr do
        set _val to get arr _i
        if _val > _max then
            set _max to _val
        end
        set _i to _i + 1
    end
    return _max
end

# Find minimum in array
define array_min with arr do
    if length arr == 0 then
        return 0
    end
    set _min to get arr 0
    set _i to 1
    while _i < length arr do
        set _val to get arr _i
        if _val < _min then
            set _min to _val
        end
        set _i to _i + 1
    end
    return _min
end

# Count occurrences of value in array
define array_count with arr value do
    set _count to 0
    set _i to 0
    while _i < length arr do
        if get arr _i == value then
            set _count to _count + 1
        end
        set _i to _i + 1
    end
    return _count
end

# Find index of value (-1 if not found)
define array_find with arr value do
    set _i to 0
    while _i < length arr do
        if get arr _i == value then
            return _i
        end
        set _i to _i + 1
    end
    return -1
end

# Check if array contains value
define array_has with arr value do
    set _idx to call array_find arr value
    if _idx >= 0 then
        return true
    end
    return false
end

# Print all elements
define array_print with arr do
    set _i to 0
    while _i < length arr do
        print get arr _i
        set _i to _i + 1
    end
end

# Average of array
define array_avg with arr do
    if length arr == 0 then
        return 0
    end
    set _sum to call array_sum arr
    return _sum / length arr
end

