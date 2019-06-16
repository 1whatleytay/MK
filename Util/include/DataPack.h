#ifndef MK_DATAPACK_H
#define MK_DATAPACK_H

#include <Util.h>

#include <unordered_map>

class JSON;

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
    void addFunction(const std::string &functionName, const std::string &source);
    void addRecipe(const std::string &recipeName, const JSON *json);

    void setFormat(double value);
    void setDescription(const std::string &desc);
    void setArtifact(bool value);

    DataPack(std::string path, std::string name);
};

#endif //MK_DATAPACK_H
