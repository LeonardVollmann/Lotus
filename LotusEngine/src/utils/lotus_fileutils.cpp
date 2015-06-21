#include "lotus_fileutils.hpp"
#include <iostream>
#include <fstream>

std::string FileUtils::readFile(const std::string &fileName)
{
	std::ifstream file;
	file.open(fileName);
	
	std::string output;
	std::string line;
	
	if (file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to read file: " << fileName << std::endl;
	}
		
	return output;
}