#include <DataPack.h>

#include <JSON.h>

#include <sstream>

void DataPack::make() {
    if (path.substr(path.size() - 1) != "/" && path.substr(path.size() - 1) != "\\") {
        path += "/";
    }

    // DataPack Directory
    makeDirectory(path);
    try {
        std::string toDelete = textFrom(path + "mk.artifact");
        std::vector<std::string> deleteFiles = split(toDelete);
        for (const std::string &file : deleteFiles) {
            if (!file.empty() && file[0] != '#')
                removeFile(path + file);
        }
    } catch (FileNotFound &e) { }

    std::stringstream pendingFiles;
    pendingFiles << "# Files included here will be updated by MK on recompile.\n";
    pendingFiles << "# May cause development glitches if deleted. Otherwise, delete away!\n";

    // Info File
    JSON *json = (new JSON(JSON::Object))
            ->setObject("pack",
                    (new JSON(JSON::Object))
                    ->setNumber("pack_format", format)
                    ->setText("description", description)
                    );
    textTo(path + "pack.mcmeta", json->make());
    delete json;

    // Data Directory
    std::string dataPath = path + "data/";
    makeDirectory(dataPath);

    // Minecraft Directory
    if (!onTick.empty() || !onLoad.empty()) {
        std::string mcfTagsPath = dataPath + "minecraft/tags/functions/";
        makeDirectory(dataPath + "minecraft/");
        makeDirectory(dataPath + "minecraft/tags/");
        makeDirectory(dataPath + "minecraft/tags/functions/");
        if (!onTick.empty()) {
            JSON *values = new JSON(JSON::Array);
            for (const std::string &tick : onTick) values->appendText(name + ":" + tick);
            JSON *tick = (new JSON(JSON::Object))
                    ->setState("replace", false)
                    ->setObject("values", values);
            textTo(mcfTagsPath + "tick.json", tick->make());
            pendingFiles << "data/minecraft/tags/functions/tick.json\n";
        }

        if (!onLoad.empty()) {
            JSON *values = new JSON(JSON::Array);
            for (const std::string &load : onLoad) values->appendText(name + ":" + load);
            JSON *load = (new JSON(JSON::Object))
                    ->setState("replace", false)
                    ->setObject("values", values);
            textTo(mcfTagsPath + "load.json", load->make());
            pendingFiles << "data/minecraft/tags/functions/load.json\n";
        }
    }

    // Namespace Directory
    std::string namespacePath = dataPath + name + "/";
    makeDirectory(namespacePath);

    if (!functions.empty()) {
        std::string functionsPath = namespacePath + "functions/";
        makeDirectory(functionsPath);

        for (const auto &pair : functions) {
            std::string fileName = pair.first + ".mcfunction";
            textTo(functionsPath + fileName, pair.second);
            pendingFiles << "data/" + name + "/functions/" + fileName + "\n";
        }
    }

    if (!recipes.empty()) {
        std::string recipesPath = namespacePath + "recipes/";
        makeDirectory(recipesPath);
        std::string craftingPath = recipesPath + "crafting/";
        makeDirectory(craftingPath);

        for (const auto &pair : recipes) {
            std::string fileName = pair.first + ".json";
            textTo(craftingPath + fileName, pair.second);
            pendingFiles << "data/" + name + "/recipes/crafting/" + fileName + "\n";
        }
    }

    if (artifact)
        textTo(path + "mk.artifact", pendingFiles.str());
}

void DataPack::addOnTick(const std::string &functionName) {
    onTick.push_back(functionName);
}

void DataPack::addOnLoad(const std::string &functionName) {
    onLoad.push_back(functionName);
}

void DataPack::addFunction(const std::string &functionName, const std::string &source) {
    functions[functionName] = source;
}

void DataPack::addRecipe(const std::string &recipeName, const JSON *json) {
    recipes[recipeName] = json->make();
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
