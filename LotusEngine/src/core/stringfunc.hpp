#pragma once

#include <string>
#include <vector>

namespace lotus
{

std::vector<std::string> tokenize(const std::string &str, char delim);

std::string &removeWhiteSpace(std::string &str);
std::string &removeWhiteSpaceFront(std::string &str);
std::string &removeWhiteSpaceBack(std::string &str);

bool startsWith(const std::string &str, const std::string &start);
bool endsWith(const std::string &str, const std::string &end);
bool contains(const std::string &str, const std::string c);

std::string &toUpperCase(std::string &str);
std::string &toLowerCase(std::string &str);

std::string join(const std::vector<std::string> &strings, const std::string &separator);

} // namespace lotus