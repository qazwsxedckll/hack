cmake_minimum_required(VERSION 3.14)

project(hack)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(INSTALL_GTEST OFF)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(hack-assembler)
add_subdirectory(hack-VM)
add_subdirectory(jack-compiler)