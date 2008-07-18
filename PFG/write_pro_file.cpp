#include "write_pro_file.h"
#include "definitions.h"

#include <iostream>

void write_pro_file(fileList &h_files, fileList &cpp_files, fileList &qrc_files, fileList &uic_files, pathList &depend_paths, std::string &modules, std::string &templateType, std::string &target, std::streambuf *sbuf)
{
	std::ostream output(sbuf);

	if( !(h_files.empty() && cpp_files.empty() && qrc_files.empty() && uic_files.empty()) )
	{
		output << "TEMPLATE = " << templateType << std::endl;
		output << "TARGET = " << target << std::endl;

		if( !depend_paths.empty() )
		{
			output << "DEPENDPATH += .";
			for(fileList::iterator it = depend_paths.begin(); it != depend_paths.end(); it++)
			{
				output << " " << *it;
			}
			output << std::endl;

			output << "INCLUDEPATH += .";
			for(fileList::iterator it = depend_paths.begin(); it != depend_paths.end(); it++)
			{
				output << " " << *it;
			}
			output << std::endl;
		}

		if( !modules.empty() )
		{
			output << "QT += " << modules << std::endl;
		}

		if( !qrc_files.empty() )
		{
			output << "RESOURCES = " << qrc_files[0];
			for(fileList::iterator it = qrc_files.begin()+1; it != qrc_files.end(); it++)
			{
				output << " \\" << std::endl;
				output << "            " << *it;
			}
			output << std::endl;
		}

		if( !h_files.empty() )
		{
			output << "HEADERS = " << h_files[0];
			for(fileList::iterator it = h_files.begin()+1; it != h_files.end(); it++)
			{
				output << " \\" << std::endl;
				output << "          " << *it;
			}
			output << std::endl;
		}

		if( !cpp_files.empty() )
		{
			output << "SOURCES = " << cpp_files[0];
			for(fileList::iterator it = cpp_files.begin()+1; it != cpp_files.end(); it++)
			{
				output << " \\" << std::endl;
				output << "          " << *it;
			}
			output << std::endl;
		}

		if( !uic_files.empty() )
		{
			output << "FORMS = " << uic_files[0];
			for(fileList::iterator it = uic_files.begin()+1; it != uic_files.end(); it++)
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
