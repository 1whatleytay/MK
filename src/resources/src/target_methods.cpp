#include <resources/resources.h>

const std::vector<MethodData> targetMethods = {
    { "kill", { }, "kill [target]" },
    { "give", {
        { "item", Param::Type::Item },
        { "count", Param::Type::Number },
        { "data", Param::Type::Text, { }, true },
    }, "give [target] [item][data] [count]" },
    { "playSound", {
        { "sound", Param::Type::Text },
        { "source", Param::Type::Text, {"master", "music", "record", "weather", "block", "hostile", "neutral", "player", "ambient", "voice", } },
        { "coord", Param::Type::Coordinate, { }, true },
        { "volume", Param::Type::Text, { }, true },
        { "pitch", Param::Type::Text, { }, true },
        { "minVolume", Param::Type::Text, { }, true },
    }, "playsound [sound] [source] [target] [coord] [volume] [pitch] [minVolume]" },
    { "gamemode", {
        { "mode", Param::Type::Text, {"survival", "creative", "adventure", "spectator", } },
    }, "gamemode [mode] [target]" },
    { "addTag", {
        { "name", Param::Type::Text },
    }, "tag [target] add [name]" },
    { "removeTag", {
        { "name", Param::Type::Text },
    }, "tag [target] remove [name]" },
    { "listTags", { }, "tag [target] list" },
};

const std::vector<MethodData> &getGlobalMethodData() { return targetMethods; }
