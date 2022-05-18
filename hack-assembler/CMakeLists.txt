cmake_minimum_required(VERSION 3.14)

project(hack-assembler)

add_executable(assembler
    src/code.cc
    src/parser.cc
    src/symboltable.cc
    main.cc
)

target_include_directories(assembler
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(TARGETS assembler
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(parser_test
    test/parser_test.cc
    src/parser.cc
)

target_include_directories(parser_test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(parser_test
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(parser_test)