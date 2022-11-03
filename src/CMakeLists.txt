add_library(container)

target_sources(container
  PRIVATE
    example.cpp
    vector.cpp
  PUBLIC
    vector.h
    example.h
)

target_include_directories(container
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)