#include "Params.h"

#include <Parser.h>
#include <Formats.h>

#include <sstream>

std::string Params::nextEntity(bool optional) {
    if (hasFinished) {
        if (optional) return "";
        else throw WrongArgumentCount(paramCount + 1);
    }
    std::string next = parseEntity(parser.untilNextSymbols({ ',', ')' }));
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

std::string Params::nextItem(bool optional) {
    if (hasFinished) {
        if (optional) return "";
        else throw WrongArgumentCount(paramCount + 1);
    }
    std::string next = parseItemOrBlock(parser.untilNextSymbols({ ',', ')' }));
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

std::string Params::nextText(bool optional) {
    if (hasFinished) {
        if (optional) return "";
        else throw WrongArgumentCount(paramCount + 1);
    }
    std::string next = parser.untilNextSymbols({ ',', ')' });
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

// Might not allow negative numbers
std::string Params::nextNumber(bool optional) {
    if (hasFinished) {
        if (optional) return "";
        else throw WrongArgumentCount(paramCount + 1);
    }
    std::string next = parser.untilNextSymbols({ ',', ')' });
    if (!isDigits(next)) throw Unexpected("number", next);
    if (parser.nextSymbol() == ')') hasFinished = true;
    paramCount++;
    return next;
}

std::string Params::nextCoordinate(bool optional) {
    if (hasFinished) {
        if (optional) return "";
        else throw WrongArgumentCount(paramCount + 1);
    }
    std::string next = parser.untilNextSymbols({ ',', ')' });
    char nextSym = parser.nextSymbol();
    if (nextSym != ')' && nextSym != ',') throw UnexpectedSymbol({ ')', ',' }, nextSym);
    if (nextSym == ')') hasFinished = true;

    Parser coordParser = Parser(next);
    std::stringstream stream;
    if (coordParser.nextSymbol() != '[') throw Unexpected("coordinate", coordParser.lastWord());
    std::string coordNext;
    for (int a = 0; a < 3; a++) {
        coordNext = coordParser.nextWord();
        if (coordNext == "~") {
            stream << "~";
            coordNext = coordParser.nextWord();
        }
        if (coordNext == "-") {
            stream << "-";
            coordNext = coordParser.nextWord();
        }
        if (!isDigits(coordNext)) throw Unexpected("coordinate component", coordParser.lastWord());
        stream << coordNext;
        if (a != 2) stream << " ";
    }

    return stream.str();
}

std::string Params::next(Type type, bool optional) {
    switch (type) {
        case Text:
            return nextText(optional);
        case Number:
            return nextNumber(optional);
        case Item:
            return nextItem(optional);
        case Entity:
            return nextEntity(optional);
        case Coordinate:
            return nextCoordinate(optional);
    }
}

bool Params::finish() {
    if (hasFinished) return true;
    if (paramCount == 0 && parser.nextSymbol() == ')') return true;
    throw WrongArgumentCount(paramCount);
}

Params::Params(Parser &parser) : parser(parser) {
    if (parser.nextSymbol() != '(') throw UnexpectedSymbol({ '(' }, parser.lastSymbol());
}
