#include <RecipeNode.h>

#include <JSON.h>
#include <Formats.h>
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

    JSON *json = new JSON(JSON::Object);
    json->setText("type", type);
    json->setObject("result", (new JSON(JSON::Object))
        ->setNumber("count", std::stod(parameters["count"]))
        ->setText("item", parseItemOrBlock(parameters["item"]))
    );

    if (recipeType == RecipeType::Shaped) {

    } else if (recipeType == RecipeType::Shapeless) {
        if (contents.empty() || contents.size() > 9)
            throw Unexpected("contents size from 1 - 9", std::to_string(contents.size()) + " elements");

        JSON *ingredients = new JSON(JSON::Array);

        for (const std::string &content : contents) {
            std::string result;

            if (isItemOrBlock(content)) {
                result = parseItemOrBlock(content);
            } else {
                if (parameters.find(content) != parameters.end()) {
                    result = parseItemOrBlock(parameters[content]);
                } else {
                    throw Unexpected("item, block or alias", content);
                }
            }

            ingredients->appendObject((new JSON(JSON::Object))->setText("item", result));
        }

        json->setObject("ingredients", ingredients);
    } else throw Unexpected("recipe type", std::to_string((int)recipeType));

    return json;
}

RecipeNode::RecipeNode(Node *parent, Parser &parser) : Node(parent, Recipe) {
    if (parser.nextWord() != "recipe") throw Unsupported("Weirdly Defined Recipe");
    recipeName = parseName(parser.nextWord());

    defineParams();

    if (parser.nextSymbol() != '{') throw UnexpectedSymbol({ '{' }, parser.lastSymbol());
    while (!parser.reachedEnd() && parser.nextSymbol() != '}') {
        parser.rollback();
        std::string key = parser.nextWord();

        if (parser.nextSymbol() != ':') throw UnexpectedSymbol({ ':' }, parser.lastSymbol());

        if (key == "contents") {
            if (parser.nextSymbol() != '{') throw UnexpectedSymbol({ '{' }, parser.lastSymbol());
            do {
                std::string get = parser.untilNextSymbols({',', '}'});
                if (!get.empty()) contents.push_back(get);
            } while (parser.nextSymbol() == ',');
            parser.rollback();
            if (parser.nextSymbol() != '}') throw UnexpectedSymbol({ '}' }, parser.lastSymbol());
        } else {
            std::string value = parser.untilNextSymbols({ '\n', ';' });
            if (parser.nextSymbol() != ';') parser.rollback();
            parameters[key] = value;
        }
    }

    if (parameters["type"] == "shaped") recipeType = RecipeType::Shaped;
    else if (parameters["type"] == "shapeless") recipeType = RecipeType::Shapeless;
    else throw Unexpected("recipe type", parameters["type"]);

    if (recipeType == RecipeType::Shaped &&
        (parameters.find("width") != parameters.end() || parameters.find("height") != parameters.end())) {
        throw Unexpected("no width or height for shapeless recipe", "width or height");
    }
}
