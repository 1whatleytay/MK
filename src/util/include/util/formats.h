#pragma once

#include <string>

class Parser;

bool isItem(const std::string &target);
bool isEntity(const std::string &target);

std::string parseTarget(Parser &parser);
std::string parseMinecraft(Parser &parser);
std::string parseItem(Parser &parser);
std::string parseEntity(Parser &parser);

std::string parseQuotes(const std::string &text);

std::string parseName(const std::string &name);
