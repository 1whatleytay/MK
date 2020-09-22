add_library(improv-nodes
    include/nodes/node.h
    include/nodes/code.h
    include/nodes/tag.h
    include/nodes/parameter.h
    include/nodes/function.h
    include/nodes/command.h
    include/nodes/score.h
    include/nodes/modify_score.h
    include/nodes/execute.h
    include/nodes/modify_target.h
    include/nodes/method.h
    include/nodes/player.h
    include/nodes/recipe.h

    src/node.cpp
    src/code.cpp
    src/tag.cpp
    src/parameter.cpp
    src/function.cpp
    src/command.cpp
    src/score.cpp
    src/modify_score.cpp
    src/execute.cpp
    src/modify_target.cpp
    src/method.cpp
    src/player.cpp
    src/recipe.cpp)

target_include_directories(improv-nodes PUBLIC include)
target_link_libraries(improv-nodes improv-util improv-resources)
