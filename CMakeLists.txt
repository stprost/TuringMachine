cmake_minimum_required(VERSION 3.10)
project(TuringMachine C)

set(CMAKE_C_STANDARD 99)

add_executable(TuringMachine main.c header.h step.c output.c in.c )