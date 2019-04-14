#ifndef MK_MODIFYTARGETNODE_H
#define MK_MODIFYTARGETNODE_H

#include <Node.h>

#include <unordered_map>

class Parser;
class MethodInfo;

class ModifyTargetNode : public Node {
public:
    const MethodInfo *method = nullptr;
    std::unordered_map<std::string, std::string> methodValues;

    std::string getSource() override;

    static bool hasMethod(const std::string &name);

    ModifyTargetNode(Node *parent, Parser &parser);
};


#endif //MK_MODIFYTARGETNODE_H
