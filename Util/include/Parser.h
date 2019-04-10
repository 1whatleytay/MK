#ifndef MK_PARSER_H
#define MK_PARSER_H

#include "Util.h"

class Parser {
    int rollbackIndex = 0;
    int index = 0;
    std::string text;

    int selectIndex = 0;

    bool end(int offset = 0);
    void pushIndex();

public:
    bool reachedEnd(int offset = 0);

    void seekNext(const std::string &word);
    void seekNextWords(const std::vector<std::string> &word);
    void rollback();

    void select();
    std::string clip();

    std::string untilNextSymbolClosing(char opening, char symbol, int depth = 1);
    std::string untilNextSymbol(char symbol);
    std::string untilNextSymbols(const std::vector<char> &tests);
    std::string untilNextWord(const std::string &word);
    std::string untilNextWords(const std::vector<std::string> &tests);
    std::string untilNextWhitespace();

    char lastSymbol();
    std::string lastWord();

    char nextSymbol();
    std::string nextWord();

    explicit Parser(std::string nText);
};

#endif //MK_PARSER_H
