#include "ExecuteNode.h"

#include <Formats.h>
#include <Parser.h>

#include <CodeNode.h>

#include <sstream>

std::string ExecuteNode::getSource() {
    std::stringstream childSource;
    for (const auto &child : children) {
        childSource << child->getSource();
    }
    std::vector<std::string> commands = split(childSource.str());
    std::stringstream executeSource;
    for (const std::string &command : commands) {
        executeSource << "execute as " << executeTarget << " run " << command << "\n";
    }
    return executeSource.str();
}

ExecuteNode::ExecuteNode(Node *parent, Parser &parser) : Node(parent, Execute) {
    if (parser.nextWord() != "as") throw UnexpectedLine(parser.untilNextSymbol('\n'));
    executeTarget = parseTarget(parser.nextWord());

    if (parser.nextWord() == "where") {
        if (parser.nextSymbol() != '(') throw UnexpectedSymbol({ '(' }, parser.lastSymbol());
        parser.pushMode(Parser::Original);
        executeTarget += "[" + parser.untilNextSymbol(')') + "]";
        parser.popMode();
        if (parser.nextSymbol() != ')') throw UnexpectedSymbol({ ')' }, parser.lastSymbol());
    } else {
        parser.rollback();
    }

    if (parser.nextSymbol() != '{') throw UnexpectedSymbol({ '{' }, parser.lastSymbol());
    children.push_back(new CodeNode(this, parser.untilNextSymbolClosing('{', '}', 1)));
    if (parser.nextSymbol() != '}') throw UnexpectedSymbol({ '}' }, parser.lastSymbol());
}
