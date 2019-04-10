#ifndef MK_METHODNODE_H
#define MK_METHODNODE_H

#include <Node.h>

class Parser;

class MethodNode : public Node {
public:
    std::string methodName;
    std::string methodValue;

    static bool isMethod(const std::string &name);

    std::string getSource() override;

    MethodNode(Node *parent, Parser &parser);
};

#endif //MK_METHODNODE_H
