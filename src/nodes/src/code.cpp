#include <nodes/code.h>

#include <nodes/tag.h>
#include <nodes/function.h>
#include <nodes/command.h>
#include <nodes/score.h>
#include <nodes/modify_score.h>
#include <nodes/modify_target.h>
#include <nodes/execute.h>
#include <nodes/method.h>
#include <nodes/player.h>
#include <nodes/recipe.h>

#include <util/parser.h>

#include <sstream>

std::string attributes[] = {
        "load",
        "tick",
        "ordered",
        "unordered",
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

CodeNode::CodeNode(Node *parent, const std::string &source) : Node(parent, Type::Code) {
    Parser parser = Parser(source);

    std::string next;

    std::vector<std::string> attr;

    while (!parser.reachedEnd()) {
        attr.clear();
        next = parser.next();
        if (std::find(std::begin(attributes), std::end(attributes), next) != std::end(attributes)) {
            attr.push_back(next);
            continue;
        }

        parser.rollback();

        if (next == "#") {
            children.push_back(std::make_shared<TagNode>(this, parser));
        } else if (next == "func") {
            children.push_back(std::make_shared<FunctionNode>(this, parser));
        } else if (next == "score") {
            children.push_back(std::make_shared<ScoreNode>(this, parser));
        } else if (next == "player") {
            children.push_back(std::make_shared<PlayerNode>(this, parser));
        } else if (next == "as") {
            children.push_back(std::make_shared<ExecuteNode>(this, parser));
        } else if (next == "/") {
            children.push_back(std::make_shared<CommandNode>(this, parser));
        } else if (next == "recipe") {
            children.push_back(std::make_shared<RecipeNode>(this, parser));
        } else if (next == "//") { // not a great way to make comments i suppose
            parser.until({ "\n" });
        } else {
            ScoreNode *score = (ScoreNode *) parentSearch([next](Node *node) {
                return node->type == Type::Score && ((ScoreNode *) node)->scoreName == next;
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
                node = new MethodNode(this, parser);
//                throw UnexpectedLine(parser.untilNextSymbol('\n'));
            }
        }
    }
}
