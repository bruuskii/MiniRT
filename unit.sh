#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
BOLD='\033[1m'

TOTAL_TESTS=0
PASSED_TESTS=0

run_test() {
    local scene_file=$1
    local expected_status=0
    local test_name=$(basename "$scene_file")
    
    if [[ $test_name == error_* ]]; then
        expected_status=1
    fi
    
    ./miniRT "$scene_file" > /dev/null 2>&1
    local actual_status=$?
    
    ((TOTAL_TESTS++))
    
    if [[ ($expected_status == 0 && $actual_status == 0) || 
          ($expected_status != 0 && $actual_status != 0) ]]; then
        echo -e "${GREEN}✓${NC} Test passed: ${BOLD}$test_name${NC}"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}✗${NC} Test failed: ${BOLD}$test_name${NC}"
        echo "   Expected status: $expected_status, Got: $actual_status"
    fi
}


if [ ! -x "./miniRT" ]; then
    echo -e "${RED}Error: miniRT executable not found or not executable${NC}"
    exit 1
fi

if [ ! -d "./scenes" ]; then
    echo -e "${RED}Error: scenes directory not found${NC}"
    exit 1
fi

echo -e "${BOLD}Running MiniRT Test Suite${NC}"
echo "================================"

for scene in ./scenes/*; do
    if [ -f "$scene" ]; then
        run_test "$scene"
    fi
done

echo "================================"
echo -e "${BOLD}Test Summary${NC}"
echo "Total tests: $TOTAL_TESTS"
echo "Passed tests: $PASSED_TESTS"
echo "Failed tests: $((TOTAL_TESTS - PASSED_TESTS))"

if [ $PASSED_TESTS -ne $TOTAL_TESTS ]; then
    exit 1
fi

exit 0
