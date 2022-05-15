cmake_minimum_required(VERSION 3.14)

project(hack-assembler)

add_executable(assembler
    src/code.cc
    src/parser.cc
    src/symboltable.cc
    main.cc
)

target_include_directories(assembler
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
