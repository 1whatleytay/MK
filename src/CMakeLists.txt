add_subdirectory(util)
add_subdirectory(resources)
add_subdirectory(nodes)

add_executable(improv
    builder.h
    builder.cpp

    main.cpp)
target_link_libraries(improv improv-util improv-nodes)