#include "get_all_files.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

namespace PFG
{

int getAllFilesRec(const QDir path, QFileInfoList&, QFileInfoList&, QFileInfoList&, QFileInfoList&, QFileInfoList&);

void getAllFiles(const QString path, QFileInfoList& hFiles, QFileInfoList& cppFiles, QFileInfoList& qrcFiles, QFileInfoList& uicFiles, QFileInfoList& dependPaths)
{
	QDir baseSourceDirectory(path);
	getAllFilesRec(baseSourceDirectory, hFiles, cppFiles, qrcFiles, uicFiles, dependPaths);
}

int getAllFilesRec
(	const QDir path
	, QFileInfoList& h_files
	, QFileInfoList& cpp_files
	, QFileInfoList& qrc_files
	, QFileInfoList& uic_files
	, QFileInfoList& depend_paths
)
{
	if ( !path.exists() )
	{
		return 1;
	}
	
	// get all files and directories
	QFileInfoList entries = path.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);

	for (int i = 0; i < entries.count(); ++i)
	{
		QFileInfo fileInfo = entries.at(i);

		if (fileInfo.isDir() && 
			fileInfo.baseName() != "build" && 
			fileInfo.baseName() != "Build" && 
			!fileInfo.suffix().endsWith("xcodeproj") &&
			!fileInfo.suffix().endsWith("app")
			)
		{
			depend_paths << fileInfo.absoluteFilePath();
			getAllFilesRec(fileInfo.absoluteFilePath(), h_files, cpp_files, qrc_files, uic_files, depend_paths);
		}
		else if	(fileInfo.isFile() && !fileInfo.fileName().startsWith("moc_") && !fileInfo.fileName().startsWith("qrc_"))
		{
			QString suffix = fileInfo.suffix();
			
			// source file
			if(suffix == "cpp" || suffix == "cc")
			{
				cpp_files << fileInfo;
			}
			// header file
			else if( suffix == "h" || suffix == "hpp" )
			{
				h_files << fileInfo;
			}
			// qt resource file
			else if( suffix == "qrc" || suffix == "rc" )
			{
				qrc_files << fileInfo;	
			}
			// ui file
			else if( suffix == "uic" || suffix == "ui" )
			{
				uic_files << fileInfo;
			}
		}
	}

	return 0;
}

} // namespace PFG

