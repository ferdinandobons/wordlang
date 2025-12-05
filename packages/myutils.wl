# myutils - Custom Wordlang Package
# Example package with utility functions

define double with n do
    return n * 2
end

define triple with n do
    return n * 3
end

define greet with name do
    set msg to concat "Hello, " name "!"
    print msg
end

define countdown_from with n do
    while n > 0 do
        print n
        set n to n - 1
    end
    print "Liftoff!"
end
