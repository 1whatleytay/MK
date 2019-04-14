#ifndef MK_METHODNODE_H
#define MK_METHODNODE_H

#include <Node.h>

#include <unordered_map>

class Parser;
class MethodInfo;

class MethodNode : public Node {
public:
    const MethodInfo *method = nullptr;
    std::unordered_map<std::string, std::string> methodValues;

    std::string getSource() override;

    static bool hasMethod(const std::string &name);

    MethodNode(Node *parent, Parser &parser);
};

#endif //MK_METHODNODE_H
