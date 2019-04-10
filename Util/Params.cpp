#include "Params.h"

#include <Parser.h>
#include <Formats.h>

std::string Params::nextEntity(bool optional) {
    if (hasFinished && !optional) throw WrongArgumentCount(paramCount + 1);
    std::string next = parseMinecraft(parser.untilNextSymbols({ ',', ')' }));
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

std::string Params::nextItem(bool optional) {
    if (hasFinished && !optional) throw WrongArgumentCount(paramCount + 1);
    std::string next = parseMinecraft(parser.untilNextSymbols({ ',', ')' }));
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

std::string Params::nextText(bool optional) {
    if (hasFinished && !optional) throw WrongArgumentCount(paramCount + 1);
    std::string next = parser.untilNextSymbols({ ',', ')' });
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

int Params::nextNumber(bool optional) {
    if (hasFinished && !optional) throw WrongArgumentCount(paramCount + 1);
    std::string next = parser.untilNextSymbols({ ',', ')' });
    if (!isDigits(next)) throw Unexpected("number", next);
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return std::stoi(next);
}

bool Params::finish() {
    if (hasFinished) return true;
    if (paramCount == 0 && parser.nextSymbol() == ')') return true;
    throw WrongArgumentCount(paramCount);
}

Params::Params(Parser &parser) : parser(parser) {
    if (parser.nextSymbol() != '(') throw UnexpectedSymbol({ '(' }, parser.lastSymbol());
}
