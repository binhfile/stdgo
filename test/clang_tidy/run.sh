#!/bin/bash
#
# @author binhfile
# @brief Command for clang-tidy
# 
# $1 build dir
# $2 report dir
# ${@:3} options...
#
CUR_DIR="$(dirname "$(readlink -e "$0")")"
BUILD_DIR="$CUR_DIR"/_build
REPORT_DIR="$CUR_DIR"/_report

if [[ ! -z "$1" ]]; then
    BUILD_DIR="$1"
fi

if [[ ! -z "$2" ]]; then
    REPORT_DIR="$2"
fi

function find_python() {
    PYTHON="`which python 2>/dev/null`"
    if [[ -z "$PYTHON" ]]; then
        PYTHON="`which python3 2>/dev/null`"
    fi
    return
}
function find_go() {
    GO="`which go 2>/dev/null`"
    return
}
function do_clang_tidy() {
    find_python
    find_go

    if [[ -z "$PYTHON" ]]; then
        echo "python not found"
        exit 1
    fi
    if [[ -z "$GO" ]]; then
        echo "go not found"
        exit 1
    fi

	EXCLUDE="googletest,/usr,_test"
    DB_PATH="$BUILD_DIR/unittest"

    if [[ ! -f "$DB_PATH/compile_commands.json" ]]; then
        echo "$DB_PATH/compile_commands.json not found"
        exit 1
    fi 
	
    "$PYTHON" "$CUR_DIR"/clang-tidy.py  \
        -checks="*,-llvm-header-guard" \
        -header-filter=.*  \
        -p "$DB_PATH" 2>"$BUILD_DIR"/clang_tody_py.err.log > "$BUILD_DIR"/clang_tidy_raw.txt
    "$GO" run "$CUR_DIR"/clang_tidy_parser.go -input="$BUILD_DIR"/clang_tidy_raw.txt \
        -exclude="$EXCLUDE" > "$REPORT_DIR"/clang_tidy.txt
    cat "$REPORT_DIR"/clang_tidy.txt
    return
}

do_clang_tidy 
