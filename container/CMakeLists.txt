add_library(container STATIC
    vector.h
    vector.cpp
)

target_include_directories(container PUBLIC "${CMAKE_CURRENT_LIST_DIR}")