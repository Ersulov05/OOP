#!/bin/bash

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
PROGRAMM="$SCRIPTPATH/../Invert"

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
        rm "$OUTPUT_FILE"
        return 0
    else
        echo "Test $TEST_COUNT Failed: Output differs from $expected_output"
        rm "$OUTPUT_FILE"
        return 1
    fi
}

echo "Running tests..."

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/input1.txt" $OUTPUT_PATH/output1.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
EMPTY_STRING=""
if run_test_case "$PROGRAMM $INPUT_PATH/input2.txt" $OUTPUT_PATH/output2.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/input3.txt" $OUTPUT_PATH/output3.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/input4.txt" $OUTPUT_PATH/output4.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/input5.txt" $OUTPUT_PATH/output5.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi


TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/input6.txt" $OUTPUT_PATH/output6.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/input7Arg.txt invalidArgument" $OUTPUT_PATH/output7Arg.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

TEST_COUNT=$((TEST_COUNT + 1))
chmod 000 $INPUT_PATH/input8ArgNotEnoughRights.txt
if run_test_case "$PROGRAMM $INPUT_PATH/input8ArgNotEnoughRights.txt" $OUTPUT_PATH/outputFailedOpenFile.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi
chmod 664 $INPUT_PATH/input8ArgNotEnoughRights.txt

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/notFoundFile.txt" $OUTPUT_PATH/outputFailedOpenFile.txt; then
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
