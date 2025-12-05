# =====================================================
# Wordlang Comprehensive Test
# Tests: Classes, Methods, If/Elseif, Nested If, Imports
# =====================================================

print "=========================================="
print "   WORDLANG COMPREHENSIVE TEST SUITE"
print "=========================================="
print ""

# -----------------------------------------------------
# 1. IMPORT TEST
# -----------------------------------------------------
print "=== 1. IMPORT TEST ==="

# Import standard library
import arrays

print "Imported arrays library"
print ""

# -----------------------------------------------------
# 2. CLASS WITH METHODS
# -----------------------------------------------------
print "=== 2. CLASS TEST ==="

class Calculator do
    method add with a b do
        return a + b
    end
    
    method subtract with a b do
        return a - b
    end
    
    method multiply with a b do
        return a * b
    end
    
    method divide with a b do
        if b == 0 then
            return 0
        else
            return a / b
        end
    end
    
    method grade with score do
        if score >= 90 then
            return 5
        elseif score >= 80 then
            return 4
        elseif score >= 70 then
            return 3
        elseif score >= 60 then
            return 2
        else
            return 1
        end
    end
    
    method classify with n do
        if n > 0 then
            if n > 100 then
                return 3
            elseif n > 10 then
                return 2
            else
                return 1
            end
        else
            if n < -100 then
                return -3
            elseif n < -10 then
                return -2
            else
                return -1
            end
        end
    end
end

set calc to new Calculator

print "calc > add 25 17:"
print calc > add 25 17

print "calc > subtract 100 35:"
print calc > subtract 100 35

print "calc > multiply 8 7:"
print calc > multiply 8 7

print "calc > divide 144 12:"
print calc > divide 144 12

print "calc > divide 10 0 (safe):"
print calc > divide 10 0

print ""
print "Grade tests:"
print "calc > grade 95:"
print calc > grade 95
print "calc > grade 82:"
print calc > grade 82
print "calc > grade 71:"
print calc > grade 71
print "calc > grade 55:"
print calc > grade 55

print ""
print "Classify tests (nested if):"
print "calc > classify 150:"
print calc > classify 150
print "calc > classify 50:"
print calc > classify 50
print "calc > classify 5:"
print calc > classify 5
print "calc > classify -200:"
print calc > classify -200
print "calc > classify -50:"
print calc > classify -50
print ""

# -----------------------------------------------------
# 3. STANDALONE FUNCTIONS WITH ELSEIF
# -----------------------------------------------------
print "=== 3. FUNCTION TEST ==="

define fizzbuzz with n do
    set result to 0
    if n % 15 == 0 then
        set result to 15
    elseif n % 5 == 0 then
        set result to 5
    elseif n % 3 == 0 then
        set result to 3
    else
        set result to n
    end
    return result
end

print "fizzbuzz tests:"
print "fizzbuzz 15:"
print call fizzbuzz 15
print "fizzbuzz 10:"
print call fizzbuzz 10
print "fizzbuzz 9:"
print call fizzbuzz 9
print "fizzbuzz 7:"
print call fizzbuzz 7
print ""

# -----------------------------------------------------
# 4. NESTED IF IN FUNCTIONS
# -----------------------------------------------------
print "=== 4. NESTED IF TEST ==="

define check_range with x y do
    if x > 0 then
        if y > 0 then
            return 1
        else
            return 2
        end
    else
        if y > 0 then
            return 3
        else
            return 4
        end
    end
end

print "check_range tests:"
print "check_range 5 10:"
print call check_range 5 10
print "check_range 5 -10:"
print call check_range 5 -10
print "check_range -5 10:"
print call check_range -5 10
print "check_range -5 -10:"
print call check_range -5 -10
print ""

# -----------------------------------------------------
# 5. COMPLEX NESTED LOGIC
# -----------------------------------------------------
print "=== 5. COMPLEX LOGIC TEST ==="

define analyze with a b c do
    if a > b then
        if a > c then
            if b > c then
                return 1
            else
                return 2
            end
        else
            return 3
        end
    elseif b > c then
        if a > c then
            return 4
        else
            return 5
        end
    else
        return 6
    end
end

print "analyze tests:"
print "analyze 30 20 10:"
print call analyze 30 20 10
print "analyze 30 10 20:"
print call analyze 30 10 20
print "analyze 20 30 10:"
print call analyze 20 30 10
print "analyze 10 20 30:"
print call analyze 10 20 30
print ""

# -----------------------------------------------------
# 6. ARRAYS WITH FUNCTIONS
# -----------------------------------------------------
print "=== 6. ARRAYS TEST ==="

set numbers to array 10 25 5 30 15 20 8

print "Array:"
print numbers

print "Length:"
print length numbers

# Find max using loop
define find_max with arr do
    set max_val to get arr 0
    set i to 1
    while i < length arr do
        set current to get arr i
        if current > max_val then
            set max_val to current
        end
        set i to i + 1
    end
    return max_val
end

# Note: arrays can't be passed to functions directly,
# so we work with the global array
set max_val to get numbers 0
for i in range 1 7 do
    set current to get numbers i
    if current > max_val then
        set max_val to current
    end
end
print "Max value:"
print max_val

# Sum
set total to 0
for i in range 0 7 do
    set total to total + get numbers i
end
print "Sum:"
print total
print ""

# -----------------------------------------------------
# 7. LOOPS WITH CONDITIONALS
# -----------------------------------------------------
print "=== 7. LOOPS TEST ==="

print "Even numbers 0-10:"
for i in range 0 11 do
    if i % 2 == 0 then
        print i
    end
end

print ""
print "Countdown with break at 3:"
set counter to 10
while counter > 0 do
    if counter == 3 then
        print "Breaking!"
        break
    end
    print counter
    set counter to counter - 1
end
print ""

# -----------------------------------------------------
# 8. CORE LIBRARY FUNCTIONS
# -----------------------------------------------------
print "=== 8. CORE LIBRARY TEST ==="

print "Math:"
print "abs(-42):"
print abs -42
print "min(15, 8):"
print min 15 8
print "max(15, 8):"
print max 15 8
print "sqrt(144):"
print sqrt 144
print "gcd(48, 18):"
print gcd 48 18

print ""
print "Time:"
print "Current datetime:"
print datetime
print "Day:"
print day
print "Hour:"
print hour

print ""
print "String:"
set msg to "Hello World"
print "Original:"
print msg
print "Upper:"
print upper msg
print "Reverse:"
print reverse msg
print ""

# -----------------------------------------------------
# 9. SECOND CLASS TEST
# -----------------------------------------------------
print "=== 9. MULTI-CLASS TEST ==="

class Person do
    method greet do
        return 1
    end
    
    method check_age with age do
        if age >= 18 then
            if age >= 65 then
                return 3
            else
                return 2
            end
        else
            return 1
        end
    end
end

set person to new Person

print "person > greet:"
print person > greet

print "person > check_age 70:"
print person > check_age 70

print "person > check_age 30:"
print person > check_age 30

print "person > check_age 15:"
print person > check_age 15
print ""

# -----------------------------------------------------
# FINAL SUMMARY
# -----------------------------------------------------
print "=========================================="
print "   ALL TESTS COMPLETED SUCCESSFULLY!"
print "=========================================="
print ""
print "Test completed at:"
print datetime

