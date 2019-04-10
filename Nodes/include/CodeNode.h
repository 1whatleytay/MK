#ifndef MK_CODENODE_H
#define MK_CODENODE_H

#include <Node.h>

class CodeNode : public Node {
    std::string source;
public:
    std::string getSource() override;

    CodeNode(Node *parent, const std::string &source);
};

#endif //MK_CODENODE_H
