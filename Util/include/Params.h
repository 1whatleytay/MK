#ifndef MK_PARAMS_H
#define MK_PARAMS_H

#include <Util.h>

class Parser;

class Params {
    Parser &parser;

    bool hasFinished = false;
    int paramCount = 0;
public:
    std::string nextEntity(bool optional = false);
    std::string nextItem(bool optional = false);
    std::string nextText(bool optional = false);
    int nextNumber(bool optional = false);

    bool finish();

    explicit Params(Parser &parser);
};


#endif //MK_PARAMS_H
