#include <utility>

#include <Parser.h>

#include <sstream>
#include <iostream>

const char symbols[] = {
        ':',
        ';',
        ',',
        '.',
        '{',
        '}',
        '+',
        '-',
        '=',
        '/',
        '\\',
        '@',
        '#',
        '$',
        '%',
        '^',
        '&',
        '*',
        '(',
        ')',
        '!',
        '?',
        '<',
        '>',
        '~',
};

bool isStrongChar(char ch) {
    if (std::isspace(ch)) return true;
    for (char c : symbols) {
        if (c == ch) return true;
    }
    return false;
}

void Parser::pushMode(Parser::Mode mode) {
    modes.push(currentMode);
    currentMode = mode;
}

Parser::Mode Parser::popMode() {
    Mode lastMode = currentMode;
    currentMode = modes.top();
    modes.pop();
    return lastMode;
}

bool Parser::end(int offset) {
    return index + offset >= text.length();
}

bool Parser::reachedEnd(int offset) {
    pushIndex();
    return end(offset);
}

void Parser::pushIndex() {
    if (currentMode != Original) while (!end() && std::isspace(text[index])) { index++; }
}

void Parser::seekNext(const std::string &word) {
    int roll = index;
    while (nextWord() != word && !reachedEnd()) { }
    if (!reachedEnd()) rollback();
    rollbackIndex = roll;
}

void Parser::seekNextWords(const std::vector<std::string> &tests) {
    int roll = index;
    while (std::find(std::begin(tests), std::end(tests), nextWord()) == std::end(tests) && !reachedEnd()) { }
    if (!reachedEnd()) rollback();
    rollbackIndex = roll;
}

void Parser::rollback() {
    index = rollbackIndex;
}

void Parser::select() {
    selectIndex = index;
}

std::string Parser::clip() {
    return text.substr((unsigned long)selectIndex, (unsigned long)index - (unsigned long)selectIndex);
}

std::string Parser::untilNextSymbolClosing(char opening, char symbol, int depth) {
    rollbackIndex = index;
    pushIndex();

    int length = 0;
    while (!reachedEnd(length)) {
        if (text[index + length] == symbol) {
            depth--;
            if (depth <= 0) break;
        }
        if (text[index + length] == opening) {
            depth++;
        }
        length++;
    }

    std::string result = reachedEnd() ? "" : text.substr((unsigned long)index, (unsigned long)length);
    index += length;

    return result;
}

char Parser::lastSymbol() {
    rollbackIndex = index;

    while (index > 0 && std::isspace(text[index])) { index--; }

    if (index >= 0) return text[--index];
    else {
        index = 0;
        return ' ';
    }
}

std::string Parser::lastWord() {
    int temp = index;

    while (index > 0 && std::isspace(text[index])) { index--; }
    if (currentMode != Original) while (index > 0 && !isStrongChar(text[index])) { index--; }

    std::string word = nextWord();
    rollback();

    rollbackIndex = temp;

    return word;
}

std::string Parser::untilNextSymbol(char symbol) {
    rollbackIndex = index;
    pushIndex();

    int length = 0;
    while (!reachedEnd(length) && (text[index + length] != symbol)) { length++; }
    if (currentMode != Original) while (length > 0 && std::isspace(text[index + length - 1])) { length--; }

    std::string result = reachedEnd() ? "" : text.substr((unsigned long)index, (unsigned long)length);
    index += length;

    return result;
}

std::string Parser::untilNextSymbols(const std::vector<char> &tests) {
    rollbackIndex = index;
    pushIndex();

    int length = 0;
    while (!reachedEnd(length) && (std::find(tests.begin(), tests.end(), text[index + length]) == tests.end())) {
        length++;
    }
    while (length >= 0 && std::isspace(text[index + length - 1])) {
        length--;
    }
    length = std::max(length, 0);

    std::string result = reachedEnd() ? "" : text.substr((unsigned long)index, (unsigned long)length);
    index += length;

    return result;
}

std::string Parser::untilNextWord(const std::string &word) {
    rollbackIndex = index;
    pushIndex();

    int firstIndex = index;
    seekNext(word);

    return text.substr((unsigned long)firstIndex, (unsigned long)index - (unsigned long)firstIndex);
}

std::string Parser::untilNextWords(const std::vector<std::string> &tests) {
    rollbackIndex = index;
    pushIndex();

    int firstIndex = index;
    seekNextWords(tests);

    return text.substr((unsigned long)firstIndex, (unsigned long)index - (unsigned long)firstIndex);
}

std::string Parser::untilNextWhitespace() {
    rollbackIndex = index;
    pushIndex();

    int length = 0;
    while (!reachedEnd(length) && !std::isspace(text[index + length])) { length++; }

    std::string result;
    if (!reachedEnd())
        result = text.substr((unsigned long)index, (unsigned long)length);

    index += length;

    return result;
}

std::string Parser::toString() { return text; }

char Parser::nextSymbol() {
    rollbackIndex = index;
    pushIndex();

    char symbol = reachedEnd() ? ' ' : text[index];
    index++;

    return symbol;
}

std::string Parser::nextWord() {
    rollbackIndex = index;
    pushIndex();

    int length = 1;

    if (!isStrongChar(text[index]))
        while (!reachedEnd(length) && !isStrongChar(text[index + length])) { length++; }

    std::string result = reachedEnd() ? "" : text.substr((unsigned long)index, (unsigned long)length);
    index += length;

    return result;
}

std::string Parser::trim(std::string text) {
    Parser parser = Parser(std::move(text));
    return parser.untilNextSymbol('\0');
}

Parser::Parser(std::string nText) : text(move(nText)) { }
