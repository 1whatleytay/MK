#include <nodes/modify_score.h>

#include <util/parser.h>
#include <util/formats.h>

#include <nodes/score.h>

#include <fmt/format.h>

std::string ModifyScoreNode::getSource() {
    switch (modifyOp) {
        case SetDisplay:
            return fmt::format("scoreboard objectives setdisplay {} {}\n", modifyTarget, modifyScore->scoreName);
        case Hide: // Instead of .hide(), do sidebar.clear(), list.clear(), aboveName.clear().
            return fmt::format("scoreboard objectives setdisplay {}\n", modifyTarget);
        case Add:
            return fmt::format("scoreboard players add {} {} {}\n", modifyTarget, modifyScore->scoreName, modifyValue);
        case Sub:
            return fmt::format("scoreboard players remove {} {} {}\n", modifyTarget, modifyScore->scoreName, modifyValue);
        case Set:
            return fmt::format("scoreboard players set {} {} {}", modifyTarget, modifyScore->scoreName, modifyValue);
        default:
            throw std::runtime_error("Internal error related to modify score.");
    }
}

ModifyScoreNode::ModifyScoreNode(Node *parent, Parser &parser) : Node(parent, Type::ModifyScore) {
    std::string target = parser.next();
    modifyScore = (ScoreNode *)parentSearch([target](Node *node) {
        return node->type == Type::Score && ((ScoreNode *)node)->scoreName == target;
    }); // TODO: Do at build time.

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
            modifyValue = std::stoi(params.nextNumber());
            break;

        case SetDisplay:
            modifyTarget = params.nextText();
            break;

        default: break;
    }

    params.finish();

    if (parser.nextWord() == "where") {
        if (parser.nextSymbol() != '(') throw UnexpectedSymbol({ '(' }, parser.lastSymbol());
        parser.pushMode(Parser::Original);
        modifyTarget += "[" + parser.untilNextSymbol(')') + "]";
        parser.popMode();
        if (parser.nextSymbol() != ')') throw UnexpectedSymbol({ ')' }, parser.lastSymbol());
    } else {
        parser.rollback();
    }
}
