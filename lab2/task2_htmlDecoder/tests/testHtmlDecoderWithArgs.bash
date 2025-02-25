#!/bin/bash

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")
PROGRAMM="$SCRIPTPATH/../HtmlDecoder"

INPUT_PATH="$SCRIPTPATH/inputs"
OUTPUT_PATH="$SCRIPTPATH/outputs"
OUTPUT_FILE="output.txt"
ERROR_FILE="error.txt"

TEST_COUNT=0
PASS_COUNT=0

run_test_case() {
    local command="$1"
    local expected_output="$2"

    if [ ! -f "$expected_output" ]; then
        echo "Error: Output file '$expected_output' not found."
        return 1
    fi

    eval $command > "$ERROR_FILE"

    if [ $? -eq 1 ]; then
        cat "$ERROR_FILE" > "$OUTPUT_FILE"
    fi

    diff -q $OUTPUT_FILE "$expected_output"
    
    if [ $? -eq 0 ]; then
        echo "Test $TEST_COUNT Passed: Output matches $expected_output"
        rm "$ERROR_FILE"
        rm "$OUTPUT_FILE"
        return 0
    else
        echo "Test $TEST_COUNT Failed: Output differs from $expected_output"
        rm "$ERROR_FILE"
        rm "$OUTPUT_FILE"
        return 1
    fi
}

echo "Running tests..."

TEST_COUNT=$((TEST_COUNT + 1))
if run_test_case "$PROGRAMM $INPUT_PATH/input1.txt $OUTPUT_FILE" $OUTPUT_PATH/output1.txt; then
    PASS_COUNT=$((PASS_COUNT + 1))
fi

# TEST_COUNT=$((TEST_COUNT + 1))
# if run_test_case_crypt_decrypt "$PROGRAMM crypt $INPUT_PATH/input2.txt $OUTPUT_FILE1 40" $OUTPUT_PATH/output2.txt 40; then
#     PASS_COUNT=$((PASS_COUNT + 1))
# fi




# TEST_COUNT=$((TEST_COUNT + 1))
# if run_test_case_error "$PROGRAMM fail $INPUT_PATH/input3.txt $OUTPUT_FILE1 40" $OUTPUT_PATH/output3.txt; then
#     PASS_COUNT=$((PASS_COUNT + 1))
# fi

# TEST_COUNT=$((TEST_COUNT + 1))
# if run_test_case_error "$PROGRAMM crypt $INPUT_PATH/input4.txt" $OUTPUT_PATH/output4.txt; then
#     PASS_COUNT=$((PASS_COUNT + 1))
# fi

# TEST_COUNT=$((TEST_COUNT + 1))
# if run_test_case_error "$PROGRAMM crypt $INPUT_PATH/input5.txt $OUTPUT_FILE1 40 50" $OUTPUT_PATH/output5.txt; then
#     PASS_COUNT=$((PASS_COUNT + 1))
# fi

# TEST_COUNT=$((TEST_COUNT + 1))
# if run_test_case_error "$PROGRAMM crypt $INPUT_PATH/input6.txt $OUTPUT_FILE1 4000" $OUTPUT_PATH/output6.txt; then
#     PASS_COUNT=$((PASS_COUNT + 1))
# fi

# TEST_COUNT=$((TEST_COUNT + 1))
# if run_test_case_error "$PROGRAMM crypt $INPUT_PATH/input7.txt $INPUT_PATH/input7.txt 40" $OUTPUT_PATH/output7.txt; then
#     PASS_COUNT=$((PASS_COUNT + 1))
# fi

# TEST_COUNT=$((TEST_COUNT + 1))
# chmod 000 $INPUT_PATH/input8NotEnoughRights.txt
# if run_test_case_error "$PROGRAMM crypt $INPUT_PATH/input8NotEnoughRights.txt $OUTPUT_FILE1 40" $OUTPUT_PATH/output8.txt; then
#     PASS_COUNT=$((PASS_COUNT + 1))
# fi
# chmod 664 $INPUT_PATH/input8NotEnoughRights.txt

# TEST_COUNT=$((TEST_COUNT + 1))
# chmod 000 $OUTPUT_PATH/output9NotEnoughRights.txt
# if run_test_case_error "$PROGRAMM crypt $INPUT_PATH/input9.txt $OUTPUT_PATH/output9NotEnoughRights.txt 40" $OUTPUT_PATH/output9.txt; then
#     PASS_COUNT=$((PASS_COUNT + 1))
# fi
# chmod 664 $OUTPUT_PATH/output9NotEnoughRights.txt

# TEST_COUNT=$((TEST_COUNT + 1))
# if run_test_case_error "$PROGRAMM crypt $INPUT_PATH/notFoundFile.txt $OUTPUT_FILE1 40" $OUTPUT_PATH/outputFailedOpenFile.txt; then
#     PASS_COUNT=$((PASS_COUNT + 1))
# fi

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
