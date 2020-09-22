#ifndef MK_TAGNODE_H
#define MK_TAGNODE_H

#include <node.h>

class Parser;

class TagNode : public Node {
public:
    std::string tagName;
    std::string tagValue;

    TagNode(Node *parent, Parser &parser);
};

#endif //MK_TAGNODE_H
