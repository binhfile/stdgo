#!/bin/bash
#
# @author binhfile
# @brief Command for test project
#
CUR_DIR="$(dirname "$(readlink -e "$0")")"
BUILD_DIR="$CUR_DIR"/../_build
REPORT_DIR="$CUR_DIR"/../_report

function do_help(){
    echo "$0 <mode> <options>"
    echo "  UNITTEST"
    echo "  unittest <mode> <unittest options>"
    echo "           all"
    return
}

# @brief Check command is found in PATH
# @param $1 Command for check
# @return 1 Command is found in PATH
function do_check_existed() {
    if [[ -z "`which $1`" ]]; then
        return false
    fi
    return true
}

MODE="$1"
if [[ "$MODE" == "unittest" ]]; then
    "$CUR_DIR"/unittest/run.sh "$BUILD_DIR"/unittest "$REPORT_DIR" "${@:2}"
elif [[ "$MODE" == "benchmark" ]]; then
    "$CUR_DIR"/benchmark/run.sh "$BUILD_DIR"/benchmark "$REPORT_DIR" "${@:2}"
else
    do_help
fi
exit 0