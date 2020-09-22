#include <util/json.h>

#include <util/util.h>
#include <util/formats.h>

#include <sstream>

std::string Json::make() const {
    switch (type) {
        case Type::Number: return asString(number);
        case Type::Text: return "\"" + text + "\"";
        case Type::Boolean: return boolean ? "true" : "false";

        case Type::Object: {
            std::stringstream stream;
            stream << "{";
            bool first = true;
            for (const auto &e : object) {
                if (!first) {
                    stream << ",";
                } else {
                    first = false;
                }
                stream << "\"" << e.first << "\":" << e.second.make();
            }
            stream << "}";
            return stream.str();
        }

        case Type::Array: {
            std::stringstream stream;
            stream << "[";
            bool first = true;
            for (const auto &e : array) {
                if (!first) {
                    stream << ",";
                } else {
                    first = false;
                }
                stream << e.make();
            }
            stream << "]";
            return stream.str();
        }

        default:
            return "";
    }
}

Json &Json::operator=(bool value) {
    *this = Json(value);
    return *this;
}
Json &Json::operator=(double value) {
    *this = Json(value);
    return *this;
}
Json &Json::operator=(std::string value) {
    *this = Json(value);
    return *this;
}
Json &Json::operator=(std::vector<Json> value) {
    *this = Json(value);
    return *this;
}
Json &Json::operator=(std::unordered_map<std::string, Json> value) {
    *this = Json(value);
    return *this;
}

Json::Json(bool value) : type(Type::Boolean), boolean(value) { }
Json::Json(double value) : type(Type::Number), number(value) { }
Json::Json(std::string value) : type(Type::Text), text(std::move(value)) { }
Json::Json(std::vector<Json> value) : type(Type::Array), array(std::move(value)) { }
Json::Json(std::unordered_map<std::string, Json> value) : type(Type::Object), object(std::move(value)) { }
