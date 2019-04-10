#include "MethodNode.h"

#include <Parser.h>
#include <Params.h>
#include <Formats.h>

class Method {

};

Method methods[] = {

};

bool MethodNode::isMethod(const std::string &name) {

}

std::string MethodNode::getSource() {
    switch (methodName) {
        case Say:
            return "say " + methodValue + "\n";
        default: return "";
    }
}

MethodNode::MethodNode(Node *parent, Parser &parser) : Node(parent, Method) {
    std::string name = parser.nextWord();
    Params params = Params(parser);

    if (name == "say") {
        methodName = Say;
        methodValue = params.nextText();
    }

    params.finish();
}
