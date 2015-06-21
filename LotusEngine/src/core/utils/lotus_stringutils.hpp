#ifndef	LOTUS_STRING_UTILS_HPP_INCLUDED
#define LOTUS_STRING_UTILS_HPP_INCLUDED

#include <string>
#include <vector>

namespace StringUtils
{
	std::vector<std::string> getTokens(const std::string &text, const std::string &delim);
	std::string &removeWhiteSpace(std::string &string);
}

#endif

