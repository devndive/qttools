#include "get_all_includes.h"
#include "definitions.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>

namespace PFG
{

void getAllIncludes(QString path, QFileInfoList h_files, QFileInfoList cpp_files, QStringList& includes)
{
	for(QFileInfoList::iterator it = h_files.begin(); it != h_files.end(); it++)
	{		
		QFile file(it->absoluteFilePath());
		
		if(file.open(QFile::ReadOnly))
		{
			QTextStream textStream(&file);
			
			while(!textStream.atEnd())
			{
				QString line = textStream.readLine();
				
				if( line.indexOf("#include ") != -1 && line.indexOf("Q") != -1 )
				{
					addToStringList(includes, line);
				}
			}
			
			file.close();
		}
	}

	for(QFileInfoList::iterator it = cpp_files.begin(); it != cpp_files.end(); it++)
	{
		QFile file(it->absoluteFilePath());
		if(file.open(QFile::ReadOnly))
		{
			QTextStream textStream(&file);
			
			while(!textStream.atEnd())
			{
				QString line = textStream.readLine();

				if( line.indexOf("//") == -1 && 
					line.indexOf("#include ") != -1 && 
					line.indexOf("Q") != -1
				   )
				{
					addToStringList(includes, line);
				}
			}
			
			file.close();
		}
	}
}

} // namespace PFG

