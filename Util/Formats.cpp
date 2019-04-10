#include <Formats.h>

#include <unordered_map>

std::unordered_map<std::string, std::string> targetAliases = {
        { "nearest", "@p" },
        { "everything", "@e" },
        { "everyone", "@a" },
        { "random", "@r" },
        { "self", "@s" },
};

const std::string minecraft = "minecraft:";

std::string parseTarget(const std::string &target) {
    if (targetAliases.find(target) != targetAliases.end()) return targetAliases[target];
    return target;
}

std::string parseMinecraft(const std::string &target) {
    if (target.substr(0, minecraft.size()) != minecraft) return minecraft + target;
    return target;
}
