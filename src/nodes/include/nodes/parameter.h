#pragma once

#include <nodes/node.h>

#include <resources/resources.h>

class Parser;

class ParameterNode : public Node {
public:
    std::string content;

    std::string nextEntity(Parser &parser);
    std::string nextItem(Parser &parser);
    std::string nextText(Parser &parser);
    std::string nextNumber(Parser &parser);
    std::string nextCoordinate(Parser &parser);

    ParameterNode(Node *parent, Parser &parser, Param::Type type);
};
