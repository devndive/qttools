#include "get_modules_string.h"

#include <vector>
#include <algorithm>

typedef std::vector< std::string > module_list;

void addToModuleList(module_list &l, std::string &toAdd);

std::string get_modules_string(include_list &includes)
{
	module_list modules;
	std::string module_string;

	for(include_list::iterator it = includes.begin(); it != includes.end(); it++)
	{
		//std::cout << *it << std::endl;

		size_t pos1, pos2;
		std::string qtInclude;

		pos1 = (*it).find("\"");
		if( pos1 != std::string::npos )
		{
			//std::cout << "found \" at pos (" << pos1 << ")" << std::endl;
			size_t last = (*it).rfind("\"");
			//std::cout << "found \" at pos (" << last << ")" << std::endl;

			qtInclude = (*it).substr( pos1 + 1, last - pos1 - 1 );
		}

		pos2 = (*it).find("<");
		if( pos2 != std::string::npos )
		{
			//std::cout << "found < at pos (" << pos2 << ")" << std::endl;
			size_t last = (*it).rfind(">");
			//std::cout << "found > at pos (" << last << ")" << std::endl;

			qtInclude = (*it).substr( pos2 + 1, last - pos2 - 1 );
		}

		//std::cout << "qtInclude: " << qtInclude << std::endl;

		if( qtInclude.find("QtXml") != std::string::npos ||
			qtInclude.find("QDom") != std::string::npos ||
			qtInclude.find("QXml") != std::string::npos )
		{
			addToModuleList(modules, std::string("xml"));
		}
		else if( qtInclude.find("QtNetwork") != std::string::npos ||
			qtInclude.find("QAbstractSocket") != std::string::npos ||
			qtInclude.find("QAuthenticator") != std::string::npos ||
			qtInclude.find("QFtp") != std::string::npos ||
			qtInclude.find("QHost") != std::string::npos ||
			qtInclude.find("QHttp") != std::string::npos ||
			qtInclude.find("QLocal") != std::string::npos ||
			qtInclude.find("QNetwork") != std::string::npos ||
			qtInclude.find("QSsl") != std::string::npos ||
			qtInclude.find("QTcp") != std::string::npos ||
			qtInclude.find("QUdp") != std::string::npos ||
			qtInclude.find("QUrl") != std::string::npos )
		{
			addToModuleList(modules, std::string("network"));
		}
		else if(qtInclude.find("QtOpenGL") != std::string::npos ||
			qtInclude.find("QGL") != std::string::npos )
		{
			addToModuleList(modules, std::string("opengl"));
		}
		else if( qtInclude.find("Q3") != std::string::npos )
		{
			addToModuleList(modules, std::string("qt3support"));
		}
		else if(qtInclude.find("QtSql") != std::string::npos ||
			qtInclude.find("QSql") != std::string::npos )
		{
			addToModuleList(modules, std::string("sql"));
		}
		else if(qtInclude.find("QtSvg") != std::string::npos ||
			qtInclude.find("QGraphics") != std::string::npos ||
			qtInclude.find("QSvg") != std::string::npos )
		{
			addToModuleList(modules, std::string("svg"));
		}
	}

	for(module_list::iterator it = modules.begin(); it != modules.end(); it++)
	{
		module_string.append( *it );
		module_string.append( " " );
	}

	return( module_string );
}

void addToModuleList(module_list &l, std::string &toAdd)
{
	include_list::iterator result = std::find(l.begin(), l.end(), toAdd);

	if( result == l.end() )
	{
		l.push_back(toAdd);
	}
}





			



