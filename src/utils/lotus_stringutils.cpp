#include "lotus_stringutils.hpp"

std::vector<std::string> StringUtils::getTokens(const std::string &text, const std::string &delim)
{
	std::vector<std::string> result;
	char *ctext = new char[text.size() + 1];
	strcpy(ctext, text.c_str());
	
	char *token = strtok(ctext, delim.c_str());
	while (token)
	{
		result.push_back((std::string) token);
		token = strtok(nullptr, delim.c_str());
	}
	
	delete ctext;
	return result;
}

std::string &StringUtils::removeWhiteSpace(std::string &string)
{
	string.erase(remove(string.begin(), string.end(), ' '), string.end());
	string.erase(remove(string.begin(), string.end(), '\t'), string.end());
	return string;
}