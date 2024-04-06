#!/bin/bash

cd "$(dirname "$0")"/..
pwd

check_clang_format() {
  echo -e "Running clang-format check "
  find . -name "*\.h" -o -name "*\.cpp" | xargs clang-format -output-replacements-xml | grep -q '<replacement>' && echo "Files do not meet the format requirements." || echo "Files meet the format requirements."
  echo
}

check_cmake_format() {
  echo -e "Running cmake-format check "
  find . -name "CMakeLists.txt" -o -name "*\.cmake" | xargs cmake-format --config .cmake-format --check | grep -q "reformatted" && echo "Files do not meet the format requirements." || echo "Files meet the format requirements."
  echo
}

check_clang_format
check_cmake_format
