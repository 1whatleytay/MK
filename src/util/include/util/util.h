#pragma once

#include <string>
#include <vector>

std::string textFrom(const std::string &path);
std::vector<unsigned> dataFrom(const std::string &path);
void textTo(const std::string &path, const std::string &text);
void dataTo(const std::string &path, std::vector<unsigned> data);

std::string asString(double value);
bool isDigits(const std::string &text);
bool isCaptial(const std::string &text);
std::vector<std::string> split(const std::string &text);
