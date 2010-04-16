#include "definitions.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

namespace PFG
{

void addToStringList(QStringList& list, QString toAdd)
{	
	if( !toAdd.isEmpty() )
	{		
		int index = list.indexOf( toAdd );
		if( index == -1 )
		{
			list.push_back(toAdd);
		}
	}
}

} // namespace PFG

