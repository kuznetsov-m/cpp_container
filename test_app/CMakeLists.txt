add_executable(test_app
    main.cpp
    ../test/test_object.h
    ../test/test_object.cpp
)

target_link_libraries(test_app PRIVATE container)

# set_target_properties(test_app PROPERTIES C_STANDARD 17 C_STANDARD_REQUIRED ON)