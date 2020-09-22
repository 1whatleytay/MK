#include <util/datapack.h>

#include <util/util.h>
#include <util/json.h>

#include <filesystem>

namespace fs = std::filesystem;

void DataPack::make() {
    if (path.substr(path.size() - 1) != "/" && path.substr(path.size() - 1) != "\\") {
        path += "/";
    }

    // DataPack Directory
    fs::remove_all(path);
    fs::create_directory(path);

    Json json = JsonObjectData {
        { "pack", JsonObjectData {
            { "pack_format", format },
            { "description", description }
        } }
    };

    textTo(path + "pack.mcmeta", json.make());

    // Data Directory
    std::string dataPath = path + "data/";
    fs::create_directory(dataPath);

    // Minecraft Directory
    if (!onTick.empty() || !onLoad.empty()) {
        std::string tagsPath = dataPath + "minecraft/tags/functions/";
        fs::create_directories(tagsPath);

        if (!onTick.empty()) {
            JsonArrayData values;

            for (const std::string &tick : onTick)
                values.push_back(name + ":" + tick);

            Json tick = JsonObjectData {
                { "replace", false },
                { "values", values }
            };
            textTo(tagsPath + "tick.json", tick.make());
        }

        if (!onLoad.empty()) {
            JsonArrayData values;

            for (const std::string &load : onLoad)
                values.push_back(name + ":" + load);

            Json load = JsonObjectData {
                { "replace", false },
                { "values", values }
            };
            textTo(tagsPath + "load.json", load.make());
        }
    }

    // Namespace Directory
    std::string namespacePath = dataPath + name + "/";
    fs::create_directory(namespacePath);

    if (!functions.empty()) {
        std::string functionsPath = namespacePath + "functions/";
        fs::create_directory(functionsPath);

        for (const auto &pair : functions) {
            std::string fileName = pair.first + ".mcfunction";
            textTo(functionsPath + fileName, pair.second);
        }
    }

    if (!recipes.empty()) {
        std::string recipesPath = namespacePath + "recipes/";
        std::string craftingPath = recipesPath + "crafting/";

        fs::create_directory(recipesPath);
        fs::create_directory(craftingPath);

        for (const auto &pair : recipes) {
            std::string fileName = pair.first + ".json";
            textTo(craftingPath + fileName, pair.second);
        }
    }
}

void DataPack::addOnTick(const std::string &functionName) {
    onTick.push_back(functionName);
}

void DataPack::addOnLoad(const std::string &functionName) {
    onLoad.push_back(functionName);
}

void DataPack::addRecipe(const std::string &recipeName, const std::string &source) {
    recipes[recipeName] = source;
}

void DataPack::addFunction(const std::string &functionName, const std::string &source) {
    functions[functionName] = source;
}

void DataPack::setFormat(double value) {
    format = value;
}

void DataPack::setDescription(const std::string &desc) {
    description = desc;
}

void DataPack::setArtifact(bool value) {
    artifact = value;
}

DataPack::DataPack(std::string path, std::string name) : path(std::move(path)), name(std::move(name)) { }
