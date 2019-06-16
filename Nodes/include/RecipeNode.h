#ifndef MK_RECIPENODE_H
#define MK_RECIPENODE_H

#include <Node.h>

#include <unordered_map>

class JSON;
class Parser;

class RecipeNode : public Node {
    void defineParams();

    std::unordered_map<std::string, std::string> parameters;
    std::vector<std::string> contents;


public:
    std::string recipeName;

    JSON *createJSON();

    RecipeNode(Node *parent, Parser &parser);
};

#endif //MK_RECIPENODE_H