#include "definitions.h"
#include "get_all_files.h"
#include "get_all_includes.h"
#include "write_pro_file.h"
#include "get_modules_string.h"

#include <iostream>
#include <string>
#include <exception>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char *argv[])
{
	//std::string *path = new std::string();
	std::string path;
	std::string templateType;
	std::string target;
	//std::string *target = new std::string();

	try
	{
		po::options_description general("General options");
		general.add_options()
			("help,h", "help")
			("path,p", po::value<std::string>(&path)->default_value("."), "location of project")
			("name,n", po::value<std::string>(&target)->default_value("Default App"), "application name")
		;

		po::options_description templatetype("Templatetype options");
		templatetype.add_options()
			("app", "Creates a Makefile to build an application")
			("lib", "Creates a Makefile to build a library")
			("subdirs", "Creates a Makefile containing rules for the subdirectories specified using the SUBDIRS variable. Each subdirectory must contain its own project file")
			("vcapp", "Creates a Visual Studio Project file to build an application")
			("vclib", "Creates a Visual Studio Project file to build a library")
		;

		po::options_description all("Allowed Options");
		all.add(general).add(templatetype);

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, all), vm);
		//po::notify(vm);

		if( vm.count("help") )
		{
			std::cout << all;
			return(0);
		}
    }
	catch(std::exception& e)
	{
		std::cout << e.what() << "\n";
    }
/*
	if( argc > 1 )
	{
		if( std::string(argv[1]) == "help" || 
			std::string(argv[1]) == "/?" || 
			std::string(argv[1]) == "-h" || 
			std::string(argv[1]) == "--help" )
		{
			if( argc == 2 )
			{
				std::cout << "usage: " << argv[0] << " [path] [templatetype] [target]" << std::endl << std::endl;
				std::cout << "usage: " << argv[0] << " help [path|templatetype|target] for more inforamtion" << std::endl;
			}

			if( argc > 2 )
			{
				std::cout << "usage: " << argv[0] << " [path] [templatetype] [target]" << std::endl << std::endl;
				
				if( std::string(argv[2]) == "path" )
				{
					std::cout << " path:" << std::endl;
					std::cout << "   location of project" << std::endl;
				}
				else if( std::string(argv[2]) == "templatetype" )
				{
					std::cout << " templatetype:" << std::endl;
					std::cout << "   app (default)" << std::endl;
					std::cout << "     Creates a Makefile to build an application." << std::endl;
					std::cout << "   lib" << std::endl;
					std::cout << "     Creates a Makefile to build a library." << std::endl;
					std::cout << "   subdirs" << std::endl;
					std::cout << "     Creates a Makefile containing rules for the" << std::endl;
					std::cout << "     subdirectories specified using the SUBDIRS" << std::endl;
					std::cout << "     variable. Each subdirectory must contain its" << std::endl;
					std::cout << "     own project file." << std::endl;
					std::cout << "   vcapp" << std::endl;
					std::cout << "     Creates a Visual Studio Project file to build" << std::endl;
					std::cout << "     an application." << std::endl;
					std::cout << "   vclib" << std::endl;
					std::cout << "     Creates a Visual Studio Project file to build" << std::endl;
					std::cout << "     a library." << std::endl;
				}
				else if( std::string(argv[2]) == "target" )
				{
					std::cout << " target:" << std::endl;
					std::cout << "   application name (default: \"Default APP\")" << std::endl;
				}
				else
				{
					std::cout << " error: unknown command ( " << argv[2] << " )" << std::endl;
					std::cout << "   possible commands: path | templatetype | target" << std::endl;
				}
			}
		}
		else
		{		
			std::string templateType("app");
			std::string target("Default APP");

			if( argc > 2 )
			{
				if( std::string( argv[2] ) != "app" && std::string( argv[2] ) != "lib" && std::string( argv[2] ) != "subdirs" && std::string( argv[2] ) != "vcapp" && std::string( argv[2] ) != "vclib" )
				{
					std::cout << " error: invalid templatetype (\"" << argv[2] << "\")" << std::endl;
					std::cout << " use: " << argv[0] << " help templatetype for more information" << std::endl;
					return( -1 );
				}
				templateType = argv[2];
			}

			if( argc > 3 )
			{
				target = argv[3];
			}

			file_list h_files, cpp_files, qrc_files, uic_files;
			path_list depend_paths;
			include_list includes;

			get_all_files(argv[1], h_files, cpp_files, qrc_files, uic_files, depend_paths);

			get_all_includes(argv[1], h_files, cpp_files, includes);

			std::string modules_string = get_modules_string(includes);

			write_pro_file(h_files, cpp_files, qrc_files, uic_files, depend_paths, modules_string, templateType, target);
		}
	}
	else
	{
		std::cerr << "usage: " << argv[0] << " [path] [templateType] [target]" << std::endl << std::endl;
		std::cerr << "usage: " << argv[0] << " help [path|templatetype|target] for more inforamtion" << std::endl;
	}
*/
}
