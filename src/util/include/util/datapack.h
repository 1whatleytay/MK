#pragma once

#include <util/util.h>

#include <string>
#include <vector>
#include <unordered_map>

class DataPack {
    std::string name;
    std::string description;
    double format = 1;

    bool artifact = true;

    std::string path;

    std::vector<std::string> onLoad;
    std::vector<std::string> onTick;

    std::unordered_map<std::string, std::string> functions;
    std::unordered_map<std::string, std::string> recipes;
public:
    void make();

    void addOnTick(const std::string &functionName);
    void addOnLoad(const std::string &functionName);
    void addRecipe(const std::string &recipeName, const std::string &source);
    void addFunction(const std::string &functionName, const std::string &source);

    void setFormat(double value);
    void setDescription(const std::string &desc);
    void setArtifact(bool value);

    DataPack(std::string path, std::string name);
};
