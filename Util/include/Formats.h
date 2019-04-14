#ifndef MK_CHECKER_H
#define MK_CHECKER_H

#include <Util.h>

std::string parseTarget(const std::string &target);
std::string parseMinecraft(const std::string &target);
std::string parseItemOrBlock(const std::string &target);
std::string parseEntity(const std::string &target);

std::string parseQuotes(const std::string &text);

#endif //MK_CHECKER_H
