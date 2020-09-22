#pragma once

#include <Util.h>

#include <string>
#include <vector>
#include <unordered_map>

class Json {
    enum class Type {
        None,
        Number,
        Text,
        Boolean,
        Array,
        Object,
    };

    Type type = Type::None;

    double number = 0;
    std::string text;
    bool boolean = false;
    std::vector<Json> array;
    std::unordered_map<std::string, Json> object;

public:
    std::string make() const;

    Json &operator=(bool value);
    Json &operator=(double value);
    Json &operator=(std::string value);
    Json &operator=(std::vector<Json> value);
    Json &operator=(std::unordered_map<std::string, Json> value);

    Json() = default;
    Json(bool value);
    Json(double value);
    Json(std::string value);
    Json(std::vector<Json> value);
    Json(std::unordered_map<std::string, Json> value);
};

using JsonArrayData = std::vector<Json>;
using JsonObjectData = std::unordered_map<std::string, Json>;
