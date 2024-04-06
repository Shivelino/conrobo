#!/bin/bash

cd "$(dirname "$0")"/..
pwd

format_dos2unix() {
    echo -e "Running dos2unix     "
    find . -name "*\.h" -o -name "*\.cpp" | xargs -I {} sh -c "dos2unix '{}' 2>/dev/null; echo -e {}"
    echo
}

format_clang_format() {
    echo -e "Running clang-format "
    find . -name "*\.h" -o -name "*\.cpp" | xargs -I {} sh -c "clang-format -i {}; echo -e {}"
    echo
}

format_cmake_format() {
    echo -e "Running cmake-format "
    find . -name "CMakeLists.txt" -o -name "*\.cmake" | xargs -I {} sh -c "cmake-format --config .cmake-format -i {}; echo -e {}"
    echo
}

# format_dos2unix
format_clang_format
format_cmake_format
