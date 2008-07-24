#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include <vector>
#include <string>

namespace PFG
{

/*
typedef std::vector< std::string > fileList;
typedef std::vector< std::string > pathList;
typedef std::vector< std::string > includeList;
*/

typedef std::vector< std::string > stringList;

void addToStringList(stringList &list, const std::string &toAdd);

}

#endif // __DEFINITIONS_H__
