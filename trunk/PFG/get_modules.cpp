#include "get_modules.h"
#include "definitions.h"
#include "create_module_vector.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

namespace PFG
{

void getModules(QStringList& includes, QStringList& modules, bool useShortModules)
{
	QList<QStringList> moduleVector;
	createModuleVector( moduleVector, useShortModules );
	
	for(QStringList::iterator it = includes.begin(); it != includes.end(); it++)
	{
		QString qtInclude;

		size_t pos1 = (*it).indexOf('\"');
		if( pos1 != -1 )
		{
			size_t last = (*it).lastIndexOf('\"');
			qtInclude = (*it).mid( pos1 + 1, last - pos1 - 1 );
		}

		size_t pos2 = (*it).indexOf('<');
		if( pos2 != -1 )
		{
			size_t last = (*it).lastIndexOf('>');
			qtInclude = (*it).mid( pos2 + 1, last - pos2 - 1 );
		}

		for( QList< QStringList >::iterator itMod = moduleVector.begin(); itMod != moduleVector.end(); itMod++ )
		{
			for( QStringList::iterator stringIt = (*itMod).begin(); stringIt != (*itMod).end(); stringIt++ )
			{
				//comparisons++;
				if( qtInclude.indexOf( *stringIt ) != -1 )
				{
					addToStringList(modules, QString("+").append(*(itMod->begin())) );
				}
			}
		}
	}
}

} // namespace PFG

