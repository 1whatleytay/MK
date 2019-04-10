#ifndef MK_UTIL_H
#define MK_UTIL_H

#include <string>
#include <vector>

class Exception: public std::exception {
public:
    virtual std::string info() const = 0;
    const char *what() const noexcept override;
};

class FileNotFound : public Exception {
    std::string path;
public:
    std::string info() const override;
    explicit FileNotFound(std::string path);
};

class FileIssue : public Exception {
    std::string path;
public:
    std::string info() const override;
    explicit FileIssue(std::string path);
};

class Unsupported : public Exception {
    std::string feature;
public:
    std::string info() const override;
    explicit Unsupported(std::string feature);
};

class UnexpectedSymbol : public Exception {
    std::vector<char> expected;
    char received;
public:
    std::string info() const override;

    UnexpectedSymbol(std::vector<char> expected, char received);
};

class WrongCase : public Exception {
    std::string expectedCase;
    std::string name;
public:
    std::string info() const override;
    WrongCase(std::string expectedCase, std::string name);
};

class UnexpectedLine : public Exception {
    std::string line;
public:
    std::string info() const override;
    explicit UnexpectedLine(std::string line);
};

class Unexpected : public Exception {
    std::string expected;
    std::string got;
public:
    std::string info() const override;
    explicit Unexpected(std::string expected, std::string got);
};

class WrongArgumentCount : public Exception {
    int number;
public:
    std::string info() const override;
    explicit WrongArgumentCount(int number);
};

class DuplicateDefinition : Exception {
    std::string name;
    std::string type;
public:
    std::string info() const override;

    DuplicateDefinition(std::string name, std::string type);
};

std::string textFrom(const std::string &path);
std::vector<unsigned> dataFrom(const std::string &path);
void textTo(const std::string &path, const std::string &text);
void dataTo(const std::string &path, std::vector<unsigned> data);

void removeFile(const std::string &path);
void makeDirectory(const std::string &path);

std::string asString(double value);
bool isDigits(const std::string &text);
bool isCaptial(const std::string &text);
std::vector<std::string> split(const std::string &text);

void log(const std::string &text);

void logInfo(const std::string &text);
void logDebug(const std::string &text);
void logError(const std::string &text);

#endif //MK_UTIL_H
