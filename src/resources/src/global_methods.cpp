#include <resources/resources.h>

const std::vector<MethodData> globalMethods = {
    { "help", {
        { "command", Param::Type::Text, { }, true },
    }, "help [command]" },
    { "say", {
        { "text", Param::Type::Text },
    }, "say [text]" },
    { "weather", {
        { "weather", Param::Type::Text, {"clear", "rain", "thunder", } },
    }, "weather [weather]" },
    { "clone", {
        { "c1", Param::Type::Coordinate },
        { "c2", Param::Type::Coordinate },
        { "c3", Param::Type::Coordinate },
        { "mask", Param::Type::Text, {"filtered", "masked", "replace", }, true },
        { "mode", Param::Type::Text, {"force", "move", "normal", }, true },
        { "block", Param::Type::Item, { }, true },
    }, "clone [c1] [c2] [c3] [mask] [mode] [block]" },
    { "difficulty", {
        { "level", Param::Type::Text, {"peaceful", "easy", "normal", "hard", } },
    }, "difficulty [level]" },
    { "summon", {
        { "entity", Param::Type::Entity },
        { "coord", Param::Type::Coordinate, { }, true },
        { "data", Param::Type::Text, { }, true },
    }, "summon [entity] [coord] [data]" },
    { "setTime", {
        { "value", Param::Type::Text },
    }, "time set [value]" },
    { "addTime", {
        { "value", Param::Type::Text },
    }, "time add [value]" },
    { "queryTime", {
        { "type", Param::Type::Text, {"daytime", "gametime", "day", } },
    }, "time query [type]" },
};

const std::vector<MethodData> &getGlobalMethodData() { return globalMethods; }
