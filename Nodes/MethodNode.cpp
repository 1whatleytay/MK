#include "MethodNode.h"

#include <Parser.h>
#include <Params.h>
#include <Formats.h>

#include <sstream>

// Bossbar should be its own object imo

MethodInfo globalMethods[] = {
        { "help", { { "command", Params::Text, { }, true } }, "help [command]" },
        { "say", { { "text", Params::Text } }, "say [text]" },
        { "weather", { { "weather", Params::Text, { "clear", "rain", "thunder" } } }, "weather [weather]" },
        { "clone",
          {
            { "c1", Params::Coordinate }, { "c2", Params::Coordinate }, { "c3", Params::Coordinate },
                  { "mask", Params::Text, { "filtered", "masked", "replace" }, true },
                  { "clone", Params::Text, { "force", "move", "normal" }, true },
                  { "block", Params::Item, { }, true }, { "data", Params::Text, { }, true }
          },
          "clone [c1] [c2] [c3] [mask] [clone] [block] [data]" },
        { "difficulty",
          { { "diff", Params::Text, { "peaceful", "easy", "normal", "hard", "p", "e", "n", "h" } } },
          "difficulty [diff]" },
        { "summon",
          {
            { "entity", Params::Entity },
            { "coord", Params::Coordinate, { }, true }, { "data", Params::Text, { }, true } },
            "summon [entity] [coord] [data]" }
};

static const MethodInfo *findGlobalMethod(const std::string &name) {
    for (const MethodInfo &method : globalMethods) {
        if (method.name == name) return &method;
    }
    return nullptr;
}

bool MethodNode::hasMethod(const std::string &name) {
    return findGlobalMethod(name);
}

std::string MethodNode::getSource() {
    Parser parser = Parser(method->source);
    std::stringstream stream;

    parser.pushMode(Parser::Original);

    while (!parser.reachedEnd()) {
        stream << parser.untilNextSymbol('[');
        if (parser.nextSymbol() != '[') throw Unexpected(method->source, "Global Method Source");
        std::string inBetween = parser.untilNextSymbol(']');
        if (parser.nextSymbol() != ']') throw Unexpected(method->source, "Global Method Source");

        if (methodValues.find(inBetween) != methodValues.end() && !methodValues[inBetween].empty()) {
            stream << methodValues[inBetween];
        }
    }

    parser.popMode();

    return Parser::trim(stream.str()) + "\n";
}

MethodNode::MethodNode(Node *parent, Parser &parser) : Node(parent, Method) {
    std::string name = parser.nextWord();
    Params params = Params(parser);

    method = findGlobalMethod(name);

    for (const MethodInfo::Param& param : method->params) {
        std::string value = params.next(param.type, param.optional);
        if (value.empty()) break;
        if (!param.allowedValues.empty()) {
            if (std::find(std::begin(param.allowedValues), std::end(param.allowedValues), value)
                == std::end(param.allowedValues)) {
                std::stringstream stream;
                stream << "allowed value (";
                for (int a = 0; a < param.allowedValues.size(); a++) {
                    stream << param.allowedValues[a];
                    if (a < param.allowedValues.size() - 1) stream << " or ";
                }
                stream << ")";
                throw InvalidParam(stream.str(), value);
            }
        }
        methodValues[param.name] = value;
    }

    params.finish();
}
