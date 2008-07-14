#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

#include "get_all_includes.h"

namespace bfs = boost::filesystem;

void addToIncludeList(include_list &l, std::string &toAdd);

void get_all_includes(char *path, file_list &h_files, file_list &cpp_files, include_list &includes)
{
	bfs::path initial_path = bfs::system_complete( bfs::path( path, bfs::native ) );

	//include_list includes;

	for(file_list::iterator it = h_files.begin(); it != h_files.end(); it++)
	{
		//std::cout << (initial_path / *it ).string() << std::endl;

		std::ifstream file;
		file.open( (initial_path / *it ).string().c_str(), std::ifstream::in );

		while(file.good())
		{
			std::string line;
			std::getline(file, line);

			if( line.find("#include ") != std::string::npos && line.find("Q") != std::string::npos )
			{
				addToIncludeList(includes, line);
			}
		}

		file.close();
	}

	for(file_list::iterator it = cpp_files.begin(); it != cpp_files.end(); it++)
	{
		//std::cout << (initial_path / *it ).string() << std::endl;

		std::ifstream file;
		file.open( (initial_path / *it ).string().c_str(), std::ifstream::in );

		while(file.good())
		{
			std::string line;
			std::getline(file, line);

			if( line.find("#include ") != std::string::npos && line.find("Q") != std::string::npos )
			{
				addToIncludeList(includes, line);
			}
		}

		file.close();
	}
}

void addToIncludeList(include_list &l, std::string &toAdd)
{
	include_list::iterator result = std::find(l.begin(), l.end(), toAdd);

	if( result == l.end() )
	{
		l.push_back(toAdd);
	}
}