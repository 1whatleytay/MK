add_library(mk-resources
        include/MethodInfo.h
        include/Methods.h

        GlobalMethods.cpp
        TargetMethods.cpp)

target_include_directories(mk-resources PUBLIC include)
target_link_libraries(mk-resources mk-util)
