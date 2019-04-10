#include "ModifyTargetNode.h"

#include <Parser.h>
#include <Params.h>
#include <Formats.h>

std::string ModifyTargetNode::getSource() {
    switch (modifyFunction) {
        case Kill:
            return "kill " + modifyTarget + "\n";
        case Give:
            return "give " + modifyTarget + " " + modifyValue + modifyData + " " + std::to_string(modifyCount) + "\n";
    }
}

ModifyTargetNode::ModifyTargetNode(Node *parent, Parser &parser) : Node(parent, ModifyTarget) {
    modifyTarget = parseTarget(parser.nextWord());

    if (parser.nextSymbol() != '.') throw UnexpectedSymbol({ '.' }, parser.lastSymbol());
    std::string function = parser.nextWord();

    Params params = Params(parser);

    if (function == "kill") modifyFunction = Kill;
    else if (function == "give") {
        modifyFunction = Give;
        modifyValue = params.nextItem();
        modifyCount = params.nextNumber();
        modifyData = params.nextText(true);
    }

    params.finish();
}
