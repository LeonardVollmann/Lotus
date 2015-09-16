#include "stringfunc.hpp"

#include <cctype>
#include <sstream>
#include <iterator>
#include <algorithm>

namespace lotus {

	std::vector<std::string> tokenize(const std::string &str, char delim)
	{
		std::vector<std::string> result;

		std::istringstream stream(str);
		for(std::string token; getline(stream, token, delim);)
		{
			if (token.size() == 0) continue;
			result.push_back(token);
		}
		
		return result;
	}

	std::string &removeWhiteSpace(std::string &str)
	{
		auto it = str.begin();
		while (it < str.end())
		{
			while (isspace(*it))
			{
				str.erase(it);
			}
			it++;
		}

		return str;
	}

	std::string &removeWhiteSpaceFront(std::string &str)
	{
		while (isspace(str[0]))
		{
			str.erase(0, 1);
		}

		return str;
	}

	std::string &removeWhiteSpaceBack(std::string &str)
	{
		unsigned int stringLength = (unsigned int) str.size();
		while (isspace(str[stringLength - 1]))
		{
			str.erase(--stringLength);
		}

		return str;
	}

	bool startsWith(const std::string &str, const std::string &start)
	{
		return str.substr(0, start.size()) == start;
	}

	bool endsWith(const std::string &str, const std::string &end)
	{
		const unsigned int stringLength = (unsigned int) str.size();
		return str.substr(stringLength - end.size(), stringLength) == end;
	}

	bool contains(const std::string &str, const std::string c)
	{
		return str.find(c) != std::string::npos;
	}

	std::string &toUpperCase(std::string &str)
	{
		for (auto it = str.begin(); it < str.end(); it++)
		{
			*it = toupper(*it);
		}

		return str;
	}

	std::string &toLowerCase(std::string &str)
	{
		for (auto it = str.begin(); it < str.end(); it++)
		{
			*it = tolower(*it);
		}

		return str;
	}

	std::string join(const std::vector<std::string> &strings, const std::string &separator)
	{
		std::string result;

		for (auto it = strings.begin(); it < strings.end(); it++)
		{
			result += *it;

			if (it != strings.end() - 1)
			{
				result += separator;
			}
		}

		return result;
	}

}
