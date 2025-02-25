#!/bin/bash

run_test_case() {
  local command="$1"
  local expected_output="$2"

  local actual_output=$($command)
  actual_output=$(echo -n "$actual_output")

  if [ "$actual_output" == "$expected_output" ]; then
    echo "Test Passed: Command '$command' outputted '$actual_output'"
    return 0
  else
    echo "Test Failed: For command '$command', expected '$expected_output', but got '$actual_output'"
    return 1
  fi
}

TEST_COUNT=0
PASS_COUNT=0

echo "Running tests..."

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 16 10 ff" "255"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 10 2 10" "1010"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 2 10 1010" "10"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 10 16 255" "FF"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 10 2 -10" "-1010"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 16 10 -1F" "-31"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 10 16 0" "0"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 10 37 0" "ERROR"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 6 9 8" "ERROR"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 1 9 0" "ERROR"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 5 h 3" "ERROR"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 1 9" "ERROR"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 1 9 0 34" "ERROR"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 10 16 2147483647" "7FFFFFFF"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 10 16 -2147483647" "-7FFFFFFF"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "./Radix 10 16 2147483648" "ERROR"; then
  PASS_COUNT=$((PASS_COUNT + 1))
fi

echo ""
echo "----------------------------"
echo "Total tests: $TEST_COUNT"
echo "Tests passed: $PASS_COUNT"
echo "Tests failed: $((TEST_COUNT - PASS_COUNT))"

if [ "$PASS_COUNT" -ne "$TEST_COUNT" ]; then
  exit 1
else
  exit 0
fi
