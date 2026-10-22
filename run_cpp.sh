#!/usr/bin/env bash
set -e

if [ $# -lt 1 ]; then
    echo "Usage: $0 <path_to_cpp_file> [args...]" >&2
    exit 1
fi

CPP_FILE="$1"

if [ ! -f "$CPP_FILE" ]; then
    echo "Error: File '$CPP_FILE' not found." >&2
    exit 1
fi

EXECUTABLE="${CPP_FILE%.*}.out"
if [[ "$EXECUTABLE" != */* ]]; then
    EXECUTABLE="./$EXECUTABLE"
fi

cleanup() {
    rm -f "$EXECUTABLE"
}

trap cleanup EXIT INT TERM

g++ -std=c++20 "$CPP_FILE" -o "$EXECUTABLE"

"$EXECUTABLE" "${@:2}"
