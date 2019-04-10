#ifndef MK_MODIFYSCORENODE_H
#define MK_MODIFYSCORENODE_H

#include <Node.h>

class Parser;
class ScoreNode;

class ModifyScoreNode : public Node {
public:
    enum Operation {
        Set,
        Add,
        Sub,

        SetDisplay,
        Hide,

        Error
    };

    Operation modifyOp = Error;
    ScoreNode *modifyScore = nullptr;
    std::string modifyTarget;
    int modifyValue = 0;

    std::string getSource() override;

    ModifyScoreNode(Node *parent, Parser &parser);
};

#endif //MK_MODIFYSCORENODE_H
