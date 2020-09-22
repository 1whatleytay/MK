#include <nodes/tag.h>

#include <util/parser.h>

TagNode::TagNode(Node *parent, Parser &parser) : Node(parent, Type::Tag) {
    if (parser.next() != "#")
        throw std::runtime_error("Internal error related to tags.");

    tagName = parser.next();
    tagValue = parser.until({ "\n" });
}
