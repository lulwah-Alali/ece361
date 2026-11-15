#!/bin/sh

passed=0
failed=0

for input in inputs/*; do
    [ -f "$input" ] || continue

    name=$(basename "$input")
    expected="expected/$name"

    if [ ! -f "$expected" ]; then
        echo "FAIL: $name (missing expected output)"
        failed=$((failed + 1))
        continue
    fi

    actual=$(mktemp)
    ./balance < "$input" > "$actual"
    status=$?

    expected_status=$(head -n 1 "$expected")
    tail -n +2 "$expected" > "$actual.expected"

    if [ "$status" -eq "$expected_status" ] &&
       diff -q "$actual" "$actual.expected" > /dev/null; then
        echo "PASS: $name"
        passed=$((passed + 1))
    else
        echo "FAIL: $name"
        failed=$((failed + 1))
    fi

    rm -f "$actual" "$actual.expected"
done

echo "Passed: $passed"
echo "Failed: $failed"

[ "$failed" -eq 0 ] && [ "$passed" -ge 6 ]
