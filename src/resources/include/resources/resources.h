#pragma once

#include <string>
#include <vector>

class Param {
public:
    enum class Type {
        Entity,
        Item,
        Text,
        Number,
        Coordinate
    };

    std::string name;
    Type type;
    std::vector<std::string> allowedValues;
    bool optional = false;
};

class MethodData {
public:

    std::string name;
    std::vector<Param> params;
    std::string source;
};

const std::vector<std::string> &getItemNames();
const std::vector<std::string> &getEntityNames();
const std::vector<MethodData> &getGlobalMethodData();
const std::vector<MethodData> &getTargetMethodData();
