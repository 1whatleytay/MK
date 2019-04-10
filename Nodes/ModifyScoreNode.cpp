#include "ModifyScoreNode.h"

#include <Parser.h>
#include <Params.h>
#include <Formats.h>

#include <ScoreNode.h>

std::string ModifyScoreNode::getSource() {
    switch (modifyOp) {
        case SetDisplay:
            return "scoreboard objectives setdisplay " + modifyTarget + " " + modifyScore->scoreName + "\n";
        case Hide: // Instead of .hide(), do sidebar.clear(), list.clear(), aboveName.clear().
            return "scoreboard objectives setdisplay " + modifyTarget + "\n";

        case Add:
            return "scoreboard players add " + modifyTarget + " "
                + modifyScore->scoreName + " " + std::to_string(modifyValue) + "\n";
        case Sub:
            return "scoreboard players remove " + modifyTarget + " "
                + modifyScore->scoreName + " " + std::to_string(modifyValue) + "\n";
        case Set:
            return "scoreboard players set " + modifyTarget + " "
                + modifyScore->scoreName + " " + std::to_string(modifyValue) + "\n";
        default: throw Unsupported("Error Modify Op");
    }
}

ModifyScoreNode::ModifyScoreNode(Node *parent, Parser &parser) : Node(parent, ModifyScore) {
    std::string target = parser.nextWord();
    modifyScore = (ScoreNode *)parentSearch([target](Node *node) {
        return node->type == Score && ((ScoreNode *)node)->scoreName == target;
    });

    switch (parser.nextSymbol()) {
        case '.': {
            std::string func = parser.nextWord();
            if (func == "setDisplay") modifyOp = SetDisplay;
            else if (func == "hide") modifyOp = Hide;

            else if (func == "set") modifyOp = Set;
            else if (func == "add") modifyOp = Add;
            else if (func == "sub" || func == "subtract") modifyOp = Sub;
            break;
        }
        default:
            throw UnexpectedSymbol({ '.', '+', '-' }, parser.lastSymbol());
    }

    Params params = Params(parser);

    switch (modifyOp) {
        case Set:
        case Add:
        case Sub:
            modifyTarget = parseTarget(params.nextText());
            modifyValue = params.nextNumber();
            break;

        case SetDisplay:
            modifyTarget = params.nextText();
            break;

        default: break;
    }

    params.finish();
}
