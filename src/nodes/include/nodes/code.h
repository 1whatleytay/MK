#pragma once

#include <nodes/node.h>

class CodeNode : public Node {
public:
    std::string getSource() override;

    CodeNode(Node *parent, const std::string &source);
};
