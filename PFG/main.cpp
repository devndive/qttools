#include "get_all_files.h"
#include "get_all_includes.h"
#include "write_pro_file.h"
#include "get_modules.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	
	QStringList argumentList = QCoreApplication::arguments();
	
	QString inputDirectory = ".";
	QString appName = "Default Application";
	QString outputFile = "";
	QString templateType = "app";
		
	QStringList libDirs, libs;
	QTextStream textStream(stdout);
	
	if( argumentList.contains("--help") )
	{
		textStream << "For most users no module options, no libs and no lib-dirs are needed. ";
		textStream << "You should probably be fine with --input-dir, --name and --output-file";
		textStream << "\n";
		textStream << "e.g.:\n";
		textStream << "  PFG --input-dir ~/qttools/PFG/ --name PFG --output-file PFG.pro";
		textStream << "\n\n";
		textStream << "For more information see\n";
		textStream << "  http://qttools.googlecode.com/\n";
		textStream << "or conatact me directly\n";
		textStream << "  yann.duval.82@googlemail.com\n\n";
		
		return 0;
	}

	// get output-file parameter
	int index = argumentList.indexOf("--output-file");
	if (index != -1 && ((index + 1) < argumentList.count()))
	{		
		QFile *file = new QFile(argumentList.at(index+1));
		if(file->open(QFile::WriteOnly))
		{
			textStream.setDevice(file);
		}
	}

	index = argumentList.indexOf("--input-directory");
	if (index != -1 && ((index + 1) < argumentList.count()))
	{
		QDir inputParam(argumentList.at(index+1));
		if(inputParam.exists())
		{
			inputDirectory = inputParam.path();
		}
	}
	
	index = argumentList.indexOf("--name");
	if(index != -1 && (index + 1) < argumentList.count())
	{
		appName = argumentList.at(index + 1);
	}

	QFileInfoList hFiles, cppFiles, qrcFiles, uicFiles, dependPaths;
	QStringList includes;
	QStringList moduleList;

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

	PFG::writeProFile(inputDirectory, hFiles, cppFiles, qrcFiles, uicFiles, dependPaths, moduleList, templateType, appName, textStream.device(), libDirs, libs);
}
