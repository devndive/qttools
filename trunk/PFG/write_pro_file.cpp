#include "write_pro_file.h"
#include "definitions.h"

#include <iostream>

namespace PFG
{

void writeProFile(stringList &h_files, stringList &cpp_files, stringList &qrc_files, stringList &uic_files, stringList &depend_paths, stringList &modules, std::string &templateType, std::string &target, std::streambuf *sbuf, stringList &libDirs, stringList &libs)
{
	std::ostream output(sbuf);

	if( !(h_files.empty() && cpp_files.empty() && qrc_files.empty() && uic_files.empty()) )
	{
		output << "TEMPLATE = " << templateType << std::endl;
		output << "TARGET = " << target << std::endl;

		if( !depend_paths.empty() )
		{
			output << "DEPENDPATH += .";
			for(stringList::iterator it = depend_paths.begin(); it != depend_paths.end(); it++)
			{
				output << " " << *it;
			}
			output << std::endl;

			output << "INCLUDEPATH += .";
			for(stringList::iterator it = depend_paths.begin(); it != depend_paths.end(); it++)
			{
				output << " " << *it;
			}
			output << std::endl;
		}

		if( !modules.empty() )
		{
			std::string qt_add, qt_sub;

			for(stringList::iterator it = modules.begin(); it != modules.end(); it++)
			{
				if( (*it)[0] == '+' )
				{
					qt_add.append( " " );
					qt_add.append( (*it).substr(1) );
				}

				if( (*it)[0] == '-' )
				{
					qt_sub.append( " " );
					qt_sub.append( (*it).substr(1) );
				}
			}

			if( !qt_add.empty() )
			{
				output << "QT +=" << qt_add << std::endl;
			}
			if( !qt_sub.empty() )
			{
				output << "QT -=" << qt_sub << std::endl;
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

		if( !qrc_files.empty() )
		{
			output << "RESOURCES = " << qrc_files[0];
			for(stringList::iterator it = qrc_files.begin()+1; it != qrc_files.end(); it++)
			{
				output << " \\" << std::endl;
				output << "            " << *it;
			}
			output << std::endl;
		}

		if( !h_files.empty() )
		{
			output << "HEADERS = " << h_files[0];
			for(stringList::iterator it = h_files.begin()+1; it != h_files.end(); it++)
			{
				output << " \\" << std::endl;
				output << "          " << *it;
			}
			output << std::endl;
		}

		if( !cpp_files.empty() )
		{
			output << "SOURCES = " << cpp_files[0];
			for(stringList::iterator it = cpp_files.begin()+1; it != cpp_files.end(); it++)
			{
				output << " \\" << std::endl;
				output << "          " << *it;
			}
			output << std::endl;
		}

		if( !uic_files.empty() )
		{
			output << "FORMS = " << uic_files[0];
			for(stringList::iterator it = uic_files.begin()+1; it != uic_files.end(); it++)
			{
				output << " \\" << std::endl;
				output << "        " << *it;
			}
			output << std::endl;
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

