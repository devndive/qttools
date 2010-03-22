#include "get_all_files.h"
#include <QtCore/QDir>
#include <iostream>

namespace PFG
{

int getAllFilesRec(const QDir path, stringList&, stringList&, stringList&, stringList&, stringList&);

void getAllFiles(const std::string &path, stringList &hFiles, stringList &cppFiles, stringList &qrcFiles, stringList &uicFiles, stringList &dependPaths)
{
	QDir baseSourceDirectory(path.c_str());
	
	getAllFilesRec(baseSourceDirectory, hFiles, cppFiles, qrcFiles, uicFiles, dependPaths);
}

int getAllFilesRec(const QDir path, stringList &h_files, stringList &cpp_files, stringList &qrc_files, stringList &uic_files, stringList &depend_paths)
{
	if ( !path.exists() )
	{
		std::cout << "\nNot found: " << qPrintable(path.absolutePath()) << std::endl;
		return 1;
	}
	
	// get all files and directories
	QStringList entries = path.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);

	for (int i = 0; i < entries.count(); ++i)
	{
		QFileInfo fileInfo(entries.at(i));
		
		if (fileInfo.isDir())
		{
			depend_paths.push_back(qPrintable(fileInfo.dir().absolutePath()));
			getAllFilesRec(fileInfo.dir(), h_files, cpp_files, qrc_files, uic_files, depend_paths);
		}
		else if	(fileInfo.isFile() && !fileInfo.fileName().startsWith("moc_") && !fileInfo.fileName().startsWith("qrc_"))
		{
			QString suffix = fileInfo.suffix();
			
			// source file
			if(suffix == "cpp" || suffix == "cc")
			{
				cpp_files.push_back( qPrintable(fileInfo.filePath()) );
			}
			// header file
			else if( suffix == ".h" || suffix == ".hpp" )
			{
				h_files.push_back( qPrintable(fileInfo.filePath()) );
			}
			// qt resource file
			else if( suffix == ".qrc" || suffix == ".rc" )
			{
				qrc_files.push_back( qPrintable(fileInfo.filePath()) );	
			}
			// ui file
			else if( suffix == ".uic" || suffix == ".ui" )
			{
				uic_files.push_back( qPrintable(fileInfo.filePath()) );
			}
		}
	}

	return 0;
}

} // namespace PFG

