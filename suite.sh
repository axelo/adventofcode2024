#!/bin/sh

set -e

failures=$((0))

testday () {
    NO_TRACE=1 ./run.sh "$1" "$2"

    answer_example=$("./$1$2.out" < "$1.example" | tail -n 1)

    if [ "$answer_example" = "$3" ]; then
        printf "%s%s - example - ok\n" "$1" "$2"
    else
        printf "%s%s - example - failed - expected %s, got %s\n" "$1" "$2" "$3" "$answer_example"
        failures=$((failures + 1))
    fi

    answer=$("./$1$2.out" < "$1.input" | tail -n 1)

    if [ "$answer" = "$4" ]; then
        printf "%s%s - input   - ok\n" "$1" "$2"
    else
        printf "%s%s - input   - failed - expected %s, got %s\n" "$1" "$2" "$4" "$answer"
        failures=$((failures + 1))
    fi
}

testday 01 a 11 1580061
testday 01 b 31 23046913
testday 02 a 2 383
testday 02 b 4 436
testday 03 a 161 185797128
testday 03 b 48 89798695

if [ $failures -eq 0 ]; then
    printf 'success\n'
else
    printf '%s failed\n' "$failures"
    exit 1
fi
