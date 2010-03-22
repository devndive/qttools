#include "definitions.h"

#include <algorithm>

namespace PFG
{

void addToStringList(stringList &list, const std::string &toAdd)
{
	if( toAdd.size() > 0 )
	{
		stringList::iterator result = std::find(list.begin(), list.end(), toAdd);

		if( result == list.end() )
		{
			list.push_back(toAdd);
		}
	}
}

} // namespace PFG

