#include "ModifyTargetNode.h"

#include <Parser.h>
#include <Params.h>
#include <Formats.h>

#include <sstream>

MethodInfo targetMethods[] = {
        { "kill", { }, "kill [target]" },
        { "give",
            { { "item", Params::Item }, { "count", Params::Number },  { "data", Params::Text, { }, true } },
            "give [target] [item][data] [count]" },
        { "playSound",
            {
                { "sound", Params::Text },
                { "source", Params::Text,
                  { "master", "music", "record", "weather", "block", "hostile", "neutral", "player", "ambient", "voice" }
                },
                { "coord", Params::Coordinate, { }, true },
                { "volume", Params::Text, { }, true },
                { "pitch", Params::Text, { }, true },
                { "minVolume", Params::Text, { }, true },
            },
          "playsound [sound] [source] [target] [coord] [volume] [pitch] [minVolume]" },
        { "gamemode",
            { { "mode", Params::Text, { "survival", "creative", "adventure", "spectator" } } },
            "gamemode [mode] [target]" }
};

static const MethodInfo *findTargetMethod(const std::string &name) {
    for (const MethodInfo &method : targetMethods) {
        if (method.name == name) return &method;
    }
    return nullptr;
}

bool ModifyTargetNode::hasMethod(const std::string &name) {
    return findTargetMethod(name);
}

std::string ModifyTargetNode::getSource() {
    Parser parser = Parser(method->source);
    std::stringstream stream;

    parser.pushMode(Parser::Original);

    while (!parser.reachedEnd()) {
        stream << parser.untilNextSymbol('[');
        if (parser.nextSymbol() != '[') throw Unexpected(method->source, "Target Method Source");
        std::string inBetween = parser.untilNextSymbol(']');
        if (parser.nextSymbol() != ']') throw Unexpected(method->source, "Target Method Source");

        if (methodValues.find(inBetween) != methodValues.end() && !methodValues[inBetween].empty()) {
            stream << methodValues[inBetween];
        }
    }

    parser.popMode();

    return Parser::trim(stream.str()) + "\n";
}

ModifyTargetNode::ModifyTargetNode(Node *parent, Parser &parser) : Node(parent, ModifyTarget) {
    methodValues["target"] = parseTarget(parser.nextWord());
    if (parser.nextSymbol() != '.') throw UnexpectedSymbol({ '.' }, parser.lastSymbol());
    std::string name = parser.nextWord();
    Params params = Params(parser);

    method = findTargetMethod(name);

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
