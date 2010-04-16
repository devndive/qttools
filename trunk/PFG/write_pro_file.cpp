#include "write_pro_file.h"

#include <QtCore/QFileInfoList>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <QtCore/QDir>

namespace PFG
{

void writeList(QDir basePath, QFileInfoList listToWrite, const QString &prefix, QIODevice *device, const QString &appender)
{
	if(listToWrite.count() > 0)
	{
		QTextStream textStream(device);
		
		textStream << prefix << appender << basePath.relativeFilePath(listToWrite.begin()->canonicalFilePath());
		
		if(listToWrite.count() > 1)
		{
			for(QFileInfoList::iterator it = listToWrite.begin() + 1; it != listToWrite.end(); it++)
			{
				textStream << " \\\n";
				textStream << " " << basePath.relativeFilePath(it->canonicalFilePath());
			}
		}
		
		textStream << "\n";
	}
}

void writeProFile
(	
	QDir basePath
	, QFileInfoList headerFiles
	, QFileInfoList sourceFiles
	, QFileInfoList qrcFiles
	, QFileInfoList uicFiles
	, QFileInfoList dependPaths
	, QStringList modules
	, QString &templateType
	, QString &target
	, QIODevice *device
	, QStringList libDirs
	, QStringList libs
)
{
	QTextStream textStream(device);
	
	if( !(headerFiles.empty() && sourceFiles.empty() && qrcFiles.empty() && uicFiles.empty()) )
	{
		textStream << "TEMPLATE = " << templateType << "\n";
		textStream << "TARGET = " << target << "\n";
		textStream.flush();

		if( !dependPaths.empty() )
		{
			writeList(basePath, dependPaths, "DEPENDPATH", device, " += . ");
			writeList(basePath, dependPaths, "INCLUDEPATH", device, " += . ");
		}

		if( !modules.empty() )
		{
			QString qtAdd, qtSub;

			for(QStringList::iterator it = modules.begin(); it != modules.end(); it++)
			{
				if( (*it)[0] == '+' )
				{
					qtAdd.append( " " );
					qtAdd.append( (*it).mid(1) );
				}

				if( (*it)[0] == '-' )
				{
					qtSub.append( " " );
					qtSub.append( (*it).mid(1) );
				}
			}

			if( !qtAdd.isEmpty() )
			{
				textStream << "QT +=" << qPrintable(qtAdd) << "\n";
			}
			if( !qtSub.isEmpty() )
			{
				textStream << "QT -=" << qPrintable(qtSub) << "\n";
			}
		}

		if( !libDirs.empty() || !libs.empty() )
		{
			textStream << "LIBS +=";

			for(QStringList::iterator it = libDirs.begin(); it != libDirs.end(); it++)
			{
				textStream << " -L" << qPrintable(*it);
			}

			for(QStringList::iterator it = libs.begin(); it != libs.end(); it++)
			{
				textStream << " -l" << qPrintable(*it);
			}

			textStream << "\n";
		}
		
		textStream.flush();

		if( !qrcFiles.empty() )
		{
			writeList(basePath, qrcFiles, "RESOURCES", textStream.device());
		}

		if( !headerFiles.empty() )
		{
			writeList(basePath, headerFiles, "HEADERS", textStream.device());
		}

		if( !sourceFiles.empty() )
		{
			writeList(basePath, sourceFiles, "SOURCES", textStream.device());
		}

		if( !uicFiles.empty() )
		{
			writeList(basePath, uicFiles, "FORMS", textStream.device());
		}
	}
	else
	{
		textStream << " error: no project relevant files found!" << "\n";
		textStream << " please make sure that there are *.cpp, *.h, *.uic, *.rc or *.qrc" << "\n";
		textStream << "   in the given directory!" << "\n";
	}
}

} // namespace PFG

