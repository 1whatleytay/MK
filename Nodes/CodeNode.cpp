#include "CodeNode.h"

#include <Parser.h>

#include <TagNode.h>
#include <FunctionNode.h>
#include <CommandNode.h>
#include <ScoreNode.h>
#include <ModifyScoreNode.h>
#include <ExecuteNode.h>
#include <ModifyTargetNode.h>
#include <MethodNode.h>
#include <PlayerNode.h>

#include <sstream>

std::string attributes[] = {
        "load",
        "tick"
};

std::string targetNames[] = {
        "nearest", "@p",
        "everything", "@e",
        "everyone", "@e",
        "random", "@r",
        "self", "@s",
};

std::string CodeNode::getSource() {
    std::stringstream stream;

    for (Node *child : children) {
        stream << child->getSource();
    }

    return stream.str();
}

CodeNode::CodeNode(Node *parent, const std::string &source) : Node(parent, Code), source(source) {
    Parser parser = Parser(source);

    std::string next;

    std::vector<std::string> attr;

    while (!(next = parser.nextWord()).empty()) {
        if (std::find(std::begin(attributes), std::end(attributes), next) != std::end(attributes)) {
            attr.push_back(next);
            continue;
        }

        Node *node = nullptr;

        parser.rollback();

        if (next == "#") {
            node = new TagNode(this, parser);
        } else if (next == "func") {
            node = new FunctionNode(this, parser, attr);
        } else if (next == "score") {
            node = new ScoreNode(this, parser);
        } else if (next == "player") {
            node = new PlayerNode(this, parser);
        } else if (next == "as") {
            node = new ExecuteNode(this, parser);
        } else if (next == "/") {
            node = new CommandNode(this, parser.nextSymbol() + parser.untilNextSymbols({'\n', ';', '/'}));
        } else if (next == "//") {
            parser.untilNextSymbol('\n');
        } else {
            ScoreNode *score = (ScoreNode *) parentSearch([next](Node *node) {
                return node->type == Score && ((ScoreNode *) node)->scoreName == next;
            });
            // EntityNode

            bool generalTarget =
                    std::find(std::begin(targetNames), std::end(targetNames), next) != std::end(targetNames);

            if (score) {
                node = new ModifyScoreNode(this, parser);
            } else if (generalTarget) {
                node = new ModifyTargetNode(this, parser);
            } else if (MethodNode::hasMethod(next)) {
                node = new MethodNode(this, parser);
            } else if (next == ";") {
                parser.nextSymbol();
            } else {
                throw UnexpectedLine(parser.untilNextSymbol('\n'));
            }
        }

        if (node) {
            children.push_back(node);
            attr.clear();
        }
    }
}
