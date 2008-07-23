#include "get_modules.h"

#include <vector>
#include <algorithm>

typedef std::vector< std::string > module_list;

namespace PFG
{

//void addToModuleList(module_list &l, const std::string &toAdd);

void getModules(stringList &includes, stringList &modules)
{
	for(stringList::iterator it = includes.begin(); it != includes.end(); it++)
	{
		//std::cout << *it << std::endl;

		std::string qtInclude;

		size_t pos1 = (*it).find("\"");
		if( pos1 != std::string::npos )
		{
			//std::cout << "found \" at pos (" << pos1 << ")" << std::endl;
			size_t last = (*it).rfind("\"");
			//std::cout << "found \" at pos (" << last << ")" << std::endl;

			qtInclude = (*it).substr( pos1 + 1, last - pos1 - 1 );
		}

		size_t pos2 = (*it).find("<");
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
			addToStringList(modules, std::string("+xml"));
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
			addToStringList(modules, std::string("+network"));
		}
		else if(qtInclude.find("QtOpenGL") != std::string::npos ||
			qtInclude.find("QGL") != std::string::npos )
		{
			addToStringList(modules, std::string("+opengl"));
		}
		else if( qtInclude.find("Q3") != std::string::npos )
		{
			addToStringList(modules, std::string("+qt3support"));
		}
		else if(qtInclude.find("QtSql") != std::string::npos ||
			qtInclude.find("QSql") != std::string::npos )
		{
			addToStringList(modules, std::string("+sql"));
		}
		else if(qtInclude.find("QtSvg") != std::string::npos ||
			qtInclude.find("QGraphics") != std::string::npos ||
			qtInclude.find("QSvg") != std::string::npos )
		{
			addToStringList(modules, std::string("+svg"));
		}
	}

	/*
	for(module_list::iterator it = modules.begin(); it != modules.end(); it++)
	{
		module_string.append( *it );
		module_string.append( " " );
	}
	*/

	//return( module_string );
}
/*
void addToModuleList(module_list &l, const std::string &toAdd)
{
	includeList::iterator result = std::find(l.begin(), l.end(), toAdd);

	if( result == l.end() )
	{
		l.push_back(toAdd);
	}
}
*/
} // namespace PFG

