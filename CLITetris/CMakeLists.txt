﻿# CMakeList.txt : CMake project for CLITetris, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories("include" "src")

# Add source to this project's executable.
add_executable (
	CLITetris
	"include/CLITetris.h"
	"src/CLITetris.cpp"
	"include/Piece.h" 
	"src/Piece.cpp"
	"include/Game.h"
	"src/Game.cpp"
	"include/Config.h"
	"src/Config.cpp"
	"include/Printer.h"
	"src/Printer.cpp" "include/Global.h" "include/Menu.h" "src/Menu.cpp")
# TODO: Add tests and install targets if needed.


find_path(PDCURSES_INCLUDE curses.h)
find_library(PDCURSES_LIBRARY pdcurses)

target_include_directories(
	CLITetris PRIVATE ${PDCURSES_INCLUDE}
)

target_link_libraries(
	CLITetris PRIVATE ${PDCURSES_LIBRARY} 
)
