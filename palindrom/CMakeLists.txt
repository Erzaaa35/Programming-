cmake_minimum_required(VERSION 3.10)
project(Palindrom C)

set(CMAKE_C_STANDARD 99)

add_executable(palindrome src/main.c src/palindrome.c)

target_include_directories(palindrome PRIVATE ${CMAKE_SOURCE_DIR}/src) 