#include "Builder.h"

#include <Parser.h>

#include <CodeNode.h>
#include <TagNode.h>
#include <FunctionNode.h>
#include <ScoreNode.h>

#include <sstream>

TagNode* Builder::getTag(const std::string& tagName) {
    return (TagNode *)tree->search([tagName](Node *node) {
        return node->type == Node::Tag && ((TagNode *)node)->tagName == tagName;
    });
}

DataPack* Builder::getDataPack() { return dataPack; }

void Builder::build() {
    log("[Building Main]");
    tree = new CodeNode(nullptr, source);
    tree->verify();

    TagNode *nameNode = getTag("name");
    TagNode *descriptionNode = getTag("description");
    TagNode *formatNode = getTag("format");
    TagNode *initNode = getTag("init");

    std::string projectName = "mk";
    std::string initName = "__init";

    if (nameNode) { projectName = nameNode->tagValue; }
    if (initNode) { initName = initNode->tagValue; }

    log("[Creating DataPack " + projectName + "]");
    dataPack = new DataPack(projectName, projectName);
    if (descriptionNode) dataPack->setDescription(descriptionNode->tagValue);
    if (formatNode) dataPack->setFormat(std::stod(formatNode->tagValue));

    tree->search([this](Node *node) {
        if (node->type == Node::Function) {
            FunctionNode *function = (FunctionNode *)node;
            dataPack->addFunction(function->funcName, function->getSource());
            if (function->onLoad) dataPack->addOnLoad(function->funcName);
            if (function->onTick) dataPack->addOnTick(function->funcName);
        }
        return false;
    });

    // Init function for creating scoreboard values.
    std::stringstream initStream;

    tree->search([this, &initStream](Node *node) {
        if (node->type == Node::Score)
            initStream << ((ScoreNode *)node)->createScore();
        return false;
    });

    std::string initSource = initStream.str();
    if (!initSource.empty()) {
        dataPack->addFunction(initName, initSource);
        // Priority on load.
        dataPack->addOnLoad(initName);
    }

    dataPack->make();
}

Builder::Builder(std::string source) : source(std::move(source)) { }

Builder Builder::fromFile(const std::string &path) {
    return Builder(textFrom(path));
}

Builder::~Builder() {
    delete tree;
    delete dataPack;
}
