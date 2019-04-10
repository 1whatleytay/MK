#ifndef MK_MODIFYTARGETNODE_H
#define MK_MODIFYTARGETNODE_H

#include <Node.h>

class Parser;

class ModifyTargetNode : public Node {
public:
    enum Function {
        Kill,
        Give,
    };

    std::string modifyTarget, modifyValue, modifyData;
    int modifyCount = 0;
    Function modifyFunction;

    std::string getSource() override;

    ModifyTargetNode(Node *parent, Parser &parser);
};


#endif //MK_MODIFYTARGETNODE_H
