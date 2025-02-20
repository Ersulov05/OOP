#!/bin/bash

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
PROGRAMM="$SCRIPTPATH/../Replace"

INPUT_PATH="$SCRIPTPATH/inputs"
OUTPUT_PATH="$SCRIPTPATH/outputs"
OUTPUT_FILE="output.txt"

TEST_COUNT=0
PASS_COUNT=0

run_test_case() {
    local command="$1"
    local expected_output="$2"

    if [ ! -f "$expected_output" ]; then
        echo "Error: Output file '$expected_output' not found."
        return 1
    fi

    eval $command > $OUTPUT_FILE

    diff -q $OUTPUT_FILE "$expected_output"
    
    if [ $? -eq 0 ]; then
        echo "Test $TEST_COUNT Passed: Output matches $expected_output"
        return 0
    else
        echo "Test $TEST_COUNT Failed: Output differs from $expected_output"
        return 1
    fi
}

echo "Running tests..."

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/inputArg1.txt $OUTPUT_FILE ma mama" $OUTPUT_PATH/outputArg1.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
EMPTY_STRING=""
if run_test_case "$PROGRAMM $INPUT_PATH/inputArg2.txt $OUTPUT_FILE string ''" $OUTPUT_PATH/outputArg2.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/inputArg4.txt $OUTPUT_FILE 1231234 XYZ" $OUTPUT_PATH/outputArg4.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/inputArg5.txt $OUTPUT_FILE 123 456" $OUTPUT_PATH/outputArg5.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
ARG5=$(cat "$INPUT_PATH/arg5.txt")
if run_test_case "$PROGRAMM $INPUT_PATH/notFoundFile.txt $OUTPUT_FILE 123 456" $OUTPUT_PATH/error.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/inputArg3.txt $OUTPUT_FILE ma" $OUTPUT_PATH/error.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/inputArg3.txt $OUTPUT_FILE" $OUTPUT_PATH/error.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/inputArg3.txt" $OUTPUT_PATH/error.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
chmod 000 $INPUT_PATH/inputArg6NotEnoughRules.txt
if run_test_case "$PROGRAMM $INPUT_PATH/inputArg6NotEnoughRules.txt $OUTPUT_FILE 123 456" $OUTPUT_PATH/outputArg6.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi
chmod 644 $INPUT_PATH/inputArg6NotEnoughRules.txt

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
