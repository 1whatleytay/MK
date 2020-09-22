#include "FunctionNode.h"

#include <Parser.h>
#include <Formats.h>
#include <CodeNode.h>

#include <sstream>

std::string FunctionNode::getSource() {
    return children[0]->getSource();
}

FunctionNode::FunctionNode(Node *parent, Parser &parser, std::vector<std::string> attributes)
    : Node(parent, Function) {
    onLoad = std::find(attributes.begin(), attributes.end(), "load") != attributes.end();
    onTick = std::find(attributes.begin(), attributes.end(), "tick") != attributes.end();

    if (parser.nextWord() != "func") throw Unsupported("Non-explicit func");
    funcName = parseName(parser.untilNextSymbol('{'));
    if (isCaptial(funcName)) throw WrongCase("snake_case", funcName);
    if (parser.nextSymbol() != '{') throw UnexpectedSymbol({ '{' }, parser.lastSymbol());
    funcSource = parser.untilNextSymbolClosing('{', '}', 1);
    if (parser.nextSymbol() != '}') throw UnexpectedSymbol({ '}' }, parser.lastSymbol());

    children.push_back(new CodeNode(this, funcSource));
}
