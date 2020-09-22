#include <nodes/command.h>

#include <util/parser.h>

std::string CommandNode::getSource() {
    return command + "\n";
}

CommandNode::CommandNode(Node *parent, Parser &parser) : Node(parent, Type::Command) {
    if (parser.next() != "/")
        throw std::runtime_error("Internal error related to commands.");

    command = parser.until({ "\n" });
}
