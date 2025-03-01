cmake_minimum_required(VERSION 3.10)
project(multi_threaded_programming)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Threads package
find_package(Threads REQUIRED)

# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Banking System executable
add_executable(banking_system
    src/banking/main.cpp
    src/banking/account.cpp
    src/banking/bank.cpp
)

# IPC executables
add_executable(producer src/ipc/producer.cpp)
add_executable(consumer src/ipc/consumer.cpp)

# Tests
enable_testing()

# Banking system tests
add_executable(banking_tests
    tests/banking/account_test.cpp
    tests/banking/bank_test.cpp
    src/banking/account.cpp
    src/banking/bank.cpp
)
target_include_directories(banking_tests PRIVATE src)
target_link_libraries(banking_tests
    GTest::gtest_main
    Threads::Threads
)

# IPC tests
add_executable(ipc_tests
    tests/ipc/pipe_test.cpp
)
target_link_libraries(ipc_tests PRIVATE
    gtest_main
    Threads::Threads
)

include(GoogleTest)
gtest_discover_tests(banking_tests)
gtest_discover_tests(ipc_tests)