# FetchContent_Declare(
#     pugixml
#     GIT_REPOSITORY https://github.com/zeux/pugixml.git
#     GIT_TAG        v1.12.1
# )
# FetchContent_MakeAvailable(pugixml)

add_executable(jackcompiler
    main.cc
    src/jack_analyzer.cc
    src/jack_tokenizer.cc
    src/compilation_engine.cc
)

target_include_directories(jackcompiler
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(jackcompiler
    GTest::gtest_main
)

install(TARGETS jackcompiler
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(jack_analyzer_test
    src/jack_analyzer.cc
    src/jack_tokenizer.cc
    src/compilation_engine.cc
    test/jack_analyzer_test.cc
)

target_include_directories(jack_analyzer_test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(jack_analyzer_test
    GTest::gtest_main
)

add_executable(jack_tokenizer_test
    src/jack_analyzer.cc
    src/jack_tokenizer.cc
    src/compilation_engine.cc
    test/jack_tokenizer_test.cc
)

target_include_directories(jack_tokenizer_test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(jack_tokenizer_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(jack_analyzer_test)
gtest_discover_tests(jack_tokenizer_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test
)