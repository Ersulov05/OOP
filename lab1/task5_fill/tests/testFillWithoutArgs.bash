#!/bin/bash

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
PROGRAM_PATH_ABS="../Fill"

INPUT_PATH="$SCRIPTPATH/inputs"
OUTPUT_PATH="$SCRIPTPATH/outputs"
TEMP_FILE="temp.txt"

TEST_COUNT=0
PASS_COUNT=0

test_run_case() {
    local input_file="$1"
    local output_file="$2"

    if [ ! -f "$input_file" ]; then
        echo "Error: Input file '$input_file' not found."
        return 1
    fi

    if [ ! -f "$output_file" ]; then
        echo "Error: Output file '$output_file' not found."
        return 1
    fi

    $SCRIPTPATH/$PROGRAM_PATH_ABS < "$input_file" > "$TEMP_FILE"

    diff -q "$TEMP_FILE" "$output_file"
    
    if [ $? -eq 0 ]; then
        echo "Test $TEST_COUNT Passed: Output matches $output_file"
        rm "$TEMP_FILE"
        return 0
    else
        echo "Test $TEST_COUNT Failed: Output differs from $output_file"
        # rm "$TEMP_FILE"
        return 1
    fi
}

echo "Running tests..."

TEST_COUNT=$((TEST_COUNT + 1))
if test_run_case "$INPUT_PATH/input1.txt" "$OUTPUT_PATH/output1.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_run_case "$INPUT_PATH/input2.txt" "$OUTPUT_PATH/output2.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_run_case "$INPUT_PATH/input3.txt" "$OUTPUT_PATH/output3.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_run_case "$INPUT_PATH/input4.txt" "$OUTPUT_PATH/output4.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_run_case "$INPUT_PATH/input5.txt" "$OUTPUT_PATH/output5.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_run_case "$INPUT_PATH/input6.txt" "$OUTPUT_PATH/output6.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_run_case "$INPUT_PATH/input7.txt" "$OUTPUT_PATH/output7.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_run_case "$INPUT_PATH/input8.txt" "$OUTPUT_PATH/output8.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_run_case "$INPUT_PATH/input9.txt" "$OUTPUT_PATH/output9.txt"; then
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
