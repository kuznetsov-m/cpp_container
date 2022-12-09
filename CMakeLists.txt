cmake_minimum_required(VERSION 3.17)
# project(cpp-container LANGUAGES CXX)
project(cpp-container VERSION 1.0.0)

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(container)

enable_testing()
add_subdirectory(test)

add_subdirectory(test_app)