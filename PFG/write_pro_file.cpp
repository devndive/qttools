#include "write_pro_file.h"
#include "definitions.h"

#include <iostream>

void write_pro_file(file_list &h_files, file_list &cpp_files, file_list &qrc_files, file_list &uic_files, path_list &depend_paths, std::string &modules, std::string &templateType, std::string &target)
{
	if( !(h_files.empty() && cpp_files.empty() && qrc_files.empty() && uic_files.empty()) )
	{
		std::cout << "TEMPLATE = " << templateType << std::endl;
		std::cout << "TARGET = " << target << std::endl;

		if( !depend_paths.empty() )
		{
			std::cout << "DEPENDPATH += .";
			for(file_list::iterator it = depend_paths.begin(); it != depend_paths.end(); it++)
			{
				std::cout << " " << *it;
			}
			std::cout << std::endl;

			std::cout << "INCLUDEPATH += .";
			for(file_list::iterator it = depend_paths.begin(); it != depend_paths.end(); it++)
			{
				std::cout << " " << *it;
			}
			std::cout << std::endl;
		}

		if( !modules.empty() )
		{
			std::cout << "QT += " << modules << std::endl;
		}

		if( !qrc_files.empty() )
		{
			std::cout << "RESOURCES = " << qrc_files[0];
			for(file_list::iterator it = qrc_files.begin()+1; it != qrc_files.end(); it++)
			{
				std::cout << " \\" << std::endl;
				std::cout << "            " << *it;
			}
			std::cout << std::endl;
		}

		if( !h_files.empty() )
		{
			std::cout << "HEADERS = " << h_files[0];
			for(file_list::iterator it = h_files.begin()+1; it != h_files.end(); it++)
			{
				std::cout << " \\" << std::endl;
				std::cout << "          " << *it;
			}
			std::cout << std::endl;
		}

		if( !cpp_files.empty() )
		{
			std::cout << "SOURCES = " << cpp_files[0];
			for(file_list::iterator it = cpp_files.begin()+1; it != cpp_files.end(); it++)
			{
				std::cout << " \\" << std::endl;
				std::cout << "          " << *it;
			}
			std::cout << std::endl;
		}

		if( !uic_files.empty() )
		{
			std::cout << "FORMS = " << uic_files[0];
			for(file_list::iterator it = uic_files.begin()+1; it != uic_files.end(); it++)
			{
				std::cout << " \\" << std::endl;
				std::cout << "        " << *it;
			}
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << " error: no project relevant files found!" << std::endl;
		std::cout << " please make sure that there are *.cpp, *.h, *.uic, *.rc or *.qrc" << std::endl;
		std::cout << "   in the given directory!" << std::endl;
	}
}
