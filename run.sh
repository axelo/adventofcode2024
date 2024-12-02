#!/bin/sh

set -e -o pipefail

if [[ -nz "${NO_TRACE:-}" ]]; then
    set +x
else
    set -x
fi

cc -std=c17 -Werror -Wall -Wpedantic -Wconversion -Wswitch-enum -Wno-unused-function -fsanitize=undefined,integer,nullability -O3 -g "$1$2.c" -o "$1$2.out"

if [ -n "$3" ]; then
    "./$1$2.out" < "$1.$3"
fi
