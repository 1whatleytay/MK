#include "CommandNode.h"

#include <Parser.h>

std::string CommandNode::getSource() {
    return command + "\n";
}

CommandNode::CommandNode(Node *parent, const std::string &source) : Node(parent, Command) {
    Parser parser = Parser(source);

    if (parser.nextSymbol() != '/') throw UnexpectedSymbol({'/'}, parser.lastSymbol());

    command = parser.untilNextSymbol('\n');
}
