#ifndef MK_JSON_H
#define MK_JSON_H

#include <Util.h>

#include <unordered_map>

class JSON {
public:
    enum Type {
        Number,
        Text,
        Boolean,
        Object,
        Array
    };

private:
    Type type;

    double number = 0;
    bool state = false;
    std::string text;
    std::unordered_map<std::string, JSON *> objects;
    std::vector<JSON *> array;

public:
    JSON *setNumber(const std::string &name, double value);
    JSON *setState(const std::string &name, bool state);
    JSON *setText(const std::string &name, const std::string &value);
    JSON *setObject(const std::string &name, JSON *object);

    JSON *appendNumber(double value);
    JSON *appendState(bool value);
    JSON *appendText(const std::string &value);
    JSON *appendObject(JSON *object);

    std::string make() const;

    explicit JSON(double value);
    explicit JSON(std::string value);
    explicit JSON(bool value);
    explicit JSON(Type type);

    ~JSON();
};

#endif //MK_JSON_H
