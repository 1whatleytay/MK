#ifndef MK_COMMANDNODE_H
#define MK_COMMANDNODE_H

#include <Node.h>

class CommandNode : public Node {
public:
    std::string command;

    std::string getSource() override;

    CommandNode(Node *parent, const std::string &source);
};

#endif //MK_COMMANDNODE_H
