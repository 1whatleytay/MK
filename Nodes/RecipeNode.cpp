#include <RecipeNode.h>

#include <JSON.h>
#include <Parser.h>

void RecipeNode::defineParams() {
    parameters["type"] = "shaped";

    parameters["width"] = "3";
    parameters["height"] = "3";

    parameters["item"] = "";
    parameters["count"] = "1";
}

JSON* RecipeNode::createJSON() {
    std::string type;
    if (parameters["type"] == "shaped") type = "crafting_shaped";
    if (parameters["type"] == "shapeless") type = "crafting_shapeless";

    return (new JSON(JSON::Object))
        ->setText("type", type)
        ->setObject("pattern",
            (new JSON(JSON::Array))->appendText(""));
}

RecipeNode::RecipeNode(Node *parent, Parser &parser) : Node(parent, Recipe) {
    if (parser.nextWord() != "recipe") throw Unsupported("Weirdly Defined Recipe");
    recipeName = parser.nextWord();

    defineParams();

    if (parser.nextSymbol() != '{') throw UnexpectedSymbol({ '{' }, parser.lastSymbol());
    while (!parser.reachedEnd() && parser.nextSymbol() != '}') {
        parser.rollback();
        std::string key = parser.nextWord();

        if (parser.nextSymbol() != ':') throw UnexpectedSymbol({ ':' }, parser.lastSymbol());

        if (key == "contents") {
            if (parser.nextSymbol() != '{') throw UnexpectedSymbol({ '{' }, parser.lastSymbol());
            do {
                contents.push_back(parser.untilNextSymbols({',', '}'}));
            } while (parser.nextSymbol() == ',');
            parser.rollback();
            if (parser.nextSymbol() != '}') throw UnexpectedSymbol({ '}' }, parser.lastSymbol());
        } else {
            std::string value = parser.untilNextSymbols({ '\n', ';' });
            if (parser.nextSymbol() != ';') parser.rollback();
            parameters[key] = value;
        }
    }
}
