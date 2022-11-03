add_library(container)

target_sources(container
  PRIVATE
    container.cpp
  PUBLIC
    vector.h
  )

target_include_directories(container
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)