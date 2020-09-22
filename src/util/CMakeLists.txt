add_library(improv-util
    include/util/util.h
    include/util/datapack.h
    include/util/json.h
    include/util/formats.h
    include/util/parser.h

    src/util.cpp
    src/datapack.cpp
    src/json.cpp
    src/formats.cpp
    src/parser.cpp)

target_link_libraries(improv-util PUBLIC improv-resources fmt)
target_include_directories(improv-util PUBLIC include)
