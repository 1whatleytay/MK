#include "ModifyTargetNode.h"

#include <Parser.h>
#include <Params.h>
#include <Formats.h>

#include <Methods.h>

#include <sstream>

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
        if (parser.reachedEnd()) break;
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
    if (parser.nextSymbol() != '.') throw UnexpectedSymbol({'.'}, parser.lastSymbol());
    std::string name = parser.nextWord();
    Params params = Params(parser);

    method = findTargetMethod(name);

    if (method) {
        for (const MethodInfo::Param &param : method->params) {
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
    } else {
        throw UnknownFunction(name);
    }

    params.finish();

    if (parser.nextWord() != "where") {
        parser.rollback();
        return;
    }

    if (parser.nextSymbol() != '(') throw UnexpectedSymbol({'('}, parser.lastSymbol());
    parser.pushMode(Parser::Original);
    methodValues["target"] += "[" + parser.untilNextSymbol(')') + "]"; // TODO: Actually parse contents.
    parser.popMode();
    if (parser.nextSymbol() != ')') throw UnexpectedSymbol({')'}, parser.lastSymbol());
}
