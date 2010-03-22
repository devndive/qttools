#include "definitions.h"
#include "get_all_files.h"
#include "get_all_includes.h"
#include "write_pro_file.h"
#include "get_modules.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QDir>

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	
	QStringList argumentList = QCoreApplication::arguments();
	
	QStringList possibleArgs;
	// arguments for help
	possibleArgs << "--help" << "-h";
	// arguments for input directory
	possibleArgs << "--input-dir" << "-i";
	// arguments for the application name
	possibleArgs << "--name" << "-n";
	// arguments for the output file
	possibleArgs << "--output-file" << "-o";
	// arguments for the template type
	possibleArgs << "--template-type" << "-t";
	// arguments to not use short module-list
	possibleArgs << "--no-short-modules";
	
	try
	{
		std::string inputDirectory = ".";
		std::string appName = "Default Application";
		std::string outputFile = "";
		std::string templateType = "app";
		
		PFG::stringList libDirs, libs;
		std::streambuf* sbuf(std::cout.rdbuf());


		if( argumentList.contains("--help") )
		{
			std::cout << "For most users no module options, no libs and no lib-dirs are needed. ";
			std::cout << "You should probably be fine with --input-dir, --name and --output-file";
			std::cout << std::endl << std::endl;
			std::cout << "e.g.:" << std::endl;
			std::cout << "  PFG --input-dir ~/qttools/PFG/ --name PFG --output-file PFG.pro";
			std::cout << std::endl << std::endl;
			std::cout << "For more information see" << std::endl;
			std::cout << "  http://qttools.googlecode.com/" << std::endl;
			std::cout << "or conatact me directly" << std::endl;
			std::cout << "  yann.duval.82@googlemail.com" << std::endl << std::endl;

			return(0);
		}

		// get output-file parameter
		int index = argumentList.indexOf("--output-file");
		if (index != -1 && ((index + 1) < argumentList.count()))
		{
			std::ofstream outputFileStream(qPrintable(argumentList.at(index)), std::ofstream::out);
			if(outputFileStream)
			{
				sbuf = outputFileStream.rdbuf();
			}
		}

		index = argumentList.indexOf("--input-directory");
		if (index != -1 && ((index + 1) < argumentList.count()))
		{
			QDir inputDirectory(argumentList.at(index));
			if(inputDirectory.exists())
			{
				inputDirectory = qPrintable(argumentList.at(index));
			}
		}

		PFG::stringList hFiles, cppFiles, qrcFiles, uicFiles, dependPaths;
		PFG::stringList includes;
		PFG::stringList moduleList;

		PFG::getAllFiles(inputDirectory, hFiles, cppFiles, qrcFiles, uicFiles, dependPaths);

		PFG::getAllIncludes(inputDirectory, hFiles, cppFiles, includes);

		if( argumentList.contains("--no-short-modules") )
		{
			PFG::getModules(includes, moduleList);
		}
		else
		{
			PFG::getModules(includes, moduleList, true);
		}

		PFG::writeProFile(hFiles, cppFiles, qrcFiles, uicFiles, dependPaths, moduleList, templateType, appName, sbuf, libDirs, libs);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << "\n";
	}
}

