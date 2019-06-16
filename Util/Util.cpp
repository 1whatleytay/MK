#include <utility>

#include <utility>

#include <Util.h>

#include <fstream>
#include <sstream>
#include <iostream>

#ifdef __WIN32
#include <Windows.h>
#else
#include <sys/stat.h>
#endif

const char* Exception::what() const noexcept {
    return info().c_str();
}

std::string FileNotFound::info() const { return "Cannot find file \"" + path + "\"."; }
FileNotFound::FileNotFound(std::string path) : path(std::move(path)) { }

std::string FileIssue::info() const { return "Could not write to file \"" + path + "\"."; }
FileIssue::FileIssue(std::string path) : path(std::move(path)) { }

std::string UnexpectedSymbol::info() const {
    std::stringstream stream;
    for (int a = 0; a < expected.size(); a++) {
        stream << "'" << expected[a] << "'" << (a != expected.size() - 1 ? " or " : "");
    }
    return "Expected " + stream.str() + " but got '" + received + "'.";
}

UnexpectedSymbol::UnexpectedSymbol(std::vector<char> expected, char received)
    : expected(std::move(expected)), received(received) {}

std::string Unsupported::info() const { return feature + " are not supported."; }
Unsupported::Unsupported(std::string feature) : feature(std::move(feature)) { }

std::string WrongCase::info() const { return "\"" + name + "\" is not in " + expectedCase + "."; }
WrongCase::WrongCase(std::string expectedCase, std::string name)
    : expectedCase(std::move(expectedCase)), name(std::move(name)) { }

std::string InvalidParam::info() const { return "\"" + name + "\" is not a valid " + type + "."; }
InvalidParam::InvalidParam(std::string type, std::string name) : type(std::move(type)), name(std::move(name)) { }

std::string UnexpectedLine::info() const { return "Unexpected line \"" + line + "\"."; }
UnexpectedLine::UnexpectedLine(std::string line) : line(std::move(line)) { }

std::string Unexpected::info() const { return "Expected " + expected + " but got \"" + got + "\"."; }
Unexpected::Unexpected(std::string expected, std::string got) : expected(std::move(expected)), got(std::move(got)) { }

std::string WrongArgumentCount::info() const {
    return "Incorrect argument count, expected " + std::to_string(number) + ".";
}
WrongArgumentCount::WrongArgumentCount(int number) : number(number) { }

std::string DuplicateDefinition::info() const {
    return "Duplicate symbol \"" + name + "\" of type " + type + ".";
}
DuplicateDefinition::DuplicateDefinition(std::string name, std::string type)
    : name(std::move(name)), type(std::move(type)) { }

std::string UnknownFunction::info() const { return "Unknown function named \"" + name + "\"."; }

UnknownFunction::UnknownFunction(std::string name) : name(name) { }

std::string textFrom(const std::string &path) {
    std::ifstream stream = std::ifstream(path, std::ios::ate);
    if (!stream.good()) throw FileNotFound(path);
    unsigned long length = (unsigned long)stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::vector<char> text = std::vector<char>(length);
    stream.read(&text[0], length);
    stream.close();

    return std::string(text.begin(), text.end());
}

void textTo(const std::string &path, const std::string &text) {
    std::ofstream stream = std::ofstream(path);
    if (!stream.good()) throw FileIssue(path);
    stream.write(text.c_str(), text.size());
    stream.close();
}

std::vector<unsigned> dataFrom(const std::string &path) {
    std::ifstream stream = std::ifstream(path, std::ios::ate | std::ios::binary);
    if (!stream.good()) throw FileNotFound(path);
    unsigned long length = (unsigned long)stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::vector<unsigned> data = std::vector<unsigned>(length / sizeof(unsigned));
    stream.read((char*)&data[0], length);
    stream.close();

    return data;
}

void dataTo(const std::string &path, std::vector<unsigned> data) {
    std::ofstream stream = std::ofstream(path, std::ios::binary);
    if (!stream.good()) throw FileIssue(path);
    stream.write((char*)&data[0], data.size() * sizeof(unsigned));
    stream.close();
}

void makeDirectory(const std::string &path) {
#ifdef __WIN32
    //TODO: Windows support.
#else
    mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
#endif
}

void removeFile(const std::string &path) {
#ifdef __WIN32
    //TODO: Windows support.
#else
    remove(path.c_str());
#endif
}

std::vector<std::string> split(const std::string &text) {
    std::vector<std::string> out;
    std::stringstream stream = std::stringstream(text);
    std::string next;

    while (std::getline(stream, next)) {
        out.push_back(next);
    }

    return out;
}

std::string asString(double value) {
    std::string before = std::to_string(value);
    if (before[before.size() - 1] != '0') return before;
    unsigned index;
    for (index = before.size() - 1; index > 0 && (before[index] == '0' || before[index] == '.'); index--) { }
    return before.substr(0, index + 1);
}

bool isCaptial(const std::string &text) {
    for (char a : text) {
        if (std::isupper(a))
            return true;
    }

    return false;
}

bool isDigits(const std::string &text) {
    for (char a : text) {
        if (!std::isdigit(a)) return false;
    }

    return true;
}

void log(const std::string &text) { std::cout << text << std::endl; }

void logInfo(const std::string &text) { log("INFO: " + text); }
void logError(const std::string &text) { log("ERROR: " + text); }
void logDebug(const std::string &text) {
#ifdef LOG_DEBUG
        log("DEBUG: " + text);
#endif
}
