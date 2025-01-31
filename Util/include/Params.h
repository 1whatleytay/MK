#ifndef MK_PARAMS_H
#define MK_PARAMS_H

#include <Util.h>

class Parser;

class Params {
    Parser &parser;

    bool hasFinished = false;
    int paramCount = 0;
public:
    enum Type {
        Entity,
        Item,
        Text,
        Number,
        Coordinate
    };

    std::string nextEntity(bool optional = false);
    std::string nextItem(bool optional = false);
    std::string nextText(bool optional = false);
    std::string nextNumber(bool optional = false);
    std::string nextCoordinate(bool optional = false);

    std::string next(Type type, bool optional = false);

    bool finish();

    explicit Params(Parser &parser);
};

#endif //MK_PARAMS_H
