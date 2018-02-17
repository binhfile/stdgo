#!/bin/bash
#
# @author binhfile
# @brief Command for unittest
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

CMAKE=""
MAKE=""

function find_cmake() {
    CMAKE="`which cmake 2>/dev/null`"
    if [[ -z "$CMAKE" ]]; then
        CMAKE="`which cmake3 2>/dev/null`"
    fi
    return
}
function find_make() {
    MAKE="`which make 2>/dev/null`"
    if [[ -z "$MAKE" ]]; then
        MAKE="`which mingw32-make 2>/dev/null`"
    fi
    return
}

function do_initialize() {
    mkdir -p "$BUILD_DIR"
    mkdir -p "$REPORT_DIR"
    return
}

# @param $1 mode
function do_run() {
    if [[ ! -d "$BUILD_DIR" ]]; then
        echo "$BUILD_DIR is not existed" 1>&2
        exit 1
    fi 
    find_cmake
    find_make
    if [[ -z "$CMAKE" ]];then
        echo "cmake not found"
        exit 1
    fi 

    cd "$BUILD_DIR"
    "$CMAKE" -G "Unix Makefiles" \
        -DCMAKE_MAKE_PROGRAM="$MAKE" \
        -DCMAKE_BUILD_TYPE=Release \
        -DMODE="$1" \
        -DGTEST_DIR="$CUR_DIR"/../../third_party/googletest/googletest \
        "$CUR_DIR" || exit 1
    "$MAKE" -j4 || exit 1
    ./unittest 
    return
}
function do_clean() {
    if [[ ! -d "$BUILD_DIR" ]]; then
        echo "$BUILD_DIR is not existed" 1>&2
        exit 1
    fi 
    rm -rf "$BUILD_DIR"
    return
}

do_initialize

MODE="$3"
if [[ "$MODE" == "clean" ]];then
    do_clean
    exit 0
fi

do_run "${@:3}"