cmake_minimum_required(VERSION 3.10)
project(multi_threaded_programming)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)

# Banking System executable
add_executable(banking_system
    src/banking/main.cpp
    src/banking/account.cpp
    src/banking/bank.cpp
)

# Link with pthread
target_link_libraries(banking_system PRIVATE Threads::Threads)

# IPC executables
add_executable(producer src/ipc/producer.cpp)
add_executable(consumer src/ipc/consumer.cpp) 