#include <util/formats.h>

#include <util/parser.h>

#include <resources/resources.h>

#include <fmt/format.h>

#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, std::string> targetAliases = {
        { "nearest", "@p" },
        { "everything", "@e" },
        { "everyone", "@a" },
        { "random", "@r" },
        { "self", "@s" },
};

bool isItem(const std::string &target) {
    auto &items = getItemNames();

    return std::find(items.begin(), items.end(), target) != items.end();
}

bool isEntity(const std::string &target) {
    auto &entities = getEntityNames();

    return std::find(entities.begin(), entities.end(), target) != entities.end();
}

std::string parseTarget(Parser &parser) {
    std::string target = parser.next();

    if (targetAliases.find(target) != targetAliases.end())
        return targetAliases[target];

    return target;
}

std::string parseMinecraft(Parser &parser) {
    std::string target = parser.next();

    if (target == "minecraft") {
        if (parser.next() != ":")
            throw std::runtime_error("When parsing object, expected : after minecraft.");

        target = parser.next();
    }

    return "minecraft:" + target;
}

std::string parseItem(Parser &parser) {
    std::string result = parseMinecraft(parser);

    if (!isItem(result))
        throw std::runtime_error(fmt::format("Unknown item or block {}.", result));

    return result;
}

std::string parseEntity(Parser &parser) {
    std::string result = parseMinecraft(parser);

    if (!isEntity(result))
        throw std::runtime_error(fmt::format("Unknown entity {}.", result));

    return result;
}

std::string parseQuotes(const std::string &text) {
    // TODO: Fill in with cool stuff, e.g. escapes and take Parser object instead.
    return text.substr(1, text.size() - 2);
}

std::string parseName(const std::string &text) {
    std::stringstream stream;
    bool first = true;
    for (char a : text) {
        if (std::isupper(a)) {
            if (!first) {
                stream << "_";
            }
            stream << (char)std::tolower(a);
        } else {
            stream << a;
        }
        if (first) first = false;
    }
    return stream.str();
}
