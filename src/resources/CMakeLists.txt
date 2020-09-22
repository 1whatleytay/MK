add_library(improv-resources
    include/resources/resources.h

    src/items.cpp
    src/entities.cpp
    src/global_methods.cpp
    src/target_methods.cpp)

target_include_directories(improv-resources PUBLIC include)
target_link_libraries(improv-resources improv-util)
