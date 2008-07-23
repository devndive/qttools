#include <algorithm>
#include "definitions.h"

namespace PFG
{

void addToStringList(stringList &list, const std::string &toAdd)
{
	stringList::iterator result = std::find(list.begin(), list.end(), toAdd);

	if( result == list.end() )
	{
		list.push_back(toAdd);
	}
}

} // namespace PFG

