#!/bin/bash

PROGRAM="../build/Procesor_CSS"

if [ ! -f "$PROGRAM" ]; then
    echo "Error: Program '$PROGRAM' not found."
    exit 1
fi

if [ $# -ne 1 ]; then
    echo "Usage: $0 <test_number>"
    exit 1
fi

test_number=$1
input_file="${test_number}.in"
output_file="${test_number}.out"

exec 3< "$output_file"
count=1
$PROGRAM < "$input_file" | while IFS= read -r line; do
    IFS= read -r expected <&3
    if [[ "$line" != "$expected" ]]; then
        echo "Difference found on line $count:"
        echo "Expected: $expected"
        echo "Actual  : $line"
#        break
    fi
    count=$((count + 1))
done
exec 3<&-