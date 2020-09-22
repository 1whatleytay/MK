#ifndef MK_SCORENODE_H
#define MK_SCORENODE_H

#include <node.h>

class Parser;

class ScoreNode : public Node {
public:
    std::string scoreName;
    std::string scoreType;

    std::string createScore();

    ScoreNode(Node *parent, Parser &parser);
};


#endif //MK_SCORENODE_H
