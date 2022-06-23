cmake_minimum_required(VERSION 3.14)

project(jackcompiler)

add_executable(jackcompiler
    main.cc
    src/utils.cc
    src/jacktokenizer.cc
)

target_include_directories(jackcompiler
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(TARGETS jackcompiler
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
)


add_executable(utils_test
    test/utils_test.cc
    src/utils.cc
)

target_include_directories(utils_test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(utils_test
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(utils_test)