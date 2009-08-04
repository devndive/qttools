#include "write_pro_file.h"
#include "definitions.h"

#include <iostream>
#include <iomanip>

namespace PFG
{

void writeList(stringList& listToWrite, const std::string& prefix, std::streambuf *sbuf)
{
	std::ostream output(sbuf);

	output << prefix << " = " << *(listToWrite.begin());
	
	for(stringList::iterator it = listToWrite.begin()+1; it != listToWrite.end(); it++)
	{
		output << " \\" << std::endl;
		output << std::setw(prefix.length()+2) << std::setfill(' ') << " " << *it;
	}
	output << std::endl;
}

void writeProFile
(	
	stringList &headerFiles
	, stringList &sourceFiles
	, stringList &qrcFiles
	, stringList &uicFiles
	, stringList &dependPaths
	, stringList &modules
	, std::string &templateType
	, std::string &target
	, std::streambuf *sbuf
	, stringList &libDirs
	, stringList &libs
)
{
	std::ostream output(sbuf);

	if( !(headerFiles.empty() && sourceFiles.empty() && qrcFiles.empty() && uicFiles.empty()) )
	{
		output << "TEMPLATE = " << templateType << std::endl;
		output << "TARGET = " << target << std::endl;

		if( !dependPaths.empty() )
		{
			output << "DEPENDPATH += .";
			for(stringList::iterator it = dependPaths.begin(); it != dependPaths.end(); it++)
			{
				output << " " << *it;
			}
			output << std::endl;

			output << "INCLUDEPATH += .";
			for(stringList::iterator it = dependPaths.begin(); it != dependPaths.end(); it++)
			{
				output << " " << *it;
			}
			output << std::endl;
		}

		if( !modules.empty() )
		{
			std::string qtAdd, qtSub;

			for(stringList::iterator it = modules.begin(); it != modules.end(); it++)
			{
				if( (*it)[0] == '+' )
				{
					qtAdd.append( " " );
					qtAdd.append( (*it).substr(1) );
				}

				if( (*it)[0] == '-' )
				{
					qtSub.append( " " );
					qtSub.append( (*it).substr(1) );
				}
			}

			if( !qtAdd.empty() )
			{
				output << "QT +=" << qtAdd << std::endl;
			}
			if( !qtSub.empty() )
			{
				output << "QT -=" << qtSub << std::endl;
			}
			//output << "QT += " << modules << std::endl;
		}

		if( !libDirs.empty() || !libs.empty() )
		{
			output << "LIBS +=";

			for(stringList::iterator it = libDirs.begin(); it != libDirs.end(); it++)
			{
				output << " -L" << *it;
			}

			for(stringList::iterator it = libs.begin(); it != libs.end(); it++)
			{
				output << " -l" << *it;
			}

			output << std::endl;
		}

		if( !qrcFiles.empty() )
		{
			writeList(qrcFiles, "RESOURCES", output.rdbuf());
		}

		if( !headerFiles.empty() )
		{
			writeList(headerFiles, "HEADERS", output.rdbuf());
		}

		if( !sourceFiles.empty() )
		{
			writeList(sourceFiles, "SOURCES", output.rdbuf());
		}

		if( !uicFiles.empty() )
		{
			writeList(uicFiles, "FORMS", output.rdbuf());
		}
	}
	else
	{
		output << " error: no project relevant files found!" << std::endl;
		output << " please make sure that there are *.cpp, *.h, *.uic, *.rc or *.qrc" << std::endl;
		output << "   in the given directory!" << std::endl;
	}
}

} // namespace PFG

