# CMakeList.txt : CMake project for CLITetris, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories("include" "src")

# Add source to this project's executable.
add_executable (CLITetris "src/CLITetris.cpp" "include/CLITetris.h" "include/Piece.h" "src/Piece.cpp" "src/Main.cpp" "include/Main.h" "include/Config.h" "src/Config.cpp")

# TODO: Add tests and install targets if needed.
