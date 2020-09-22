#pragma once

#include <nodes/node.h>

class CommandNode : public Node {
public:
    std::string command;

    std::string getSource() override;

    CommandNode(Node *parent, Parser &parser);
};
