cmake_minimum_required(VERSION 3.14)

project(hack-VM)

add_executable(VMtranslator
    src/codewriter.cc
    src/parser.cc
    main.cc
)

target_include_directories(VMtranslator
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# add_executable(parser_test
# )

# target_include_directories(parser_test
#     PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
# )

# target_link_libraries(parser_test
#     gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(parser_test)