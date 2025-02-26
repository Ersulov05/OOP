#!/bin/bash

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")

RED='\033[0;31m'  # Код для красного цвета
GREEN='\033[0;32m' # Код для зеленого цвета
NC='\033[0m'      # Код для сброса цвета

INPUT_PATH="$SCRIPTPATH/inputs"
OUTPUT_PATH="$SCRIPTPATH/outputs"

TEST_COUNT=0
PASS_COUNT=0

test_replace_with_files() {
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

    $SCRIPTPATH/../Replace < "$input_file" > temp.txt

    diff -q temp.txt "$output_file" > /dev/null 2>&1
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Test $TEST_COUNT Passed${NC}: Output matches $expected_output"
        rm temp.txt
        return 0
    else
        echo -e "${RED}Test $TEST_COUNT Failed${NC}: Output differs from $expected_output"
        rm temp.txt
        return 1
    fi
}

echo "Running tests..."

TEST_COUNT=$((TEST_COUNT + 1))
if test_replace_with_files "$INPUT_PATH/input1.txt" "$OUTPUT_PATH/output1.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_replace_with_files "$INPUT_PATH/input2.txt" "$OUTPUT_PATH/output2.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_replace_with_files "$INPUT_PATH/input3.txt" "$OUTPUT_PATH/output3.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_replace_with_files "$INPUT_PATH/input4.txt" "$OUTPUT_PATH/output4.txt"; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if test_replace_with_files "$INPUT_PATH/input5.txt" "$OUTPUT_PATH/output5.txt"; then
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
