#include "get_all_includes.h"

#include <iostream>
#include <fstream>

namespace PFG
{

void getAllIncludes(std::string &path, stringList &h_files, stringList &cpp_files, stringList &includes)
{
	//includeList includes;

	for(stringList::iterator it = h_files.begin(); it != h_files.end(); it++)
	{
		std::ifstream file( (*it).c_str(), std::ifstream::in );

		while(file)
		{
			std::string line;
			std::getline(file, line);

			if( line.find("#include ") != std::string::npos && line.find("Q") != std::string::npos )
			{
				addToStringList(includes, line);
			}
		}
	}

	for(stringList::iterator it = cpp_files.begin(); it != cpp_files.end(); it++)
	{
		std::ifstream file( (*it).c_str(), std::ifstream::in );

		while(file)
		{
			std::string line;
			std::getline(file, line);

			if( line.find("//") == std::string::npos && 
				line.find("#include ") != std::string::npos && 
				line.find("Q") != std::string::npos
			)
			{
				addToStringList(includes, line);
			}
		}

		file.close();
	}
}

} // namespace PFG

