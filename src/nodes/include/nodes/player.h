#ifndef MK_PLAYERNODE_H
#define MK_PLAYERNODE_H

#include <node.h>

class Parser;

class PlayerNode : public Node {
public:
    std::string name;

    PlayerNode(Node *parent, Parser &parser);
};

#endif //MK_PLAYERNODE_H
