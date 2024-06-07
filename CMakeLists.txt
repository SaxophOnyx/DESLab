cmake_minimum_required(VERSION 3.28.0)
project(deslab VERSION 0.1.0 LANGUAGES C)

file(GLOB_RECURSE SOURCES
  src/*.c
  src/*.h
)

add_executable(deslab ${SOURCES})