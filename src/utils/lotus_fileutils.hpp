#ifndef LOTUS_FILE_UTILS_HPP_INCLUDED
#define LOTUS_FILE_UTILS_HPP_INCLUDED

#include <string>

namespace lotus {

	class FileUtils
	{
	public:
		static std::string readFile(const std::string &fileName);
	};

}

#endif