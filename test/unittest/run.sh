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
QT_DIR=""

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     MACHINE=Linux;;
    Darwin*)    MACHINE=Mac;;
    CYGWIN*)    MACHINE=Cygwin;;
    MINGW*)     MACHINE=MinGW;;
    *)          MACHINE="UNKNOWN:${unameOut}"
esac

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
function find_qt() {
    if [[ "$MACHINE" == "MinGW" ]];then
        QT_DIR="C:\\Qt\\Qt5.10.1\\5.10.1\\mingw53_32"
    else
        QT_DIR="/opt/Qt5.10.1/5.10.1/gcc_64"
    fi
    return 
}

function do_initialize() {
    mkdir -p "$BUILD_DIR"
    mkdir -p "$REPORT_DIR"
    return
}
# @param $1 source dir
# @param $2 destination dir
# @param $3 file name
function copy_file_if_not_existed() {
    if [[ ! -f "$2"/"$3" ]] && [[ ! -d "$2"/"$3" ]]; then
        cp -rf "$1"/"$3" "$2"/
    fi
    return
}
# @param $1 Qt dir
# @param $2 Install dir
function install_qt_depend() {
    if [[ "$MACHINE" == "MinGW" ]];then
        copy_file_if_not_existed "$1"/plugins "$2" platforms

        copy_file_if_not_existed "$1"/bin "$2" libEGL.dll
        copy_file_if_not_existed "$1"/bin "$2" libGLESv2.dll
        copy_file_if_not_existed "$1"/bin "$2" opengl32sw.dll
        copy_file_if_not_existed "$1"/bin "$2" libgcc_s_dw2-1.dll
        copy_file_if_not_existed "$1"/bin "$2" libstdc++-6.dll
        
        copy_file_if_not_existed "$1"/bin "$2" Qt5Core.dll
        copy_file_if_not_existed "$1"/bin "$2" Qt5Gui.dll
        copy_file_if_not_existed "$1"/bin "$2" Qt5Widgets.dll
        copy_file_if_not_existed "$1"/bin "$2" Qt5Charts.dll

        find "$2" -type f -name "*d.dll" | xargs rm
    fi
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
    find_qt
    if [[ -z "$CMAKE" ]];then
        echo "cmake not found"
        exit 1
    fi 
    if [[ -z "$MAKE" ]];then
        echo "make not found"
        exit 1
    fi 
    if [[ -z "$QT_DIR" ]];then
        echo "Qt not found"
        exit 1
    fi 

    cd "$BUILD_DIR"
    "$CMAKE" -G "Unix Makefiles" \
        -DCMAKE_MAKE_PROGRAM="$MAKE" \
        -DCMAKE_BUILD_TYPE=Release \
        -DMODE="$1" \
        -DGTEST_DIR="$CUR_DIR"/../../third_party/googletest/googletest \
        -DCMAKE_PREFIX_PATH="$QT_DIR" \
        "$CUR_DIR" || exit 1
    "$MAKE" -j4 || exit 1
    install_qt_depend "$QT_DIR" "$BUILD_DIR"
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"$QT_DIR"/lib
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
