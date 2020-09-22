#include <util/util.h>

#include <fmt/format.h>

#include <fstream>
#include <sstream>
#include <iostream>

std::string textFrom(const std::string &path) {
    std::ifstream stream = std::ifstream(path, std::ios::ate);

    if (!stream.good())
        throw std::runtime_error(fmt::format("Cannot find file {}.", path));

    unsigned long length = (unsigned long)stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::vector<char> text = std::vector<char>(length);
    stream.read(&text[0], length);
    stream.close();

    return std::string(text.begin(), text.end());
}

void textTo(const std::string &path, const std::string &text) {
    std::ofstream stream = std::ofstream(path, std::ios::trunc);

    if (!stream.good())
        throw std::runtime_error(fmt::format("Cannot open file {}.", path));
    stream.write(text.c_str(), text.size());
    stream.close();
}

std::vector<unsigned> dataFrom(const std::string &path) {
    std::ifstream stream = std::ifstream(path, std::ios::ate | std::ios::binary);

    if (!stream.good())
        throw std::runtime_error(fmt::format("Cannot find file {}.", path));
    unsigned long length = (unsigned long)stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::vector<unsigned> data = std::vector<unsigned>(length / sizeof(unsigned));
    stream.read((char*)&data[0], length);
    stream.close();

    return data;
}

void dataTo(const std::string &path, std::vector<unsigned> data) {
    std::ofstream stream = std::ofstream(path, std::ios::binary | std::ios::trunc);

    if (!stream.good())
        throw std::runtime_error(fmt::format("Cannot open file {}.", path));
    stream.write((char*)&data[0], data.size() * sizeof(unsigned));
    stream.close();
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
