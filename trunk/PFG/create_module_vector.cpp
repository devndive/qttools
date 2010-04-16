#include "create_module_vector.h"
#include "definitions.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>

namespace PFG
{

void createModuleVector(QList<QStringList>& moduleVector, bool shortModules)
{
	// Modulefiles will be in modules subdir. This should be configurable in future
	// now we expect, that the modules-folder is right next to the application it self
	QDir moduleBasePath(QCoreApplication::applicationDirPath().append("/modules/"));

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
			QFile file(fileList.at(i).filePath());
			
			// get module name from filename
			QString moduleName = fileList.at(i).baseName().split('_')[0];
			
			if(file.open(QFile::ReadOnly))
			{
				QTextStream textStream(&file);
				QStringList includes;
				
				// the module name is always the first entry in the list
				includes.push_back(moduleName);

				while(!file.atEnd())
				{
					addToStringList(includes, textStream.readLine());
				}
			
				moduleVector.push_back( includes );
				file.close();
			}
		}
	}
}

}
