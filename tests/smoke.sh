#!/bin/sh
# Run from the repository root after building the examples.
set -eu
expect() {
    expected=$1; shift
    actual=$("$@")
    if [ "$actual" != "$expected" ]; then
        printf '%s: expected "%s", got "%s"\n' "$*" "$expected" "$actual" >&2
        exit 1
    fi
}
expect '71.7' ./build/average
expect 'Word is a palindrome!' ./build/palindrome radar
expect 'Word is a NOT palindrome!' ./build/palindrome abcd
expect '32.000000 F' ./build/temperature 0 C
expect '171' ./build/euler19
expect '210' ./build/euler40
(cd euler13 && expect 'Sum (52 digits): 5537376230390876637302048746832985971773659831892672
Sum (first 10 digits): 5537376230' ../build/euler13)
(cd maze && ../build/maze m1.txt) | grep -q 'Found maze path'
