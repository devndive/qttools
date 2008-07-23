#ifndef __GET_ALL_INCLUDES_H__
#define __GET_ALL_INCLUDES_H__

#include <string>
#include "definitions.h"

namespace PFG
{

void getAllIncludes(std::string &path, stringList &h_files, stringList &cpp_files, stringList &includes);

} // namespace PFG

#endif // __GET_ALL_INCLUDES_H__

