#ifndef MK_METHODINFO_H
#define MK_METHODINFO_H

#include <Params.h>

class MethodInfo {
public:
    class Param {
    public:
        std::string name;
        Params::Type type;
        std::vector<std::string> allowedValues;
        bool optional = false;
    };

    std::string name;
    std::vector<Param> params;
    std::string source;
};

#endif //MK_METHODINFO_H
