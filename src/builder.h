#ifndef MK_BUILDER_H
#define MK_BUILDER_H

#include <util/util.h>
#include <util/datapack.h>

#include <string>

class Node;
class TagNode;

class Builder {
    std::string source;
    std::string name;

    Node *tree = nullptr;
    DataPack *dataPack = nullptr;

    TagNode *getTag(const std::string &tagName);
public:
    DataPack *getDataPack();

    void build();

    explicit Builder(std::string source);
    static Builder fromFile(const std::string &path);

    ~Builder();
};

#endif //MK_BUILDER_H
