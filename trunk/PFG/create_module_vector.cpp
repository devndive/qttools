#include "create_module_vector.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QStringList>

#include <iostream>
#include <fstream>

namespace PFG
{

void createModuleVector( std::vector< stringList > &moduleVector, bool shortModules)
{
	// Modulefiles will be in modules subdir. This should be configurable in future
	QDir moduleBasePath("./modules/");

	// Check if moduleBasePath exists and is directory
	if( moduleBasePath.exists() )
	{
		// Get all files in directory, exclude SymLinks and special-files
		moduleBasePath.setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
		
		QStringList filterList;
		// only use short modulename lists
		if( shortModules )
		{
			filterList << "*_short";
		}
		// use the full modulename lists
		else
		{
			filterList << "*_long";
		}
		// set the name filter
		moduleBasePath.setNameFilters(filterList);
		
		// get the filelist
		QFileInfoList fileList = moduleBasePath.entryInfoList();


		for (int i = 0; i < fileList.count(); ++i)
		{
			std::ifstream file( qPrintable(fileList.at(i).filePath()) );
			stringList includes;
		
			while(file)
			{
				std::string line;
				std::getline(file, line);
				addToStringList(includes, line);
			}
			
			moduleVector.push_back( includes );
		}
	}
}

}
