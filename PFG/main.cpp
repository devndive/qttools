#include "definitions.h"
#include "get_all_files.h"
#include "get_all_includes.h"
#include "write_pro_file.h"
#include "get_modules.h"

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char *argv[])
{
	try
	{
		std::string path, appName, outputFile, templateType, help;
		PFG::stringList libDirs, libs;
		std::streambuf* sbuf(std::cout.rdbuf());

		po::options_description general("General options", 76);
		general.add_options()
			("help,h", po::value<std::string>(&help)->default_value("all"), "help message, options are all|general|modules")
			("input-dir,i", po::value<std::string>(&path)->default_value("."), "location of project")
			("name,n", po::value<std::string>(&appName)->default_value("Default App"), "application name")
			("output-file,o", po::value<std::string>(&outputFile)->default_value(""), "name of output file, if omitted the standard output is used")
			("template-type,t", po::value<std::string>(&templateType)->default_value("app"), "templatetypes:\n\n"
					" app \t(default) Creates a Makefile to build an application.\n"
					" lib \tCreates a Makefile to build a library.\n"
					" sub \tCreates a Makefile containing rules for the subdirectories specified using the SUBDIRS variable. Each subdirectory must contain its own project file.\n"
					" vca \tCreates a Visual Studio Project file to build an application.\n"
					" vcl \tCreates a Visual Studio Project file to build a library.")
			("lib-dirs,L", po::value<PFG::stringList>(&libDirs), "extra library dirs")
			("libs,l", po::value<PFG::stringList>(&libs), "extra libraries")
		;

		po::options_description modules("Module options", 76);
		modules.add_options()
			("core", "use qt core module")
			("no-core", "do not use qt core (use with caution)")
			("gui", "use qt gui module")
			("no-gui", "do not use qt gui (use with caution)")
			("network", "use qt network module")
			("no-network", "do not use qt network module")
			("opengl", "use qt opengl module")
			("no-opengl", "do not use qt opengl module")
			("sql", "use qt sql module")
			("no-sql", "do not use qt sql module")
			("svg", "use qt svg module")
			("no-svg", "do not use qt svg module")
			("qt3support", "use qt3support module")
			("no-qt3support", "do not use qt3support module")
			("xml", "use qt xml support")
			("no-xml", "do not use qt xml support")
		;

		po::options_description all("Allowed options");
		all.add(general).add(modules);

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, all), vm);
		po::notify(vm);

		if( vm.count("help") )
		{
			if( help == "all" )
				std::cout << all;
			else if( help == "general" )
				std::cout << general;
			else if( help == "modules" )
				std::cout << modules;
			else
				std::cout << all;

			std::cout << std::endl;
			std::cout << "For most users no module options, no libs and no lib-dirs are needed. ";
			std::cout << "You should probably be fine with --input-dir, --name and --output-file";
			std::cout << std::endl << std::endl;
			std::cout << "e.g.:" << std::endl;
			std::cout << "  PFG --input-dir ~/qttools/PFG/ --name PFG --output-file PFG.pro";
			std::cout << std::endl << std::endl;

			return(0);
		}

		std::ofstream outputFileStream;
		if( vm.count("output-file") )
		{
			if( !vm["output-file"].as<std::string>().empty() )
			{
				outputFileStream.open(vm["output-file"].as<std::string>().c_str(), std::ofstream::out);
				sbuf = outputFileStream.rdbuf();
			}
		}

		if( vm.count("template-type") )
		{
			if( templateType != "app" && templateType != "lib" && templateType != "sub" && templateType != "vca" && templateType != "vcl" )
			{
				std::cerr << "ERROR: incorrect template type. Use app|lib|sub|vca|vcl!" << std::endl;
				std::cerr << "Try " << argv[0] << " --help for mor information on template types" << std::endl;
				return(0);
			}

			if( templateType == "vca" ) templateType = "vcapp";
			if( templateType == "vcl" ) templateType = "vclib";
		}

		PFG::stringList hFiles, cppFiles, qrcFiles, uicFiles, dependPaths;
		PFG::stringList includes;
		PFG::stringList moduleList;

		PFG::getAllFiles(path, hFiles, cppFiles, qrcFiles, uicFiles, dependPaths);

		PFG::getAllIncludes(path, hFiles, cppFiles, includes);
		PFG::getModules(includes, moduleList);

		
		if( vm.count("core") )
		{
			PFG::addToStringList(moduleList, std::string("+core"));
		}

		if( vm.count("no-core") )
		{
			PFG::addToStringList(moduleList, std::string("-core"));
		}
		
		if( vm.count("gui") )
		{
			PFG::addToStringList(moduleList, std::string("+gui"));
		}

		if( vm.count("no-gui") )
		{
			PFG::addToStringList(moduleList, std::string("-gui"));
		}

		if( vm.count("network") )
		{
			PFG::addToStringList(moduleList, std::string("+network"));
		}

		if( vm.count("no-network") )
		{
			PFG::addToStringList(moduleList, std::string("-network"));
		}

		if( vm.count("opengl") )
		{
			PFG::addToStringList(moduleList, std::string("+opengl"));
		}

		if( vm.count("no-opengl") )
		{
			PFG::addToStringList(moduleList, std::string("-opengl"));
		}

		if( vm.count("sql") )
		{
			PFG::addToStringList(moduleList, std::string("+sql"));
		}

		if( vm.count("no-sql") )
		{
			PFG::addToStringList(moduleList, std::string("-sql"));
		}

		if( vm.count("svg") )
		{
			PFG::addToStringList(moduleList, std::string("+svg"));
		}

		if( vm.count("no-svg") )
		{
			PFG::addToStringList(moduleList, std::string("-svg"));
		}

		if( vm.count("qt3support") )
		{
			PFG::addToStringList(moduleList, std::string("+qt3support"));
		}

		if( vm.count("no-qt3support") )
		{
			PFG::addToStringList(moduleList, std::string("-qt3support"));
		}

		if( vm.count("xml") )
		{
			PFG::addToStringList(moduleList, std::string("+xml"));
		}

		if( vm.count("no-xml") )
		{
			PFG::addToStringList(moduleList, std::string("-xml"));
		}

		PFG::writeProFile(hFiles, cppFiles, qrcFiles, uicFiles, dependPaths, moduleList, templateType, appName, sbuf, libDirs, libs);
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

			fileList h_files, cpp_files, qrc_files, uic_files;
			pathList depend_paths;
			includeList includes;

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
