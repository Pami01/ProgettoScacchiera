cmake_minimum_required(VERSION 3.0)

project(ProgettoScacchiera)

include_directories(include src executables)

add_library(piece include/piece.h src/piece.cpp)
add_library(board include/board.h src/board.cpp)
add_library(position include/position.h src/position.cpp)

add_executable(scacchiera executables/scacchiera.cpp src/piece.cpp src/board.cpp src/position.cpp)

target_link_libraries(scacchiera piece board position)
