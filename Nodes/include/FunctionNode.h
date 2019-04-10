#ifndef MK_FUNCTIONNODE_H
#define MK_FUNCTIONNODE_H

#include <Node.h>

class Parser;

class FunctionNode : public Node {
public:
    std::string funcName;
    std::string funcSource;

    bool onLoad = false, onTick = false;

    std::string getSource() override;

    FunctionNode(Node *parent, Parser &parser, std::vector<std::string> attributes = {});
};

#endif //MK_FUNCTIONNODE_H
