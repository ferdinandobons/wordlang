# =====================================================
# Wordlang Comprehensive Test
# Tests: functions, nested loops, conditionals, arrays
# =====================================================

print "=== WORDLANG COMPREHENSIVE TEST ==="
print ""

# -----------------------------------------------------
# 1. BASIC FUNCTIONS
# -----------------------------------------------------
print "--- 1. Basic Functions ---"

define add_numbers with a b do
    return a + b
end

define multiply with x y do
    return x * y
end

print "add_numbers 10 5:"
print call add_numbers 10 5

print "multiply 7 8:"
print call multiply 7 8
print ""

# -----------------------------------------------------
# 2. RECURSIVE FUNCTION (Factorial)
# -----------------------------------------------------
print "--- 2. Recursive Function ---"

define factorial with n do
    if n <= 1 then
        return 1
    else
        return n * call factorial n - 1
    end
end

print "factorial 5:"
print call factorial 5

print "factorial 7:"
print call factorial 7
print ""

# -----------------------------------------------------
# 3. FIBONACCI (Iterative)
# -----------------------------------------------------
print "--- 3. Fibonacci Sequence ---"

define fib with n do
    if n <= 0 then
        return 0
    end
    if n == 1 then
        return 1
    end
    set a to 0
    set b to 1
    set limit to n + 1
    for i in range 2 limit do
        set temp to a + b
        set a to b
        set b to temp
    end
    return b
end

print "First 10 Fibonacci numbers:"
for i in range 0 10 do
    set result to call fib i
    print result
end
print ""

# -----------------------------------------------------
# 4. NESTED LOOPS
# -----------------------------------------------------
print "--- 4. Nested Loops (Multiplication Table 3x3) ---"

for i in range 1 4 do
    for j in range 1 4 do
        set product to i * j
        print product
    end
end
print ""

# -----------------------------------------------------
# 5. NESTED CONDITIONALS
# -----------------------------------------------------
print "--- 5. Nested Conditionals ---"

define classify_positive with n do
    if n > 100 then
        print "large positive"
    else
        if n > 10 then
            print "medium positive"
        else
            print "small positive"
        end
    end
end

define classify_negative with n do
    if n < -100 then
        print "large negative"
    else
        if n < -10 then
            print "medium negative"
        else
            print "small negative"
        end
    end
end

define classify_number with n do
    if n > 0 then
        call classify_positive n
    else
        if n < 0 then
            call classify_negative n
        else
            print "zero"
        end
    end
end

print "classify 150:"
call classify_number 150
print "classify 50:"
call classify_number 50
print "classify 5:"
call classify_number 5
print "classify 0:"
call classify_number 0
print "classify -7:"
call classify_number -7
print "classify -200:"
call classify_number -200
print ""

# -----------------------------------------------------
# 6. ARRAYS OPERATIONS
# -----------------------------------------------------
print "--- 6. Arrays Operations ---"

set numbers to array 10 25 5 30 15 20

print "Array:"
print numbers

print "Length:"
print length numbers

print "First element (get 0):"
print get numbers 0

print "Third element (get 2):"
print get numbers 2

# Find max manually
set max_val to get numbers 0
set size to length numbers
for i in range 1 size do
    set current to get numbers i
    if current > max_val then
        set max_val to current
    end
end
print "Max value:"
print max_val

# Calculate sum
set total to 0
for i in range 0 size do
    set total to total + get numbers i
end
print "Sum:"
print total

# Modify array
put numbers 0 to 999
print "After put numbers[0] = 999:"
set temp to get numbers 0
print temp

append numbers 100
print "After append 100:"
print numbers
print ""

# -----------------------------------------------------
# 7. WHILE LOOP WITH BREAK/CONTINUE
# -----------------------------------------------------
print "--- 7. While Loop with Break/Continue ---"

print "Print only even numbers 0-10, stop at 8:"
set counter to 0
while counter <= 10 do
    if counter == 8 then
        print "Breaking at 8!"
        break
    end
    if counter % 2 != 0 then
        set counter to counter + 1
        continue
    end
    print counter
    set counter to counter + 1
end
print ""

# -----------------------------------------------------
# 8. COMPLEX NESTED FUNCTION
# -----------------------------------------------------
print "--- 8. Complex Nested Logic ---"

define is_prime with n do
    if n < 2 then
        return 0
    end
    if n == 2 then
        return 1
    end
    if n % 2 == 0 then
        return 0
    end
    set i to 3
    while i * i <= n do
        if n % i == 0 then
            return 0
        end
        set i to i + 2
    end
    return 1
end

print "Prime numbers from 1 to 30:"
for num in range 1 31 do
    set prime to call is_prime num
    if prime == 1 then
        print num
    end
end
print ""

# -----------------------------------------------------
# 9. STRING OPERATIONS
# -----------------------------------------------------
print "--- 9. String Operations ---"

set greeting to "Hello World"
print "Original:"
print greeting
print "Upper:"
print upper greeting
print "Lower:"
print lower greeting
print "Reversed:"
print reverse greeting
print "Length:"
print length greeting
print "Contains 'World':"
print contains greeting "World"
print ""

# -----------------------------------------------------
# 10. CORE LIBRARY FUNCTIONS
# -----------------------------------------------------
print "--- 10. Core Library Functions ---"

print "abs(-42):"
print abs -42
print "min(15, 8):"
print min 15 8
print "max(15, 8):"
print max 15 8
print "gcd(48, 18):"
print gcd 48 18
print "sqrt(144):"
print sqrt 144
print "factorial(6):"
print factorial 6
print "iseven(42):"
print iseven 42
print "isodd(37):"
print isodd 37
print ""

# -----------------------------------------------------
# 11. TIME LIBRARY
# -----------------------------------------------------
print "--- 11. Time Library ---"

print "Current date/time:"
print datetime
print "Year:"
print year
print "Month:"
print month
print "Day:"
print day
print "Hour:"
print hour
print "Minute:"
print minute
print ""

# -----------------------------------------------------
# 12. FIZZBUZZ (Classic Test)
# -----------------------------------------------------
print "--- 12. FizzBuzz (1-20) ---"

for num in range 1 21 do
    set div3 to num % 3
    set div5 to num % 5
    
    if div3 == 0 and div5 == 0 then
        print "FizzBuzz"
    else
        if div3 == 0 then
            print "Fizz"
        else
            if div5 == 0 then
                print "Buzz"
            else
                print num
            end
        end
    end
end
print ""

# -----------------------------------------------------
# FINAL SUMMARY
# -----------------------------------------------------
print "=== ALL TESTS COMPLETED ==="
print "If you see this, everything works!"
print datetime

