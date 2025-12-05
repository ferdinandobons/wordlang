# Wordlang Standard Library: Math Extra
# Additional math functions written in Wordlang

# Factorial
define fact with n do
    if n < 2 then
        return 1
    end
    return n * call fact n - 1
end

# Fibonacci
define fib with n do
    if n < 2 then
        return n
    end
    return call fib n - 1 + call fib n - 2
end

# Power (base^exp)
define pow with base exp do
    set _result to 1
    set _i to 0
    while _i < exp do
        set _result to _result * base
        set _i to _i + 1
    end
    return _result
end

# Is prime number
define is_prime with n do
    if n < 2 then
        return false
    end
    if n == 2 then
        return true
    end
    if n % 2 == 0 then
        return false
    end
    set _i to 3
    while _i * _i <= n do
        if n % _i == 0 then
            return false
        end
        set _i to _i + 2
    end
    return true
end

# Greatest common divisor
define gcd with a b do
    while b != 0 do
        set _temp to b
        set b to a % b
        set a to _temp
    end
    return a
end

# Least common multiple
define lcm with a b do
    set _g to call gcd a b
    return a * b / _g
end

# Absolute value
define absolute with n do
    if n < 0 then
        return 0 - n
    end
    return n
end

# Clamp value between min and max
define clamp with value low high do
    if value < low then
        return low
    end
    if value > high then
        return high
    end
    return value
end

# Average of two numbers
define average with a b do
    return (a + b) / 2
end

# Sum of digits
define digit_sum with n do
    if n < 0 then
        set n to 0 - n
    end
    set _sum to 0
    while n > 0 do
        set _sum to _sum + n % 10
        set n to n / 10
    end
    return _sum
end

# Count digits
define digit_count with n do
    if n == 0 then
        return 1
    end
    if n < 0 then
        set n to 0 - n
    end
    set _count to 0
    while n > 0 do
        set _count to _count + 1
        set n to n / 10
    end
    return _count
end

