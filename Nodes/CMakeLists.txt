add_library(mk-nodes
        include/Node.h
        include/CodeNode.h
        include/TagNode.h
        include/FunctionNode.h
        include/CommandNode.h
        include/ScoreNode.h
        include/ModifyScoreNode.h
        include/ExecuteNode.h
        include/ModifyTargetNode.h
        include/MethodNode.h
        include/PlayerNode.h

        Node.cpp
        CodeNode.cpp
        TagNode.cpp
        FunctionNode.cpp
        CommandNode.cpp
        ScoreNode.cpp
        ModifyScoreNode.cpp
        ExecuteNode.cpp
        ModifyTargetNode.cpp
        MethodNode.cpp
        PlayerNode.cpp)

target_include_directories(mk-nodes PUBLIC include)
target_link_libraries(mk-nodes mk-util)
