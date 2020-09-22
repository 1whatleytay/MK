#include "MethodNode.h"

#include "FunctionNode.h"

#include <Parser.h>
#include <Params.h>
#include <Formats.h>

#include <Methods.h>

#include <sstream>

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
    if (!method) {
        std::string actualName = parseName(methodName);
        Node *select = parentSearch([&actualName](Node *node) {
            return node->type == Type::Function && ((FunctionNode *)node)->funcName == actualName;
        });
        if (!select) throw UnknownFunction(methodName);
        return "function " + parseName(methodName) + "\n";
    }

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
    methodName = parser.nextWord();
    if (parser.nextSymbol() != '(') {
        parser.rollback();
        throw Unexpected("word", parser.nextWord());
    }
    parser.rollback();
    Params params = Params(parser);

    method = findGlobalMethod(methodName);

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
        log("[Callable Custom Function " + methodName + "]");
    }

    params.finish();

    if (parser.nextWord() == "where") {
        log("WARNING: Keyword \"where\" is not allowed with a global method. Use as instead.");
    }
    parser.rollback();
}
