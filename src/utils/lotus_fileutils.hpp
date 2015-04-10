#ifndef LOTUS_FILE_UTILS_HPP_INCLUDED
#define LOTUS_FILE_UTILS_HPP_INCLUDED

#include <string>

class FileUtils
{
public:
	static std::string readFile(const std::string &fileName);
};

#endif