#include "JSON.h"

#include <sstream>

std::string JSON::make() const {
    switch (type) {
        case Number: return asString(number);
        case Text: return "\"" + text + "\"";
        case Boolean: return state ? "true" : "false";
        case Object: {
            std::stringstream stream;
            stream << "{";
            bool first = true;
            for (const auto &pair : objects) {
                if (!first) {
                    stream << ",";
                } else {
                    first = false;
                }
                stream << "\"" << pair.first << "\":" << pair.second->make();
            }
            stream << "}";
            return stream.str();
        }
        case Array: {
            std::stringstream stream;
            stream << "[";
            bool first = true;
            for (const auto &object : array) {
                if (!first) {
                    stream << ",";
                } else {
                    first = false;
                }
                stream << object->make();
            }
            stream << "]";
            return stream.str();
        }
    }
    return "";
}

JSON *JSON::setNumber(const std::string &name, double value) {
    objects[name] = new JSON(value);
    return this;
}

JSON *JSON::setState(const std::string &name, bool value) {
    objects[name] = new JSON(value);
    return this;
}

JSON *JSON::setText(const std::string &name, const std::string &value) {
    objects[name] = new JSON(value);
    return this;
}

JSON *JSON::setObject(const std::string &name, JSON *object) {
    objects[name] = object;
    return this;
}

JSON *JSON::appendNumber(double value) {
    array.push_back(new JSON(value));
    return this;
}

JSON *JSON::appendState(bool value) {
    array.push_back(new JSON(value));
    return this;
}

JSON *JSON::appendText(const std::string &value) {
    array.push_back(new JSON(value));
    return this;
}

JSON *JSON::appendObject(JSON *object) {
    array.push_back(object);
    return this;
}

JSON::JSON(double value) : type(Number), number(value) { }
JSON::JSON(std::string value) : type(Text), text(std::move(value)) { }
JSON::JSON(bool value) : type(Boolean), state(value) { }
JSON::JSON(JSON::Type type) : type(type) { }

JSON::~JSON() {
    switch (type) {
        case Object:
            for (const auto &pair : objects) delete pair.second;
            break;
        case Array:
            for (const auto &object: array) delete object;
            break;
        default: break;
    }
}
