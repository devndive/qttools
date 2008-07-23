#ifndef __GET_ALL_INCLUDES_H__
#define __GET_ALL_INCLUDES_H__

#include <string>
#include "definitions.h"

namespace PFG
{

void getAllIncludes(std::string &path, fileList &h_files, fileList &cpp_files, includeList &includes);

} // namespace PFG

#endif // __GET_ALL_INCLUDES_H__

