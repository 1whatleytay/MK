#ifndef MK_EXECUTENODE_H
#define MK_EXECUTENODE_H

#include <Node.h>

class Parser;

class ExecuteNode : public Node {
public:
    std::string executeTarget;

    std::string getSource() override;

    ExecuteNode(Node *parent, Parser &parser);
};


#endif //MK_EXECUTENODE_H
