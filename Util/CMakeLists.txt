add_library(mk-util
        include/Parser.h
        include/Util.h
        include/DataPack.h
        include/JSON.h
        include/Formats.h
        include/Params.h

        Parser.cpp
        Util.cpp
        DataPack.cpp
        JSON.cpp
        Formats.cpp
        Params.cpp)

target_include_directories(mk-util PUBLIC include)
