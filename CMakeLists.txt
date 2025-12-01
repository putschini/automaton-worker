cmake_minimum_required(VERSION 3.5.0)

project( automaton )

set (CMAKE_CXX_COMPILER g++ )
set (CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


include_directories(
        src/automaton
        src/grammar
        src/utils
        src/regex
)

file(GLOB SOURCE "./src/*/*.cpp")

add_executable( automaton ${SOURCE} src/main.cpp )

