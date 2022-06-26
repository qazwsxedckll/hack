cmake_minimum_required(VERSION 3.14)

project(jackcompiler)

add_executable(jackcompiler
    main.cc
    src/jack_analyzer.cc
    src/jack_tokenizer.cc
    src/compilation_engine.cc
)

target_include_directories(jackcompiler
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(TARGETS jackcompiler
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(jack_analyzer_test
    src/jack_analyzer.cc
    src/jack_tokenizer.cc
    test/jack_analyzer_test.cc
)

target_include_directories(jack_analyzer_test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(jack_analyzer_test
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(jack_analyzer_test)