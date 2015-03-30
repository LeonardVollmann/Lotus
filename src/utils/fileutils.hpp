#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <string>

namespace lotus {

	class FileUtils
	{
	public:
		static std::string readFile(const std::string &fileName);
	};

}

#endif