#!/usr/bin/python

import sys

def fib(n):    # write Fibonacci series up to n
    a, b = 0, 1
    while b < n:
        print b,
        a, b = b, a+b

def fib2(n):   # return Fibonacci series up to n
    result = []
    a, b = 0, 1
    while b < n:
        result.append(b)
        a, b = b, a+b
    return result


def main():
    fib(int(sys.argv[1])) #note that we're taking a command line argument
    print "\n",
    f = fib2(int(sys.argv[1])) #argv[0] is the name of the python file
    print f


if __name__ == "__main__":
    main()
