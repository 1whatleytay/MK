#include <nodes/parameter.h>

#include <util/parser.h>
#include <util/formats.h>

#include <resources/resources.h>

#include <fmt/format.h>

std::string ParameterNode::nextEntity(Parser &parser) {
    std::string next = parseEntity(parser.until({ ",", ")" }));
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

std::string ParameterNode::nextItem() {
    std::string next = parseItemOrBlock(parser.untilNextSymbols({ ',', ')' }));
    paramCount++;
    return next;
}

std::string ParameterNode::nextText() {
    std::string next = parser.untilNextSymbols({ ',', ')' });
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

// Might not allow negative numbers
std::string ParameterNode::nextNumber() {
    std::string next = parser.untilNextSymbols({ ',', ')' });
    if (!isDigits(next)) throw Unexpected("number", next);
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

std::string ParameterNode::nextCoordinate() {
    std::string next = parser.untilNextSymbols({ ',', ')' });
    char nextSym = parser.nextSymbol();
    if (nextSym != ')' && nextSym != ',') throw UnexpectedSymbol({ ')', ',' }, nextSym);
    if (nextSym == ')') hasFinished = true;

    Parser coordParser = Parser(next);
    std::stringstream stream;
    if (coordParser.nextSymbol() != '[') throw Unexpected("coordinate", coordParser.last());
    std::string coordNext;
    for (int a = 0; a < 3; a++) {
        coordNext = coordParser.next();
        if (coordNext == "~") {
            stream << "~";
            coordNext = coordParser.next();
        }
        if (coordNext == "-") {
            stream << "-";
            coordNext = coordParser.next();
        }
        if (!isDigits(coordNext)) throw Unexpected("coordinate component", coordParser.last());
        stream << coordNext;
        if (a != 2) stream << " ";
    }

    return stream.str();
}

ParameterNode::ParameterNode(Node *parent, Parser &parser, Param::Type type) : Node(parent, Type::Parameter) {
    switch (type) {
        case Param::Type::Number:
            content = nextNumber()
    }
}